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
            static const Element SESSIONTYPE;
            static const Element TIMEOFFSET;
            static const Element WEATHER;
            static const Element TRACKTEMPERATURE;
            static const Element TRACKTEMPERATURECHANGE;
            static const Element AIRTEMPERATURE;
            static const Element AIRTEMPERATURECHANGE;
            static const Element RAINPERCENTAGE;

            static const Element WEATHERFORECASTSAMPLE;

            WeatherForecastSample(const Bytes &, Pos &);
            ~WeatherForecastSample() override = default;
        };

        class SessionData : public SubPacket
        {
        public:
            static const Element TRACKTEMPERATURE;
            static const Element AIRTEMPERATURE;
            static const Element TOTALLAPS;
            static const Element TRACKLENGTH;
            static const Element SESSIONTYPE;
            static const Element TRACKID;
            static const Element FORMULA;
            static const Element SESSIONTIMELEFT;
            static const Element SESSIONDURATION;
            static const Element PITSPEEDLIMIT;
            static const Element GAMEPAUSED;
            static const Element ISSPECTATING;
            static const Element SPECTATORCARINDEX;
            static const Element SLIPRONATIVESUPPORT;
            static const Element NUMMARSHALZONES;
            static const Element MARSHALZONES;
            static const Element SAFETYCARSTATUS;
            static const Element NETWORKGAME;
            static const Element NUMWEATHERFORECASTSAMPLES;
            static const Element WEATHERFORECASTSAMPLES;
            static const Element FORECASTACCURACY;
            static const Element AIDIFFICULTY;
            static const Element SEASONLINKIDENTIFIER;
            static const Element WEEKENDLINKIDENTIFIER;
            static const Element SESSIONLINKIDENTIFIER;
            static const Element PITSTOPWINDOWIDEALLAP;
            static const Element PITSTOPWINDOWLATESTLAP;
            static const Element PITSTOPREJOINPOSITION;
            static const Element STEERINGASSIST;
            static const Element BRAKINGASSIST;
            static const Element GEARBOXASSIST;
            static const Element PITASSIST;
            static const Element PITRELEASEASSIST;
            static const Element ERSASSIST;
            static const Element DRSASSIST;
            static const Element DYNAMICRACINGLINE;
            static const Element DYNAMICRACINGLINETYPE;

            static const Element SESSIONDATA;

            SessionData(const Bytes &, Pos &);
            ~SessionData() override = default;

            SubPackets marshalzones;
            SubPackets weatherforecastsamples;
        };

        PacketSessionData(const Bytes &);
        ~PacketSessionData() override = default;
    };

} // namespace ris
