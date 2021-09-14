#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketCarDamageData : public Packet
    {
    public:
        class CarDamageData : public SubPacket
        {
        public:
            inline static const Element TYRESWEAR{"TYRESWEAR"};
            inline static const Element TYRESDAMAGE{"TYRESDAMAGE"};
            inline static const Element BRAKESDAMAGE{"BRAKESDAMAGE"};
            inline static const Element FRONTLEFTWINGDAMAGE{"FRONTLEFTWINGDAMAGE"};
            inline static const Element FRONTRIGHTWINGDAMAGE{"FRONTRIGHTWINGDAMAGE"};
            inline static const Element REARWINGDAMAGE{"REARWINGDAMAGE"};
            inline static const Element FLOORDAMAGE{"FLOORDAMAGE"};
            inline static const Element DIFFUSERDAMAGE{"DIFFUSERDAMAGE"};
            inline static const Element SIDEPODDAMAGE{"SIDEPODDAMAGE"};
            inline static const Element DRSFAULT{"DRSFAULT"};
            inline static const Element GEARBOXDAMAGE{"GEARBOXDAMAGE"};
            inline static const Element ENGINEDAMAGE{"ENGINEDAMAGE"};
            inline static const Element ENGINEMGUHWEAR{"ENGINEMGUHWEAR"};
            inline static const Element ENGINEESWEAR{"ENGINEESWEAR"};
            inline static const Element ENGINECEWEAR{"ENGINECEWEAR"};
            inline static const Element ENGINEICEWEAR{"ENGINEICEWEAR"};
            inline static const Element ENGINEMGUKWEAR{"ENGINEMGUKWEAR"};
            inline static const Element ENGINETCWEAR{"ENGINETCWEAR"};

            inline static const Element CARDAMAGEDATA{"CARDAMAGEDATA"};

            CarDamageData(const Bytes &, Pos &);
            ~CarDamageData() override = default;
        };

        PacketCarDamageData(const Bytes &);
        ~PacketCarDamageData() override = default;
    };

} // namespace ris
