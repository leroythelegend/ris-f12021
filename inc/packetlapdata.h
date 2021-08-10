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
            static const Element LASTLAPTIMEINMS;
            static const Element CURRENTLAPTIMEINMS;
            static const Element SECTOR1TIMEINMS;
            static const Element SECTOR2TIMEINMS;
            static const Element LAPDISTANCE;
            static const Element TOTALDISTANCE;
            static const Element SAFETYCARDELTA;
            static const Element CARPOSITION;
            static const Element CURRENTLAPNUM;
            static const Element PITSTATUS;
            static const Element NUMPITSTOPS;
            static const Element SECTOR;
            static const Element CURRENTLAPINVALID;
            static const Element PENALTIES;
            static const Element WARNINGS;
            static const Element NUMUNSERVEDDRIVETHROUGHPENS;
            static const Element NUMUNSERVEDSTOPGOPENS;
            static const Element GRIDPOSITION;
            static const Element DRIVERSTATUS;
            static const Element RESULTSTATUS;
            static const Element PITLANETIMERACTIVE;
            static const Element PITLANETIMEINLANEINMS;
            static const Element PITSTOPTIMERINMS;
            static const Element PITSTOPSHOULDSERVEPEN;

            static const Element LAPDATA;

            LapData(const Bytes &, Pos &);
            ~LapData() override = default;
        };

        PacketLapData(const Bytes &);
        ~PacketLapData() override = default;

    private:
        Packet::SubPackets getParticpantsLapData(const Bytes &, Pos &);
    };

} // namespace ris
