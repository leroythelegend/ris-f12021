#include "../inc/packetfinalclassificationdata.h"
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
    PacketFinalClassificationData::FinalClassificationData::FinalClassificationData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(POSITION, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMLAPS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GRIDPOSITION, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(POINTS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMPITSTOPS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(RESULTSTATUS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(BESTLAPTIMEINMS, {DecoderUInt32().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TOTALRACETIME, {DecoderDouble().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PENALTIESTIME, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMPENALTIES, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMTYRESTINTS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TYRESTINTSACTUAL, DecoderUInt8().decode(bytes, pos, 8)));
        telemetry_.insert(std::pair<Element, Values>(TYRESTINTSVISUAL, DecoderUInt8().decode(bytes, pos, 8)));
    }

    PacketFinalClassificationData::NumCars::NumCars(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(NUMCLASSIFICATIONCARS, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketFinalClassificationData::PacketFinalClassificationData(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(NumCars::NUMCARS, SubPackets{std::make_shared<NumCars>(bytes, pos)});
        Packet::add(FinalClassificationData::FINALCLASSIFICATIONDATA, createSubPackets<FinalClassificationData>(bytes, pos, NUMBEROFPARTICIPANTS));
    }
} // namespace ris
