#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketMotionData : public Packet
    {
    public:
        class CarMotionData : public SubPacket
        {
        public:
            inline static const Element WORLDPOSITIONX{"WORLDPOSITIONX"};
            inline static const Element WORLDPOSITIONY{"WORLDPOSITIONY"};
            inline static const Element WORLDPOSITIONZ{"WORLDPOSITIONZ"};
            inline static const Element WORLDVELOCITYX{"WORLDVELOCITYX"};
            inline static const Element WORLDVELOCITYY{"WORLDVELOCITYY"};
            inline static const Element WORLDVELOCITYZ{"WORLDVELOCITYZ"};
            inline static const Element WORLDFORWARDDIRX{"WORLDFORWARDDIRX"};
            inline static const Element WORLDFORWARDDIRY{"WORLDFORWARDDIRY"};
            inline static const Element WORLDFORWARDDIRZ{"WORLDFORWARDDIRZ"};
            inline static const Element WORLDRIGHTDIRX{"WORLDRIGHTDIRX"};
            inline static const Element WORLDRIGHTDIRY{"WORLDRIGHTDIRY"};
            inline static const Element WORLDRIGHTDIRZ{"WORLDRIGHTDIRZ"};
            inline static const Element GFORCELATERAL{"GFORCELATERAL"};
            inline static const Element GFORCELONGITUDINAL{"GFORCELONGITUDINAL"};
            inline static const Element GFORCEVERTICAL{"GFORCEVERTICAL"};
            inline static const Element YAW{"YAW"};
            inline static const Element PITCH{"PITCH"};
            inline static const Element ROLL{"ROLL"};

            inline static const Element CARMOTIONDATA{"CARMOTIONDATA"};

            CarMotionData(const Bytes &, Pos &);
            ~CarMotionData() override = default;
        };

        class MotionData : public SubPacket
        {
        public:
            inline static const Element SUSPENSIONPOSITION{"SUSPENSIONPOSITION"};
            inline static const Element SUSPENSIONVELOCITY{"SUSPENSIONVELOCITY"};
            inline static const Element SUSPENSIONACCELERATION{"SUSPENSIONACCELERATION"};
            inline static const Element WHEELSPEED{"WHEELSPEED"};
            inline static const Element WHEELSLIP{"WHEELSLIP"};
            inline static const Element LOCALVELOCITYX{"LOCALVELOCITYX"};
            inline static const Element LOCALVELOCITYY{"LOCALVELOCITYY"};
            inline static const Element LOCALVELOCITYZ{"LOCALVELOCITYZ"};
            inline static const Element ANGULARVELOCITYX{"ANGULARVELOCITYX"};
            inline static const Element ANGULARVELOCITYY{"ANGULARVELOCITYY"};
            inline static const Element ANGULARVELOCITYZ{"ANGULARVELOCITYZ"};
            inline static const Element ANGULARACCELERATIONX{"ANGULARACCELERATIONX"};
            inline static const Element ANGULARACCELERATIONY{"ANGULARACCELERATIONY"};
            inline static const Element ANGULARACCELERATIONZ{"ANGULARACCELERATIONZ"};
            inline static const Element FRONTWHEELSANGLE{"FRONTWHEELSANGLE"};

            inline static const Element MOTIONDATA{"MOTIONDATA"};

            MotionData(const Bytes &, Pos &);
            ~MotionData() override = default;
        };

        PacketMotionData(const Bytes &);
        ~PacketMotionData() override = default;

    private:
        Packet::SubPackets getParticpantsCarMotionData(const Bytes &, Pos &);
    };

} // namespace ris
