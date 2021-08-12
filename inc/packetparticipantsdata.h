#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketParticipantsData : public Packet
    {
    public:
        class ParticipantData : public SubPacket
        {
        public:
            inline static const Element AICONTROLLED{"AICONTROLLED"};
            inline static const Element DRIVERID{"DRIVERID"};
            inline static const Element NETWORKID{"NETWORKID"};
            inline static const Element TEAMID{"TEAMID"};
            inline static const Element MYTEAM{"MYTEAM"};
            inline static const Element RACENUMBER{"RACENUMBER"};
            inline static const Element NATIONALITY{"NATIONALITY"};
            inline static const Element NAME{"NAME"};
            inline static const Element YOURTELEMETRY{"YOURTELEMETRY"};

            inline static const Element PARTICIPANTDATA{"PARTICIPANTDATA"};

            ParticipantData(const Bytes &, Pos &);
            ~ParticipantData() override = default;
        };

        class ActiveCars : public SubPacket
        {
        public:
            inline static const Element NUMACTIVECARS{"NUMACTIVECARS"};

            inline static const Element ACTIVECARS{"ACTIVECARS"};

            ActiveCars(const Bytes &, Pos &);
            ~ActiveCars() override = default;
        };

        PacketParticipantsData(const Bytes &);
        ~PacketParticipantsData() override = default;
    };

} // namespace ris
