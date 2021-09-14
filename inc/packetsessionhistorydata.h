#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketSessionHistoryData : public Packet
    {
    public:
        class LapHistoryData : public SubPacket
        {
        public:
            inline static const Element LAPTIMEINMS{"LAPTIMEINMS"};
            inline static const Element SECTOR1TIMEINMS{"SECTOR1TIMEINMS"};
            inline static const Element SECTOR2TIMEINMS{"SECTOR2TIMEINMS"};
            inline static const Element SECTOR3TIMEINMS{"SECTOR3TIMEINMS"};
            inline static const Element LAPVALIDBITFLAGS{"LAPVALIDBITFLAGS"};

            inline static const Element LAPHISTORYDATA{"LAPHISTORYDATA"};

            LapHistoryData(const Bytes &, Pos &);
            ~LapHistoryData() override = default;
        };

        class TyreStintHistoryData : public SubPacket
        {
        public:
            inline static const Element ENDLAP{"ENDLAP"};
            inline static const Element TYREACTUALCOMPOUND{"TYREACTUALCOMPOUND"};
            inline static const Element TYREVISUALCOMPOUND{"TYREVISUALCOMPOUND"};

            inline static const Element TYRESTINTHISTORYDATA{"TYRESTINTHISTORYDATA"};

            TyreStintHistoryData(const Bytes &, Pos &);
            ~TyreStintHistoryData() override = default;
        };

        class SessionHistoryData : public SubPacket
        {
        public:
            inline static const Element CARIDX{"CARIDX"};
            inline static const Element NUMLAPS{"NUMLAPS"};
            inline static const Element NUMTYRESTINTS{"NUMTYRESTINTS"};
            inline static const Element BESTLAPTIMELAPNUM{"BESTLAPTIMELAPNUM"};
            inline static const Element BESTSECTOR1LAPNUM{"BESTSECTOR1LAPNUM"};
            inline static const Element BESTSECTOR2LAPNUM{"BESTSECTOR2LAPNUM"};
            inline static const Element BESTSECTOR3LAPNUM{"BESTSECTOR3LAPNUM"};

            inline static const Element SESSIONHISTORYDATA{"SESSIONHISTORYDATA"};

            SessionHistoryData(const Bytes &, Pos &);
            ~SessionHistoryData() override = default;
        };

        PacketSessionHistoryData(const Bytes &);
        ~PacketSessionHistoryData() override = default;
    };

} // namespace ris
