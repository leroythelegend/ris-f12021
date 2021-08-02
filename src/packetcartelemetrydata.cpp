#include "../inc/packetcartelemetrydata.h"
#include "../inc/packetheader.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder2bytes.h"
#include "../inc/decoder4bytes.h"

#include <stdexcept>

namespace ris
{

    const Element PacketCarTelemetryData::CarTelemetry::SPEED{"SPEED"};
    const Element PacketCarTelemetryData::CarTelemetry::THROTTLE{"THROTTLE"};
    const Element PacketCarTelemetryData::CarTelemetry::STEER{"STEER"};
    const Element PacketCarTelemetryData::CarTelemetry::BRAKE{"BRAKE"};
    const Element PacketCarTelemetryData::CarTelemetry::CLUTCH{"CLUTCH"};
    const Element PacketCarTelemetryData::CarTelemetry::GEAR{"GEAR"};
    const Element PacketCarTelemetryData::CarTelemetry::ENGINERPM{"ENGINERPM"};
    const Element PacketCarTelemetryData::CarTelemetry::DRS{"DRS"};
    const Element PacketCarTelemetryData::CarTelemetry::REVLIGHTSPERCENT{"REVLIGHTSPERCENT"};
    const Element PacketCarTelemetryData::CarTelemetry::REVLIGHTSBITVALUE{"REVLIGHTSBITVALUE"};
    const Element PacketCarTelemetryData::CarTelemetry::BRAKESTEMPERATURE{"BRAKESTEMPERATURE"};
    const Element PacketCarTelemetryData::CarTelemetry::TYRESSURFACETEMPERATURE{"TYRESSURFACETEMPERATURE"};
    const Element PacketCarTelemetryData::CarTelemetry::TYRESINNERTEMPERATURE{"TYRESINNERTEMPERATURE"};
    const Element PacketCarTelemetryData::CarTelemetry::ENGINETEMPERATURE{"ENGINETEMPERATURE"};
    const Element PacketCarTelemetryData::CarTelemetry::TYRESPRESSURE{"TYRESPRESSURE"};
    const Element PacketCarTelemetryData::CarTelemetry::SURFACETYPE{"SURFACETYPE"};

    const Element PacketCarTelemetryData::CarTelemetry::CARTELEMETRY{"CARTELEMETRY"};

    Values getArrayOf4Values(const Bytes &bytes, Pos &pos, int size)
    {
        Values result;
        for (int i = 0; i < 4; ++i)
        {
            if (size == 1)
            {
            result.push_back(Decoder1Byte().decode(bytes, pos));
            }
            else if (size == 2)
            {
                result.push_back(Decoder2Bytes().decode(bytes, pos));
            }
            else if (size == 4)
            {
                result.push_back(Decoder4Bytes().decode(bytes, pos));
            }
            else
            {
                throw std::runtime_error("wrong size bytes");
            }
        }
        return result;
    }

    PacketCarTelemetryData::CarTelemetry::CarTelemetry(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(SPEED, Decoder2Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(THROTTLE, Decoder4Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(STEER, Decoder4Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(BRAKE, Decoder4Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(CLUTCH, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(GEAR, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(ENGINERPM, Decoder2Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(DRS, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(REVLIGHTSPERCENT, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(REVLIGHTSBITVALUE, Decoder2Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(BRAKESTEMPERATURE, getArrayOf4Values(bytes, pos, 2)));
        telemetry_.insert(std::pair<Element, Values>(TYRESSURFACETEMPERATURE, getArrayOf4Values(bytes, pos, 1)));
        telemetry_.insert(std::pair<Element, Values>(TYRESINNERTEMPERATURE, getArrayOf4Values(bytes, pos, 1)));
        telemetry_.insert(std::pair<Element, Values>(ENGINETEMPERATURE, Decoder2Bytes().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(TYRESPRESSURE, getArrayOf4Values(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(SURFACETYPE, getArrayOf4Values(bytes, pos, 1)));
    }

    const Element PacketCarTelemetryData::CarTelemetryData::MFDPANELINDEX{"MFDPANELINDEX"};
    const Element PacketCarTelemetryData::CarTelemetryData::MFDPANELINDEXSECONDARYPLAYER{"MFDPANELINDEXSECONDARYPLAYER"};
    const Element PacketCarTelemetryData::CarTelemetryData::SUGGESTEDGEAR{"SUGGESTEDGEAR"};

    const Element PacketCarTelemetryData::CarTelemetryData::CARTELEMETRYDATA{"CARTELEMETRYDATA"};

    PacketCarTelemetryData::CarTelemetryData::CarTelemetryData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(MFDPANELINDEX, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(MFDPANELINDEXSECONDARYPLAYER, Decoder1Byte().decode(bytes, pos)));
        telemetry_.insert(std::pair<Element, Values>(SUGGESTEDGEAR, Decoder1Byte().decode(bytes, pos)));
    }

    PacketCarTelemetryData::PacketCarTelemetryData(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, std::vector<Packet::Ptr>{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(CarTelemetry::CARTELEMETRY, getParticpantsCarTelemetry(bytes, pos));
        Packet::add(CarTelemetryData::CARTELEMETRYDATA, std::vector<Packet::Ptr>{std::make_shared<CarTelemetryData>(bytes, pos)});
    }

    std::vector<Packet::Ptr> PacketCarTelemetryData::getParticpantsCarTelemetry(const Bytes &bytes, Pos &pos)
    {
        std::vector<Packet::Ptr> result;
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            result.push_back(std::make_shared<CarTelemetry>(bytes, pos));
        }
        return result;
    }

} // namespace ris
