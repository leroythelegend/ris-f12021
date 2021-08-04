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

    const Element PacketCarStatus::CarStatusData::TRACTIONCONTROL{"TRACTIONCONTROL"};
    const Element PacketCarStatus::CarStatusData::ANTILOCKBRAKES{"ANTILOCKBRAKES"};
    const Element PacketCarStatus::CarStatusData::FUELMIX{"FUELMIX"};
    const Element PacketCarStatus::CarStatusData::FRONTBRAKEBIAS{"FRONTBRAKEBIAS"};
    const Element PacketCarStatus::CarStatusData::PITLIMITERSTATUS{"PITLIMITERSTATUS"};
    const Element PacketCarStatus::CarStatusData::FUELINTANK{"FUELINTANK"};
    const Element PacketCarStatus::CarStatusData::FUELCAPACITY{"FUELCAPACITY"};
    const Element PacketCarStatus::CarStatusData::FUELREMAININGLAPS{"FUELREMAININGLAPS"};
    const Element PacketCarStatus::CarStatusData::MAXRPM{"MAXRPM"};
    const Element PacketCarStatus::CarStatusData::IDLERPM{"IDLERPM"};
    const Element PacketCarStatus::CarStatusData::MAXGEARS{"MAXGEARS"};
    const Element PacketCarStatus::CarStatusData::DRSALLOWED{"DRSALLOWED"};
    const Element PacketCarStatus::CarStatusData::DRSACTIVATIONDISTANCE{"DRSACTIVATIONDISTANCE"};
    const Element PacketCarStatus::CarStatusData::ACTUALTYRECOMPOUND{"ACTUALTYRECOMPOUND"};
    const Element PacketCarStatus::CarStatusData::VISUALTYRECOMPOUND{"VISUALTYRECOMPOUND"};
    const Element PacketCarStatus::CarStatusData::TYRESAGELAPS{"TYRESAGELAPS"};
    const Element PacketCarStatus::CarStatusData::VEHICLEFIAFLAGS{"VEHICLEFIAFLAGS"};
    const Element PacketCarStatus::CarStatusData::ERSSTOREENERGY{"ERSSTOREENERGY"};
    const Element PacketCarStatus::CarStatusData::ERSDEPLOYMODE{"ERSDEPLOYMODE"};
    const Element PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUK{"ERSHARVESTEDTHISLAPMGUK"};
    const Element PacketCarStatus::CarStatusData::ERSHARVESTEDTHISLAPMGUH{"ERSHARVESTEDTHISLAPMGUH"};
    const Element PacketCarStatus::CarStatusData::ERSDEPLOYEDTHISLAP{"ERSDEPLOYEDTHISLAP"};
    const Element PacketCarStatus::CarStatusData::NETWORKPAUSED{"NETWORKPAUSED"};

    const Element PacketCarStatus::CarStatusData::CARSTATUSDATA{"CARSTATUSDATE"};

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
        Packet::add(PacketHeader::PACKETHEADER, std::vector<Packet::Ptr>{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(CarStatusData::CARSTATUSDATA, getParticpantsCarStatus(bytes, pos));
    }

    std::vector<Packet::Ptr> PacketCarStatus::getParticpantsCarStatus(const Bytes &bytes, Pos &pos)
    {
        std::vector<Packet::Ptr> result;
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            result.push_back(std::make_shared<CarStatusData>(bytes, pos));
        }
        return result;
    }

} // namespace ris
