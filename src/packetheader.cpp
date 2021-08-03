#include "../inc/packetheader.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder2bytes.h"
#include "../inc/decoder4bytes.h"
#include "../inc/decoder8bytes.h"

namespace ris
{
    const Element PacketHeader::PACKETFORMAT{"PACKETFORMAT"};
    const Element PacketHeader::GAMEMAJORVERSION{"GAMEMAJORVERSION"};
    const Element PacketHeader::GAMEMINORVERSION{"GAMEMINORVERSION"};
    const Element PacketHeader::PACKETVERSION{"PACKETVERSION"};
    const Element PacketHeader::PACKETID{"PACKETID"};
    const Element PacketHeader::SESSIONUID{"SESSIONUID"};
    const Element PacketHeader::SESSIONTIME{"SESSIONTIME"};
    const Element PacketHeader::FRAMEIDENTIFIER{"FRAMEIDENTIFIER"};
    const Element PacketHeader::PLAYERCARINDEX{"PLAYERCARINDEX"};
    const Element PacketHeader::SECONDARYPLAYERCARINDEX{"SECONDARYPLAYERCARINDEX"};

    const Element PacketHeader::PACKETHEADER{"PACKETHEADER"};

    PacketHeader::PacketHeader(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PACKETFORMAT, {Decoder2Bytes().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(GAMEMAJORVERSION, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(GAMEMINORVERSION, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(PACKETVERSION, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(PACKETID, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(SESSIONUID, {Decoder8Bytes().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(SESSIONTIME, {Decoder4Bytes().decode(bytes, pos), 3}));
        telemetry_.insert(std::pair<Element, Values>(FRAMEIDENTIFIER, {Decoder4Bytes().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(PLAYERCARINDEX, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(SECONDARYPLAYERCARINDEX, {Decoder1Byte().decode(bytes, pos), 1}));
    }
} // namespace ris
