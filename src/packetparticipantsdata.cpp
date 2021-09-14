#include "../inc/packetparticipantsdata.h"
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
    PacketParticipantsData::ParticipantData::ParticipantData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(AICONTROLLED, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(DRIVERID, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NETWORKID, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TEAMID, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(MYTEAM, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(RACENUMBER, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NATIONALITY, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NAME, DecoderUInt8().decode(bytes, pos, 48)));
        telemetry_.insert(std::pair<Element, Values>(YOURTELEMETRY, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketParticipantsData::ActiveCars::ActiveCars(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(NUMACTIVECARS, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketParticipantsData::PacketParticipantsData(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(ActiveCars::ACTIVECARS, SubPackets{std::make_shared<ActiveCars>(bytes, pos)});
        Packet::add(ParticipantData::PARTICIPANTDATA, createSubPackets<ParticipantData>(bytes, pos, NUMBEROFPARTICIPANTS));
    }
} // namespace ris
