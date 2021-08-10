#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketLapData : public Packet
    {
    public:
        class LapData : public SubPacket
        {
        public:
            inline static const Element LASTLAPTIMEINMS{"LASTLAPTIMEINMS"};
            inline static const Element CURRENTLAPTIMEINMS{"CURRENTLAPTIMEINMS"};
            inline static const Element SECTOR1TIMEINMS{"SECTOR1TIMEINMS"};
            inline static const Element SECTOR2TIMEINMS{"SECTOR2TIMEINMS"};
            inline static const Element LAPDISTANCE{"LAPDISTANCE"};
            inline static const Element TOTALDISTANCE{"TOTALDISTANCE"};
            inline static const Element SAFETYCARDELTA{"SAFETYCARDELTA"};
            inline static const Element CARPOSITION{"CARPOSITION"};
            inline static const Element CURRENTLAPNUM{"CURRENTLAPNUM"};
            inline static const Element PITSTATUS{"PITSTATUS"};
            inline static const Element NUMPITSTOPS{"NUMPITSTOPS"};
            inline static const Element SECTOR{"SECTOR"};
            inline static const Element CURRENTLAPINVALID{"CURRENTLAPINVALID"};
            inline static const Element PENALTIES{"PENALTIES"};
            inline static const Element WARNINGS{"WARNINGS"};
            inline static const Element NUMUNSERVEDDRIVETHROUGHPENS{"NUMUNSERVEDDRIVETHROUGHPENS"};
            inline static const Element NUMUNSERVEDSTOPGOPENS{"NUMUNSERVEDSTOPGOPENS"};
            inline static const Element GRIDPOSITION{"GRIDPOSITION"};
            inline static const Element DRIVERSTATUS{"DRIVERSTATUS"};
            inline static const Element RESULTSTATUS{"RESULTSTATUS"};
            inline static const Element PITLANETIMERACTIVE{"PITLANETIMERACTIVE"};
            inline static const Element PITLANETIMEINLANEINMS{"PITLANETIMEINLANEINMS"};
            inline static const Element PITSTOPTIMERINMS{"PITSTOPTIMERINMS"};
            inline static const Element PITSTOPSHOULDSERVEPEN{"PITSTOPSHOULDSERVEPEN"};

            inline static const Element LAPDATA{"LAPDATA"};

            LapData(const Bytes &, Pos &);
            ~LapData() override = default;
        };

        PacketLapData(const Bytes &);
        ~PacketLapData() override = default;

    private:
        Packet::SubPackets getParticpantsLapData(const Bytes &, Pos &);
    };

} // namespace ris
