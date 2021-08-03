#include "../inc/packetcarstatus.h"
#include "../inc/packetheader.h"

#include "../inc/decoder1byte.h"
#include "../inc/decoder2bytes.h"
#include "../inc/decoder4bytes.h"

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
        telemetry_.insert(std::pair<Element, Values>(TRACTIONCONTROL, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(ANTILOCKBRAKES, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(FUELMIX, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(FRONTBRAKEBIAS, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(PITLIMITERSTATUS, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(FUELINTANK, {Decoder4Bytes().decode(bytes, pos), 3}));
        telemetry_.insert(std::pair<Element, Values>(FUELCAPACITY, {Decoder4Bytes().decode(bytes, pos), 3}));
        telemetry_.insert(std::pair<Element, Values>(FUELREMAININGLAPS, {Decoder4Bytes().decode(bytes, pos), 3}));
        telemetry_.insert(std::pair<Element, Values>(MAXRPM, {Decoder2Bytes().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(IDLERPM, {Decoder2Bytes().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(MAXGEARS, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(DRSALLOWED, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(DRSACTIVATIONDISTANCE, {Decoder2Bytes().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(ACTUALTYRECOMPOUND, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(VISUALTYRECOMPOUND, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(TYRESAGELAPS, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(VEHICLEFIAFLAGS, {Decoder1Byte().decode(bytes, pos), 2}));
        telemetry_.insert(std::pair<Element, Values>(ERSSTOREENERGY, {Decoder4Bytes().decode(bytes, pos), 3}));
        telemetry_.insert(std::pair<Element, Values>(ERSDEPLOYMODE, {Decoder1Byte().decode(bytes, pos), 1}));
        telemetry_.insert(std::pair<Element, Values>(ERSHARVESTEDTHISLAPMGUK, {Decoder4Bytes().decode(bytes, pos), 3}));
        telemetry_.insert(std::pair<Element, Values>(ERSHARVESTEDTHISLAPMGUH, {Decoder4Bytes().decode(bytes, pos), 3}));
        telemetry_.insert(std::pair<Element, Values>(ERSDEPLOYEDTHISLAP, {Decoder4Bytes().decode(bytes, pos), 3}));
        telemetry_.insert(std::pair<Element, Values>(NETWORKPAUSED, {Decoder1Byte().decode(bytes, pos), 1}));
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
