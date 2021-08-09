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
            static const Element WORLDPOSITIONX;
            static const Element WORLDPOSITIONY;
            static const Element WORLDPOSITIONZ;
            static const Element WORLDVELOCITYX;
            static const Element WORLDVELOCITYY;
            static const Element WORLDVELOCITYZ;
            static const Element WORLDFORWARDDIRX;
            static const Element WORLDFORWARDDIRY;
            static const Element WORLDFORWARDDIRZ;
            static const Element WORLDRIGHTDIRX;
            static const Element WORLDRIGHTDIRY;
            static const Element WORLDRIGHTDIRZ;
            static const Element GFORCELATERAL;
            static const Element GFORCELONGITUDINAL;
            static const Element GFORCEVERTICAL;
            static const Element YAW;
            static const Element PITCH;
            static const Element ROLL;

            static const Element CARMOTIONDATA;

            CarMotionData(const Bytes &, Pos &);
            ~CarMotionData() override = default;
        };

        class MotionData : public SubPacket
        {
        public:
            static const Element SUSPENSIONPOSITION;
            static const Element SUSPENSIONVELOCITY;
            static const Element SUSPENSIONACCELERATION;
            static const Element WHEELSPEED;
            static const Element WHEELSLIP;
            static const Element LOCALVELOCITYX;
            static const Element LOCALVELOCITYY;
            static const Element LOCALVELOCITYZ;
            static const Element ANGULARVELOCITYX;
            static const Element ANGULARVELOCITYY;
            static const Element ANGULARVELOCITYZ;
            static const Element ANGULARACCELERATIONX;
            static const Element ANGULARACCELERATIONY;
            static const Element ANGULARACCELERATIONZ;
            static const Element FRONTWHEELSANGLE;

            static const Element MOTIONDATA;

            MotionData(const Bytes &, Pos &);
            ~MotionData() override = default;
        };

        PacketMotionData(const Bytes &);
        ~PacketMotionData() override = default;

    private:
        Packet::SubPackets getParticpantsCarMotionData(const Bytes &, Pos &);
    };

} // namespace ris
