#include "../inc/packetlapdata.h"
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
    PacketLapData::LapData::LapData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(LASTLAPTIMEINMS, {DecoderUInt32().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(CURRENTLAPTIMEINMS, {DecoderUInt32().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SECTOR1TIMEINMS, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SECTOR2TIMEINMS, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(LAPDISTANCE, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TOTALDISTANCE, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SAFETYCARDELTA, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(CARPOSITION, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(CURRENTLAPNUM, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITSTATUS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMPITSTOPS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SECTOR, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(CURRENTLAPINVALID, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PENALTIES, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WARNINGS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMUNSERVEDDRIVETHROUGHPENS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMUNSERVEDSTOPGOPENS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GRIDPOSITION, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(DRIVERSTATUS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(RESULTSTATUS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITLANETIMERACTIVE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITLANETIMEINLANEINMS, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITSTOPTIMERINMS, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITSTOPSHOULDSERVEPEN, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketLapData::PacketLapData(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(LapData::LAPDATA, getParticpantsLapData(bytes, pos));
    }

    Packet::SubPackets PacketLapData::getParticpantsLapData(const Bytes &bytes, Pos &pos)
    {
        SubPackets result;
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            result.push_back(std::make_shared<LapData>(bytes, pos));
        }
        return result;
    }

} // namespace ris
