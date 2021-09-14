#include "../inc/packetcarstatus.h"
#include "../inc/packetheader.h"

#include "../inc/decoderuint8.h"
#include "../inc/decoderint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderfloat.h"

namespace ris
{
    PacketCarStatus::CarStatusData::CarStatusData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(TRACTIONCONTROL, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ANTILOCKBRAKES, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(FUELMIX, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(FRONTBRAKEBIAS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITLIMITERSTATUS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(FUELINTANK, {DecoderFloat().decode(bytes, pos), }));
        telemetry_.insert(std::pair<Element, Values>(FUELCAPACITY, {DecoderFloat().decode(bytes, pos), }));
        telemetry_.insert(std::pair<Element, Values>(FUELREMAININGLAPS, {DecoderFloat().decode(bytes, pos), }));
        telemetry_.insert(std::pair<Element, Values>(MAXRPM, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(IDLERPM, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(MAXGEARS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(DRSALLOWED, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(DRSACTIVATIONDISTANCE, {DecoderUInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ACTUALTYRECOMPOUND, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(VISUALTYRECOMPOUND, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TYRESAGELAPS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(VEHICLEFIAFLAGS, {DecoderInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ERSSTOREENERGY, {DecoderFloat().decode(bytes, pos), }));
        telemetry_.insert(std::pair<Element, Values>(ERSDEPLOYMODE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ERSHARVESTEDTHISLAPMGUK, {DecoderFloat().decode(bytes, pos), }));
        telemetry_.insert(std::pair<Element, Values>(ERSHARVESTEDTHISLAPMGUH, {DecoderFloat().decode(bytes, pos), }));
        telemetry_.insert(std::pair<Element, Values>(ERSDEPLOYEDTHISLAP, {DecoderFloat().decode(bytes, pos), }));
        telemetry_.insert(std::pair<Element, Values>(NETWORKPAUSED, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketCarStatus::PacketCarStatus(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(CarStatusData::CARSTATUSDATA, createSubPackets<CarStatusData>(bytes, pos, NUMBEROFPARTICIPANTS));
    }
} // namespace ris
