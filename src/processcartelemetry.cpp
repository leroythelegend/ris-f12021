#include "../inc/processcartelemetry.h"
#include "../inc/packetcartelemetrydata.h"
#include "../inc/packetlapdata.h"
#include "../inc/packetheader.h"
#include "../inc/packetmotiondata.h"

namespace ris
{
    void ProcessCarTelemetry::process(Packets packets)
    {
        Telemetry telemetry;

        for (const auto &b : *packets)
        {
            if ((PacketID)b.at(5) == PacketID::Car_Telemetry)
            {
                PacketCarTelemetryData packet(b);
                size_t playerindex = static_cast<size_t>(packet.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0));
                telemetry.packets.push_back(packet.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(playerindex));
                telemetry.packets.push_back(packet.packets(PacketCarTelemetryData::CarTelemetryData::CARTELEMETRYDATA).at(0));
            }

            if ((PacketID)b.at(5) == PacketID::Motion)
            {
                PacketMotionData packet(b);
                size_t playerindex = static_cast<size_t>(packet.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0));
                telemetry.packets.push_back(packet.packets(PacketMotionData::CarMotionData::CARMOTIONDATA).at(playerindex));
                telemetry.packets.push_back(packet.packets(PacketMotionData::MotionData::MOTIONDATA).at(0));
            }
        }

        if (telemetry.packets.size() == 4)
        {
            PacketLapData::Ptr lapdata;

            for (const auto &b : *packets)
            {
                if ((PacketID)b.at(5) == PacketID::Lap_Data)
                {
                    lapdata = std::make_shared<PacketLapData>(b);
                    break;
                }
            }

            if (lapdata)
            {
                size_t playerindex = static_cast<size_t>(lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0));

                telemetry.currentlap = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0);
                telemetry.time = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPTIMEINMS).at(0);
                telemetry.distance = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0);
                if (previousdistance_ < telemetry.distance)
                {
                    previousdistance_ = telemetry.distance;
                    telemetries_->push_back(telemetry);
                }
            }
        }
    }

    void ProcessCarTelemetry::record()
    {
        record_->record(telemetries_);
    }

    void ProcessCarTelemetry::reset()
    {
        telemetries_->clear();
        previousdistance_ = -1;
    }
} // namespace ris
