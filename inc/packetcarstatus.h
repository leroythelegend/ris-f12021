#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketCarStatus : public Packet
    {
    public:
        class CarStatusData : public SubPacket
        {
        public:
            inline static const Element TRACTIONCONTROL{"TRACTIONCONTROL"};
            inline static const Element ANTILOCKBRAKES{"ANTILOCKBRAKES"};
            inline static const Element FUELMIX{"FUELMIX"};
            inline static const Element FRONTBRAKEBIAS{"FRONTBRAKEBIAS"};
            inline static const Element PITLIMITERSTATUS{"PITLIMITERSTATUS"};
            inline static const Element FUELINTANK{"FUELINTANK"};
            inline static const Element FUELCAPACITY{"FUELCAPACITY"};
            inline static const Element FUELREMAININGLAPS{"FUELREMAININGLAPS"};
            inline static const Element MAXRPM{"MAXRPM"};
            inline static const Element IDLERPM{"IDLERPM"};
            inline static const Element MAXGEARS{"MAXGEARS"};
            inline static const Element DRSALLOWED{"DRSALLOWED"};
            inline static const Element DRSACTIVATIONDISTANCE{"DRSACTIVATIONDISTANCE"};
            inline static const Element ACTUALTYRECOMPOUND{"ACTUALTYRECOMPOUND"};
            inline static const Element VISUALTYRECOMPOUND{"VISUALTYRECOMPOUND"};
            inline static const Element TYRESAGELAPS{"TYRESAGELAPS"};
            inline static const Element VEHICLEFIAFLAGS{"VEHICLEFIAFLAGS"};
            inline static const Element ERSSTOREENERGY{"ERSSTOREENERGY"};
            inline static const Element ERSDEPLOYMODE{"ERSDEPLOYMODE"};
            inline static const Element ERSHARVESTEDTHISLAPMGUK{"ERSHARVESTEDTHISLAPMGUK"};
            inline static const Element ERSHARVESTEDTHISLAPMGUH{"ERSHARVESTEDTHISLAPMGUH"};
            inline static const Element ERSDEPLOYEDTHISLAP{"ERSDEPLOYEDTHISLAP"};
            inline static const Element NETWORKPAUSED{"NETWORKPAUSED"};

            inline static const Element CARSTATUSDATA{"CARSTATUSDATE"};

            CarStatusData(const Bytes &, Pos &);
            ~CarStatusData() override = default;
        };

        PacketCarStatus(const Bytes &);
        ~PacketCarStatus() override = default;

    private:
        Packet::SubPackets getParticpantsCarStatus(const Bytes &, Pos &);
    };

} // namespace ris
