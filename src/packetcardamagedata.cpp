#include "../inc/packetcardamagedata.h"
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
    PacketCarDamageData::CarDamageData::CarDamageData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(TYRESWEAR, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(TYRESDAMAGE, DecoderUInt8().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(BRAKESDAMAGE, DecoderUInt8().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(FRONTLEFTWINGDAMAGE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(FRONTRIGHTWINGDAMAGE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(REARWINGDAMAGE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(FLOORDAMAGE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(DIFFUSERDAMAGE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SIDEPODDAMAGE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(DRSFAULT, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GEARBOXDAMAGE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ENGINEDAMAGE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ENGINEMGUHWEAR, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ENGINEESWEAR, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ENGINECEWEAR, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ENGINEICEWEAR, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ENGINEMGUKWEAR, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ENGINETCWEAR, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketCarDamageData::PacketCarDamageData(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(CarDamageData::CARDAMAGEDATA, createSubPackets<CarDamageData>(bytes, pos, NUMBEROFPARTICIPANTS));
    }
} // namespace ris
