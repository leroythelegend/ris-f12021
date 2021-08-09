#include "../inc/packetmotiondata.h"
#include "../inc/packetheader.h"

#include "../inc/decoderuint8.h"
#include "../inc/decoderint8.h"
#include "../inc/decoderuint16.h"
#include "../inc/decoderint16.h"
#include "../inc/decoderuint32.h"
#include "../inc/decoderfloat.h"

#include <stdexcept>

namespace ris
{

    const Element PacketMotionData::CarMotionData::WORLDPOSITIONX{"WORLDPOSITIONX"};
    const Element PacketMotionData::CarMotionData::WORLDPOSITIONY{"WORLDPOSITIONY"};
    const Element PacketMotionData::CarMotionData::WORLDPOSITIONZ{"WORLDPOSITIONZ"};
    const Element PacketMotionData::CarMotionData::WORLDVELOCITYX{"WORLDVELOCITYX"};
    const Element PacketMotionData::CarMotionData::WORLDVELOCITYY{"WORLDVELOCITYY"};
    const Element PacketMotionData::CarMotionData::WORLDVELOCITYZ{"WORLDVELOCITYZ"};
    const Element PacketMotionData::CarMotionData::WORLDFORWARDDIRX{"WORLDFORWARDDIRX"};
    const Element PacketMotionData::CarMotionData::WORLDFORWARDDIRY{"WORLDFORWARDDIRY"};
    const Element PacketMotionData::CarMotionData::WORLDFORWARDDIRZ{"WORLDFORWARDDIRZ"};
    const Element PacketMotionData::CarMotionData::WORLDRIGHTDIRX{"WORLDRIGHTDIRX"};
    const Element PacketMotionData::CarMotionData::WORLDRIGHTDIRY{"WORLDRIGHTDIRY"};
    const Element PacketMotionData::CarMotionData::WORLDRIGHTDIRZ{"WORLDRIGHTDIRZ"};
    const Element PacketMotionData::CarMotionData::GFORCELATERAL{"GFORCELATERAL"};
    const Element PacketMotionData::CarMotionData::GFORCELONGITUDINAL{"GFORCELONGITUDINAL"};
    const Element PacketMotionData::CarMotionData::GFORCEVERTICAL{"GFORCEVERTICAL"};
    const Element PacketMotionData::CarMotionData::YAW{"YAW"};
    const Element PacketMotionData::CarMotionData::PITCH{"PITCH"};
    const Element PacketMotionData::CarMotionData::ROLL{"ROLL"};

    const Element PacketMotionData::CarMotionData::CARMOTIONDATA{"CARMOTIONDATA"};

    PacketMotionData::CarMotionData::CarMotionData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(WORLDPOSITIONX, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDPOSITIONY, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDPOSITIONZ, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDVELOCITYX, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDVELOCITYY, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDVELOCITYZ, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDFORWARDDIRX, {DecoderInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDFORWARDDIRY, {DecoderInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDFORWARDDIRZ, {DecoderInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDRIGHTDIRX, {DecoderInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDRIGHTDIRY, {DecoderInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WORLDRIGHTDIRZ, {DecoderInt16().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GFORCELATERAL, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GFORCELONGITUDINAL, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GFORCEVERTICAL, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(YAW, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITCH, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ROLL, {DecoderFloat().decode(bytes, pos)}));
    }

    const Element PacketMotionData::MotionData::SUSPENSIONPOSITION{"SUSPENSIONPOSITION"};
    const Element PacketMotionData::MotionData::SUSPENSIONVELOCITY{"SUSPENSIONVELOCITY"};
    const Element PacketMotionData::MotionData::SUSPENSIONACCELERATION{"SUSPENSIONACCELERATION"};
    const Element PacketMotionData::MotionData::WHEELSPEED{"WHEELSPEED"};
    const Element PacketMotionData::MotionData::WHEELSLIP{"WHEELSLIP"};
    const Element PacketMotionData::MotionData::LOCALVELOCITYX{"LOCALVELOCITYX"};
    const Element PacketMotionData::MotionData::LOCALVELOCITYY{"LOCALVELOCITYY"};
    const Element PacketMotionData::MotionData::LOCALVELOCITYZ{"LOCALVELOCITYZ"};
    const Element PacketMotionData::MotionData::ANGULARVELOCITYX{"ANGULARVELOCITYX"};
    const Element PacketMotionData::MotionData::ANGULARVELOCITYY{"ANGULARVELOCITYY"};
    const Element PacketMotionData::MotionData::ANGULARVELOCITYZ{"ANGULARVELOCITYZ"};
    const Element PacketMotionData::MotionData::ANGULARACCELERATIONX{"ANGULARACCELERATIONX"};
    const Element PacketMotionData::MotionData::ANGULARACCELERATIONY{"ANGULARACCELERATIONY"};
    const Element PacketMotionData::MotionData::ANGULARACCELERATIONZ{"ANGULARACCELERATIONZ"};
    const Element PacketMotionData::MotionData::FRONTWHEELSANGLE{"FRONTWHEELSANGLE"};

    PacketMotionData::MotionData::MotionData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(SUSPENSIONPOSITION, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(SUSPENSIONVELOCITY, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(SUSPENSIONACCELERATION, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(WHEELSPEED, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(WHEELSLIP, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(LOCALVELOCITYX, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(LOCALVELOCITYY, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(LOCALVELOCITYZ, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(ANGULARVELOCITYX, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(ANGULARVELOCITYY, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(ANGULARVELOCITYZ, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(ANGULARACCELERATIONX, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(ANGULARACCELERATIONY, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(ANGULARACCELERATIONZ, DecoderFloat().decode(bytes, pos, 4)));
        telemetry_.insert(std::pair<Element, Values>(FRONTWHEELSANGLE, DecoderFloat().decode(bytes, pos, 4)));
    }

    PacketMotionData::PacketMotionData(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        Packet::add(CarMotionData::CARMOTIONDATA, getParticpantsCarMotionData(bytes, pos));
        Packet::add(MotionData::MOTIONDATA, SubPackets{std::make_shared<MotionData>(bytes, pos)});
    }

    Packet::SubPackets PacketMotionData::getParticpantsCarMotionData(const Bytes &bytes, Pos &pos)
    {
        SubPackets result;
        for (int i = 0; i < NUMBEROFPARTICIPANTS; ++i)
        {
            result.push_back(std::make_shared<CarMotionData>(bytes, pos));
        }
        return result;
    }

} // namespace ris
