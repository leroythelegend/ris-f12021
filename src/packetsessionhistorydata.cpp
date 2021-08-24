#include "../inc/packetsessionhistorydata.h"
#include "../inc/packetheader.h"

#include "../inc/decoderuint8.h"
#include "../inc/decoderint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderfloat.h"
#include "../inc/decoderdouble.h"

namespace ris
{
    PacketSessionHistoryData::LapHistoryData::LapHistoryData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(LAPTIMEINMS, {DecoderUInt32().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SECTOR1TIMEINMS, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SECTOR2TIMEINMS, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SECTOR3TIMEINMS, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(LAPVALIDBITFLAGS, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketSessionHistoryData::TyreStintHistoryData::TyreStintHistoryData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(ENDLAP, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TYREACTUALCOMPOUND, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TYREVISUALCOMPOUND, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketSessionHistoryData::SessionHistoryData::SessionHistoryData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(CARIDX, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMLAPS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMTYRESTINTS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(BESTLAPTIMELAPNUM, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(BESTSECTOR1LAPNUM, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(BESTSECTOR2LAPNUM, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(BESTSECTOR3LAPNUM, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketSessionHistoryData::PacketSessionHistoryData(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(SessionHistoryData::SESSIONHISTORYDATA, SubPackets{std::make_shared<SessionHistoryData>(bytes, pos)});
        Packet::add(LapHistoryData::LAPHISTORYDATA, createSubPackets<LapHistoryData>(bytes, pos, MAXLAPHISTORY));
        Packet::add(TyreStintHistoryData::TYRESTINTHISTORYDATA, createSubPackets<TyreStintHistoryData>(bytes, pos, MAXTYRESTINTHISTORY));
    }
} // namespace ris
