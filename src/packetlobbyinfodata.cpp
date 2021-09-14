#include "../inc/packetlobbyinfodata.h"
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
    PacketLobbyInfoData::LobbyInfoData::LobbyInfoData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(AICONTROLLED, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TEAMID, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NATIONALITY, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NAME, DecoderUInt8().decode(bytes, pos, 48)));
        telemetry_.insert(std::pair<Element, Values>(CARNUMBER, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(READYSTATUS, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketLobbyInfoData::NumPlayers::NumPlayers(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(NUMLOBBYPLAYERS, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketLobbyInfoData::PacketLobbyInfoData(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(NumPlayers::NUMPLAYERS, SubPackets{std::make_shared<NumPlayers>(bytes, pos)});
        Packet::add(LobbyInfoData::LOBBYINFODATA, createSubPackets<LobbyInfoData>(bytes, pos, NUMBEROFPARTICIPANTS));
    }
} // namespace ris
