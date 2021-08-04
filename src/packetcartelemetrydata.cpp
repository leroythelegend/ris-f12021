#include "../inc/packetcartelemetrydata.h"
#include "../inc/packetheader.h"

#include "../inc/decoderuint8.h"
#include "../inc/decoderint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderfloat.h"


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

    PacketCarTelemetryData::CarTelemetry::CarTelemetry(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(SPEED, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(THROTTLE, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(STEER, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(BRAKE, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(CLUTCH, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GEAR, {DecoderInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ENGINERPM, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(DRS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(REVLIGHTSPERCENT, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(REVLIGHTSBITVALUE, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(BRAKESTEMPERATURE, DecoderUInt16().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(TYRESSURFACETEMPERATURE, DecoderUInt8().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(TYRESINNERTEMPERATURE, DecoderUInt8().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(ENGINETEMPERATURE, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TYRESPRESSURE, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(SURFACETYPE, DecoderUInt8().decode(bytes, pos, 4)));
    }

    const Element PacketCarTelemetryData::CarTelemetryData::MFDPANELINDEX{"MFDPANELINDEX"};
    const Element PacketCarTelemetryData::CarTelemetryData::MFDPANELINDEXSECONDARYPLAYER{"MFDPANELINDEXSECONDARYPLAYER"};
    const Element PacketCarTelemetryData::CarTelemetryData::SUGGESTEDGEAR{"SUGGESTEDGEAR"};

    const Element PacketCarTelemetryData::CarTelemetryData::CARTELEMETRYDATA{"CARTELEMETRYDATA"};

    PacketCarTelemetryData::CarTelemetryData::CarTelemetryData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(MFDPANELINDEX, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(MFDPANELINDEXSECONDARYPLAYER, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SUGGESTEDGEAR, {DecoderInt8().decode(bytes, pos)}));
    }

    PacketCarTelemetryData::PacketCarTelemetryData(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(CarTelemetry::CARTELEMETRY, getParticpantsCarTelemetry(bytes, pos));
        Packet::add(CarTelemetryData::CARTELEMETRYDATA, SubPackets{std::make_shared<CarTelemetryData>(bytes, pos)});
    }

    Packet::SubPackets PacketCarTelemetryData::getParticpantsCarTelemetry(const Bytes &bytes, Pos &pos)
    {
        SubPackets result;
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            result.push_back(std::make_shared<CarTelemetry>(bytes, pos));
        }
        return result;
    }

} // namespace ris
