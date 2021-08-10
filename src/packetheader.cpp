#include "../inc/packetheader.h"

#include "../inc/decoderuint8.h"
#include "../inc/decoderint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderuint64.h"
#include "../inc/decoderfloat.h"

namespace ris
{
    PacketHeader::PacketHeader(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(PACKETFORMAT, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GAMEMAJORVERSION, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GAMEMINORVERSION, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PACKETVERSION, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PACKETID, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SESSIONUID, {DecoderUInt64().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SESSIONTIME, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(FRAMEIDENTIFIER, {DecoderUInt32().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PLAYERCARINDEX, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SECONDARYPLAYERCARINDEX, {DecoderUInt8().decode(bytes, pos)}));
    }
} // namespace ris
