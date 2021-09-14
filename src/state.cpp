#include "../inc/state.h"

#include "../inc/definitions.h"
#include "../inc/packetheader.h"
#include "../inc/packetlapdata.h"
#include "../inc/packetevent.h"

#include <iostream>

namespace ris
{
    Packets getAllPacketsFromFrame(Network::Ptr network)
    {
        Packets result = std::make_shared<std::vector<Bytes>>();
        Packets nextpackets = std::make_shared<std::vector<Bytes>>();

        double frame = 0;
        ris::Bytes bytes;

        do
        {
            bytes = network->read();

            // if we have an event return event
            PacketID packetid = (PacketID)bytes.at(5);
            if (packetid == PacketID::Event)
            {
                result->push_back(bytes);
                return result;
            }

            // Get all the packets on the frame
            Pos pos = 0;
            PacketHeader header(bytes, pos);

            double nextframe = header.telemetry(PacketHeader::FRAMEIDENTIFIER).at(0);

            if (frame == nextframe)
            {
                nextpackets->push_back(bytes);
                continue;
            }
            else if (frame == 0 || nextframe == 0)
            {
                frame = nextframe;
                continue;
            }
            else if (nextframe >= frame)
            {
                result = std::move(nextpackets);

                nextpackets = std::make_shared<std::vector<Bytes>>();
                nextpackets->push_back(bytes);
                frame = nextframe;
                return result;
            }
            else
            {
                continue;
            }
        } while (!bytes.empty());

        return result;
    }

    template <class T>
    Packet::Ptr getPacket(const Packets &packets, PacketID id)
    {
        for (const auto &bytes : *packets)
        {
            if ((PacketID)bytes.at(5) == id)
            {
                return std::make_shared<T>(bytes);
            }
        }
        return nullptr;
    }

    State::State(Network::Ptr network)
        : network_{network} {}

    void State::initialisePacketsFromNetwork()
    {
        packets_ = getAllPacketsFromFrame(network_);
    }

    bool State::hasSessionStarted()
    {
        bool didSessionEnd = false;

        if (hasSessionEnded())
        {
            return false;
        }
        if (getPacket<PacketLapData>(packets_, PacketID::Lap_Data))
        {
            return true;
        }
        return false;
    }

    bool State::hasSessionEnded()
    {
        Packet::Ptr event = getPacket<PacketEvent>(packets_, PacketID::Event);
        if (event && (event->packets(PacketEvent::Event::EVENT).at(0)->telemetry(PacketEvent::Event::EVENTSTRINGCODE).to_string() == "SEND"))
        {
            return true;
        }
        return false;
    }

    bool State::hasStartedLap()
    {
        Packet::Ptr lapdata = getPacket<PacketLapData>(packets_, PacketID::Lap_Data);

        if (lapdata && ((lapdata->packets(PacketLapData::LapData::LAPDATA).at(static_cast<size_t>(lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0)))->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0) >= 0) &&
                        ((lapdata->packets(PacketLapData::LapData::LAPDATA).at(static_cast<size_t>(lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0)))->telemetry(PacketLapData::LapData::CURRENTLAPTIMEINMS).at(0) != 0) ||
                         (lapdata->packets(PacketLapData::LapData::LAPDATA).at(static_cast<size_t>(lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0)))->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0) < 500))))
        {
            currentlap_ = lapdata->packets(PacketLapData::LapData::LAPDATA).at(static_cast<size_t>(lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0)))->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0);
            return true;
        }
        return false;
    }

    bool State::returnedToPits()
    {
        Packet::Ptr lapdata = getPacket<PacketLapData>(packets_, PacketID::Lap_Data);
        if (lapdata && (lapdata->packets(PacketLapData::LapData::LAPDATA).at(static_cast<size_t>(lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0)))->telemetry(PacketLapData::LapData::PITSTATUS).at(0) == 1))
        {
            return true;
        }
        return false;
    }

    bool State::hasLapFinished()
    {
        Packet::Ptr lapdata = getPacket<PacketLapData>(packets_, PacketID::Lap_Data);
        if (lapdata)
        {
            if (currentlap_ != lapdata->packets(PacketLapData::LapData::LAPDATA).at(static_cast<size_t>(lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0)))->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0))
            {
                currentlap_ = lapdata->packets(PacketLapData::LapData::LAPDATA).at(static_cast<size_t>(lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0)))->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0);
                return true;
            }
        }
        return false;
    }

    Packets State::getPackets() const
    {
        return packets_;
    }

    double State::getCurrentLap() const
    {
        return currentlap_;
    }
} // namespace ris
