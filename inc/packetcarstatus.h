#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketCarStatus : public Packet
    {
    public:

        class CarStatusData : public Packet
        {
        public:
            static const Element TRACTIONCONTROL;
            static const Element ANTILOCKBRAKES;
            static const Element FUELMIX;
            static const Element FRONTBRAKEBIAS;
            static const Element PITLIMITERSTATUS;
            static const Element FUELINTANK;
            static const Element FUELCAPACITY;
            static const Element FUELREMAININGLAPS;
            static const Element MAXRPM;
            static const Element IDLERPM;
            static const Element MAXGEARS;
            static const Element DRSALLOWED;
            static const Element DRSACTIVATIONDISTANCE;
            static const Element ACTUALTYRECOMPOUND;
            static const Element VISUALTYRECOMPOUND;
            static const Element TYRESAGELAPS;
            static const Element VEHICLEFIAFLAGS;
            static const Element ERSSTOREENERGY;
            static const Element ERSDEPLOYMODE;
            static const Element ERSHARVESTEDTHISLAPMGUK;
            static const Element ERSHARVESTEDTHISLAPMGUH;
            static const Element ERSDEPLOYEDTHISLAP;
            static const Element NETWORKPAUSED;

            static const Element CARSTATUSDATA;

            CarStatusData(const Bytes &, Pos &);
            ~CarStatusData() override = default;
        };

        PacketCarStatus(const Bytes &, Pos &);
        ~PacketCarStatus() override = default;
    };

} // namespace ris
