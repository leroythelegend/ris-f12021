#include "../inc/processcartelemetry.h"
#include "../inc/packetcartelemetrydata.h"
#include "../inc/packetlapdata.h"
#include "../inc/packetheader.h"

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
                telemetry.packets.push_back(packet.packets(PacketCarTelemetryData::CarTelemetry::CARTELEMETRY).at(packet.packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0)));
                telemetry.packets.push_back(packet.packets(PacketCarTelemetryData::CarTelemetryData::CARTELEMETRYDATA).at(0));
                break;
            }
        }

        if (!telemetry.packets.empty())
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
                double playerindex = lapdata->packets(PacketHeader::PACKETHEADER).at(0)->telemetry(PacketHeader::PLAYERCARINDEX).at(0);

                telemetry.currentlap = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPNUM).at(0);
                telemetry.time = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::CURRENTLAPTIMEINMS).at(0);
                telemetry.distance = lapdata->packets(PacketLapData::LapData::LAPDATA).at(playerindex)->telemetry(PacketLapData::LapData::LAPDISTANCE).at(0);
                telemetries_.push_back(telemetry);
            }
        }
    }

    void ProcessCarTelemetry::record()
    {
        record_->record(telemetries_);
    }

    void ProcessCarTelemetry::reset()
    {
        telemetries_.clear();
    }
} // namespace ris
