#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketCarSetupData : public Packet
    {
    public:
        class CarSetupData : public SubPacket
        {
        public:
            inline static const Element FRONTWING{"FRONTWING"};
            inline static const Element REARWING{"REARWING"};
            inline static const Element ONTHROTTLE{"ONTHROTTLE"};
            inline static const Element OFFTHROTTLE{"OFFTHROTTLE"};
            inline static const Element FRONTCAMBER{"FRONTCAMBER"};
            inline static const Element REARCAMBER{"REARCAMBER"};
            inline static const Element FRONTTOE{"FRONTTOE"};
            inline static const Element REARTOE{"REARTOE"};
            inline static const Element FRONTSUSPENSION{"FRONTSUSPENSION"};
            inline static const Element REARSUSPENSION{"REARSUSPENSION"};
            inline static const Element FRONTANTIROLLBAR{"FRONTANTIROLLBAR"};
            inline static const Element REARANTIROLLBAR{"REARANTIROLLBAR"};
            inline static const Element FRONTSUSPENSIONHEIGHT{"FRONTSUSPENSIONHEIGHT"};
            inline static const Element REARSUSPENSIONHEIGHT{"REARSUSPENSIONHEIGHT"};
            inline static const Element BRAKEPRESSURE{"BRAKEPRESSURE"};
            inline static const Element BRAKEBIAS{"BRAKEBIAS"};
            inline static const Element REARLEFTTYREPRESSURE{"REARLEFTTYREPRESSURE"};
            inline static const Element REARRIGHTTYREPRESSURE{"REARRIGHTTYREPRESSURE"};
            inline static const Element FRONTLEFTTYREPRESSURE{"FRONTLEFTTYREPRESSURE"};
            inline static const Element FRONTRIGHTTYREPRESSURE{"FRONTRIGHTTYREPRESSURE"};
            inline static const Element BALLAST{"BALLAST"};
            inline static const Element FUELLOAD{"FUELLOAD"};

            inline static const Element CARSETUPDATA{"CARSETUPDATE"};

            CarSetupData(const Bytes &, Pos &);
            ~CarSetupData() override = default;
        };

        PacketCarSetupData(const Bytes &);
        ~PacketCarSetupData() override = default;
    };

} // namespace ris
