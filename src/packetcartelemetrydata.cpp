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
        Packet::add(CarTelemetry::CARTELEMETRY, createSubPackets<CarTelemetry>(bytes, pos, NUMBEROFPARTICIPANTS));
        Packet::add(CarTelemetryData::CARTELEMETRYDATA, SubPackets{std::make_shared<CarTelemetryData>(bytes, pos)});
    }
} // namespace ris
