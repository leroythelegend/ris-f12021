#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketFinalClassificationData : public Packet
    {
    public:
        class FinalClassificationData : public SubPacket
        {
        public:
            inline static const Element POSITION{"POSITION"};
            inline static const Element NUMLAPS{"NUMLAPS"};
            inline static const Element GRIDPOSITION{"GRIDPOSITION"};
            inline static const Element POINTS{"POINTS"};
            inline static const Element NUMPITSTOPS{"NUMPITSTOPS"};
            inline static const Element RESULTSTATUS{"RESULTSTATUS"};
            inline static const Element BESTLAPTIMEINMS{"BESTLAPTIMEINMS"};
            inline static const Element TOTALRACETIME{"TOTALRACETIME"};
            inline static const Element PENALTIESTIME{"PENALTIESTIME"};
            inline static const Element NUMPENALTIES{"NUMPENALTIES"};
            inline static const Element NUMTYRESTINTS{"NUMTYRESTINTS"};
            inline static const Element TYRESTINTSACTUAL{"TYRESTINTSACTUAL"};
            inline static const Element TYRESTINTSVISUAL{"TYRESTINTSVISUAL"};

            inline static const Element FINALCLASSIFICATIONDATA{"FINALCLASSIFICATIONDATA"};

            FinalClassificationData(const Bytes &, Pos &);
            ~FinalClassificationData() override = default;
        };

        class NumCars : public SubPacket
        {
        public:
            inline static const Element NUMCLASSIFICATIONCARS{"NUMACTIVECARS"};

            inline static const Element NUMCARS{"NUMCARS"};

            NumCars(const Bytes &, Pos &);
            ~NumCars() override = default;
        };

        PacketFinalClassificationData(const Bytes &);
        ~PacketFinalClassificationData() override = default;
    };

} // namespace ris
