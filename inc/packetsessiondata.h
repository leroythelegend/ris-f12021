#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketSessionData : public Packet
    {
    public:
        class MarshalZone : public SubPacket
        {
        public:
            static const Element ZONESTART;
            static const Element ZONEFLAG;

            static const Element MARSHALZONE;

            MarshalZone(const Bytes &, Pos &);
            ~MarshalZone() override = default;
        };

        class WeatherForecastSample : public SubPacket
        {
        public:
            inline static const Element SESSIONTYPE{"SESSIONTYPE"};
            inline static const Element TIMEOFFSET{"TIMEOFFSET"};
            inline static const Element WEATHER{"WEATHER"};
            inline static const Element TRACKTEMPERATURE{"TRACKTEMPERATURE"};
            inline static const Element TRACKTEMPERATURECHANGE{"TRACKTEMPERATURECHANGE"};
            inline static const Element AIRTEMPERATURE{"AIRTEMPERATURE"};
            inline static const Element AIRTEMPERATURECHANGE{"AIRTEMPERATURECHANGE"};
            inline static const Element RAINPERCENTAGE{"RAINPERCENTAGE"};

            inline static const Element WEATHERFORECASTSAMPLE{"WEATHERFORECASTSAMPLE"};

            WeatherForecastSample(const Bytes &, Pos &);
            ~WeatherForecastSample() override = default;
        };

        class SessionData : public SubPacket
        {
        public:
            inline static const Element WEATHER{"WEATHER"};
            inline static const Element TRACKTEMPERATURE{"TRACKTEMPERATURE"};
            inline static const Element AIRTEMPERATURE{"AIRTEMPERATURE"};
            inline static const Element TOTALLAPS{"TOTALLAPS"};
            inline static const Element TRACKLENGTH{"TRACKLENGTH"};
            inline static const Element SESSIONTYPE{"SESSIONTYPE"};
            inline static const Element TRACKID{"TRACKID"};
            inline static const Element FORMULA{"FORMULA"};
            inline static const Element SESSIONTIMELEFT{"SESSIONTIMELEFT"};
            inline static const Element SESSIONDURATION{"SESSIONDURATION"};
            inline static const Element PITSPEEDLIMIT{"PITSPEEDLIMIT"};
            inline static const Element GAMEPAUSED{"GAMEPAUSED"};
            inline static const Element ISSPECTATING{"ISSPECTATING"};
            inline static const Element SPECTATORCARINDEX{"SPECTATORCARINDEX"};
            inline static const Element SLIPRONATIVESUPPORT{"SLIPRONATIVESUPPORT"};
            inline static const Element NUMMARSHALZONES{"NUMMARSHALZONES"};
            inline static const Element MARSHALZONE{"MARSHALZONE"};
            inline static const Element SAFETYCARSTATUS{"SAFETYCARSTATUS"};
            inline static const Element NETWORKGAME{"NETWORKGAME"};
            inline static const Element NUMWEATHERFORECASTSAMPLES{"NUMWEATHERFORECASTSAMPLES"};
            inline static const Element FORECASTACCURACY{"FORECASTACCURACY"};
            inline static const Element AIDIFFICULTY{"AIDIFFICULTY"};
            inline static const Element SEASONLINKIDENTIFIER{"SEASONLINKIDENTIFIER"};
            inline static const Element WEEKENDLINKIDENTIFIER{"WEEKENDLINKIDENTIFIER"};
            inline static const Element SESSIONLINKIDENTIFIER{"SESSIONLINKIDENTIFIER"};
            inline static const Element PITSTOPWINDOWIDEALLAP{"PITSTOPWINDOWIDEALLAP"};
            inline static const Element PITSTOPWINDOWLATESTLAP{"PITSTOPWINDOWLATESTLAP"};
            inline static const Element PITSTOPREJOINPOSITION{"PITSTOPREJOINPOSITION"};
            inline static const Element STEERINGASSIST{"STEERINGASSIST"};
            inline static const Element BRAKINGASSIST{"BRAKINGASSIST"};
            inline static const Element GEARBOXASSIST{"GEARBOXASSIST"};
            inline static const Element PITASSIST{"PITASSIST"};
            inline static const Element PITRELEASEASSIST{"PITRELEASEASSIST"};
            inline static const Element ERSASSIST{"ERSASSIST"};
            inline static const Element DRSASSIST{"DRSASSIST"};
            inline static const Element DYNAMICRACINGLINE{"DYNAMICRACINGLINE"};
            inline static const Element DYNAMICRACINGLINETYPE{"DYNAMICRACINGLINETYPE"};

            inline static const Element SESSIONDATA{"SESSIONDATA"};

            SessionData(const Bytes &, Pos &);
            ~SessionData() override = default;

            SubPackets marshalzones;
            SubPackets weatherforecastsamples;
        };

        PacketSessionData(const Bytes &);
        ~PacketSessionData() override = default;
    };

} // namespace ris
