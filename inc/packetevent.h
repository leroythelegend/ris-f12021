#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketEvent : public Packet
    {
    public:
        class FastestLap : public SubPacket
        {
        public:
            inline static const Element VEHICLEIDX{"VEHICLEIDX"};
            inline static const Element LAPTIME{"LAPTIME"};
            inline static const Element FASTESTLAP{"FATESTLAPS"};

            FastestLap(const Bytes &, Pos &);
            ~FastestLap() override = default;
        };

        class Retirement : public SubPacket
        {
        public:
            inline static const Element VEHICLEIDX{"VEHICLEIDX"};
            inline static const Element RETIREMENT{"RETIREMENT"};

            Retirement(const Bytes &, Pos &);
            ~Retirement() override = default;
        };

        class TeamMateInPits : public SubPacket
        {
        public:
            inline static const Element VEHICLEIDX{"VEHICLEIDX"};
            inline static const Element TEAMMATEINPITS{"TEAMMATEINPITS"};

            TeamMateInPits(const Bytes &, Pos &);
            ~TeamMateInPits() override = default;
        };

        class RaceWinner : public SubPacket
        {
        public:
            inline static const Element VEHICLEIDX{"VEHICLEIDX"};
            inline static const Element RACEWINNER{"RACEWINNER"};

            RaceWinner(const Bytes &, Pos &);
            ~RaceWinner() override = default;
        };

        class Penalty : public SubPacket
        {
        public:
            inline static const Element PENALTYTYPE{"PENALTYTYPE"};
            inline static const Element INFRINGEMENTTYPE{"INFRINGEMENTTYPE"};
            inline static const Element VEHICLEIDX{"VEHICLEIDX"};
            inline static const Element OTHERVEHICLEIDX{"OTHERVEHICLEIDX"};
            inline static const Element TIME{"TIME"};
            inline static const Element LAPNUM{"LAPNUM"};
            inline static const Element PLACESGAINED{"PLACESGAINED"};
            inline static const Element PENALTY{"PENALTY"};

            Penalty(const Bytes &, Pos &);
            ~Penalty() override = default;
        };

        class SpeedTrap : public SubPacket
        {
        public:
            inline static const Element VEHICLEIDX{"VEHICLEIDX"};
            inline static const Element SPEED{"SPEED"};
            inline static const Element OVERALLFASTESTINSESSION{"OVERALLFASTESTINSESSION"};
            inline static const Element DRIVERFASTESTINSESSION{"DRIVERFASTESTINSESSION"};

            inline static const Element SPEEDTRAP{"SPEEDTRAP"};

            SpeedTrap(const Bytes &, Pos &);
            ~SpeedTrap() override = default;
        };

        class StartLights : public SubPacket
        {
        public:
            inline static const Element NUMLIGHTS{"NUMLIGHTS"};
            inline static const Element STARTLIGHTS{"STARTLIGHTS"};

            StartLights(const Bytes &, Pos &);
            ~StartLights() override = default;
        };

        class DriveThroughPenaltyServed : public SubPacket
        {
        public:
            inline static const Element VEHICLEIDX{"VEHICLEIDX"};
            inline static const Element DRIVETHROUGHPENALTYSERVED{"DRIVETHROUGHPENALTYSERVED"};

            DriveThroughPenaltyServed(const Bytes &, Pos &);
            ~DriveThroughPenaltyServed() override = default;
        };

        class StopGoPenaltyServed : public SubPacket
        {
        public:
            inline static const Element VEHICLEIDX{"VEHICLEIDX"};
            inline static const Element STOPGOPENALTYSERVED{"STOPGOPENALTYSERVED"};

            StopGoPenaltyServed(const Bytes &, Pos &);
            ~StopGoPenaltyServed() override = default;
        };

        class Buttons : public SubPacket
        {
        public:
            inline static const Element BUTTONSTATUS{"BUTTONSTATUS"};
            inline static const Element BUTTONS{"BUTTONS"};

            Buttons(const Bytes &, Pos &);
            ~Buttons() override = default;
        };

        class Flashback : public SubPacket
        {
        public:
            inline static const Element FLASHBACKFRAMEIDENTIFIER{"FLASHBACKFRAMEIDENTIFIER"};
            inline static const Element FLASHBACKSESSIONTIME{"FLASHBACKSESSIONTIME"};
            inline static const Element FLASHBACK{"FLASHBACK"};

            Flashback(const Bytes &, Pos &);
            ~Flashback() override = default;
        };

        class Event : public SubPacket
        {
        public:
            inline static const Element EVENTSTRINGCODE{"EVENTSTRINGCODE"};
            inline static const Element EVENT{"EVENT"};

            Event(const Bytes &, Pos &);
            ~Event() override = default;
        };

        PacketEvent(const Bytes &);
        ~PacketEvent() override = default;

    private:
        void addCorrectEventDetailsToPacket(const Bytes &, Pos &);
    };

} // namespace ris
