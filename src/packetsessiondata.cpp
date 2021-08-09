#include "../inc/packetsessiondata.h"
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
    const Element PacketSessionData::MarshalZone::ZONESTART{"ZONESTART"};
    const Element PacketSessionData::MarshalZone::ZONEFLAG{"ZONEFLAG"};

    const Element PacketSessionData::MarshalZone::MARSHALZONE{"MARSHALZONE"};

    PacketSessionData::MarshalZone::MarshalZone(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(ZONESTART, {DecoderFloat().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ZONEFLAG, {DecoderInt8().decode(bytes, pos)}));
    }

            const Element PacketSessionData::WeatherForecastSample::SESSIONTYPE{"SESSIONTYPE"};
            const Element PacketSessionData::WeatherForecastSample::TIMEOFFSET{"TIMEOFFSET"};
            const Element PacketSessionData::WeatherForecastSample::WEATHER{"WEATHER"};
            const Element PacketSessionData::WeatherForecastSample::TRACKTEMPERATURE{"TRACKTEMPERATURE"};
            const Element PacketSessionData::WeatherForecastSample::TRACKTEMPERATURECHANGE{"TRACKTEMPERATURECHANGE"};
            const Element PacketSessionData::WeatherForecastSample::AIRTEMPERATURE{"AIRTEMPERATURE"};
            const Element PacketSessionData::WeatherForecastSample::AIRTEMPERATURECHANGE{"AIRTEMPERATURECHANGE"};
            const Element PacketSessionData::WeatherForecastSample::RAINPERCENTAGE{"RAINPERCENTAGE"};

            const Element PacketSessionData::WeatherForecastSample::WEATHERFORECASTSAMPLE{"WEATHERFORECASTSAMPLE"};

    PacketSessionData::WeatherForecastSample::WeatherForecastSample(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(SESSIONTYPE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TIMEOFFSET, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WEATHER, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TRACKTEMPERATURE, {DecoderInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TRACKTEMPERATURECHANGE, {DecoderInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(AIRTEMPERATURE, {DecoderInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(AIRTEMPERATURECHANGE, {DecoderInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(RAINPERCENTAGE, {DecoderUInt8().decode(bytes, pos)}));

    }
    
            const Element PacketSessionData::SessionData::TRACKTEMPERATURE{"TRACKTEMPERATURE"};
            const Element PacketSessionData::SessionData::AIRTEMPERATURE{"AIRTEMPERATURE"};
            const Element PacketSessionData::SessionData::TOTALLAPS{"TOTALLAPS"};
            const Element PacketSessionData::SessionData::TRACKLENGTH{"TRACKLENGTH"};
            const Element PacketSessionData::SessionData::SESSIONTYPE{"SESSIONTYPE"};
            const Element PacketSessionData::SessionData::TRACKID{"TRACKID"};
            const Element PacketSessionData::SessionData::FORMULA{"FORMULA"};
            const Element PacketSessionData::SessionData::SESSIONTIMELEFT{"SESSIONTIMELEFT"};
            const Element PacketSessionData::SessionData::SESSIONDURATION{"SESSIONDURATION"};
            const Element PacketSessionData::SessionData::PITSPEEDLIMIT{"PITSPEEDLIMIT"};
            const Element PacketSessionData::SessionData::GAMEPAUSED{"GAMEPAUSED"};
            const Element PacketSessionData::SessionData::ISSPECTATING{"ISSPECTATING"};
            const Element PacketSessionData::SessionData::SPECTATORCARINDEX{"SPECTATORCARINDEX"};
            const Element PacketSessionData::SessionData::SLIPRONATIVESUPPORT{"SLIPRONATIVESUPPORT"};
            const Element PacketSessionData::SessionData::NUMMARSHALZONES{"NUMMARSHALZONES"};
            const Element PacketSessionData::SessionData::SAFETYCARSTATUS{"SAFETYCARSTATUS"};
            const Element PacketSessionData::SessionData::NETWORKGAME{"NETWORKGAME"};
            const Element PacketSessionData::SessionData::NUMWEATHERFORECASTSAMPLES{"NUMWEATHERFORECASTSAMPLES"};
            const Element PacketSessionData::SessionData::FORECASTACCURACY{"FORECASTACCURACY"};
            const Element PacketSessionData::SessionData::AIDIFFICULTY{"AIDIFFICULTY"};
            const Element PacketSessionData::SessionData::SEASONLINKIDENTIFIER{"SEASONLINKIDENTIFIER"};
            const Element PacketSessionData::SessionData::WEEKENDLINKIDENTIFIER{"WEEKENDLINKIDENTIFIER"};
            const Element PacketSessionData::SessionData::SESSIONLINKIDENTIFIER{"SESSIONLINKIDENTIFIER"};
            const Element PacketSessionData::SessionData::PITSTOPWINDOWIDEALLAP{"PITSTOPWINDOWIDEALLAP"};
            const Element PacketSessionData::SessionData::PITSTOPWINDOWLATESTLAP{"PITSTOPWINDOWLATESTLAP"};
            const Element PacketSessionData::SessionData::PITSTOPREJOINPOSITION{"PITSTOPREJOINPOSITION"};
            const Element PacketSessionData::SessionData::STEERINGASSIST{"STEERINGASSIST"};
            const Element PacketSessionData::SessionData::BRAKINGASSIST{"BRAKINGASSIST"};
            const Element PacketSessionData::SessionData::GEARBOXASSIST{"GEARBOXASSIST"};
            const Element PacketSessionData::SessionData::PITASSIST{"PITASSIST"};
            const Element PacketSessionData::SessionData::PITRELEASEASSIST{"PITRELEASEASSIST"};
            const Element PacketSessionData::SessionData::ERSASSIST{"ERSASSIST"};
            const Element PacketSessionData::SessionData::DRSASSIST{"DRSASSIST"};
            const Element PacketSessionData::SessionData::DYNAMICRACINGLINE{"DYNAMICRACINGLINE"};
            const Element PacketSessionData::SessionData::DYNAMICRACINGLINETYPE{"DYNAMICRACINGLINETYPE"};

            const Element PacketSessionData::SessionData::SESSIONDATA{"SESSIONDATA"};

    PacketSessionData::SessionData::SessionData(const Bytes &bytes, Pos &pos)
    {
        telemetry_.insert(std::pair<Element, Values>(TRACKTEMPERATURE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(AIRTEMPERATURE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TOTALLAPS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TRACKLENGTH, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SESSIONTYPE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(TRACKID, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(FORMULA, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SESSIONTIMELEFT, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SESSIONDURATION, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITSPEEDLIMIT, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GAMEPAUSED, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ISSPECTATING, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SPECTATORCARINDEX, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SLIPRONATIVESUPPORT, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMMARSHALZONES, {DecoderUInt8().decode(bytes, pos)}));
        for (int i = 0; i < 21; ++i)
        {
            marshalzones.push_back(std::make_shared<MarshalZone>(bytes, pos));
        }
        telemetry_.insert(std::pair<Element, Values>(SAFETYCARSTATUS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NETWORKGAME, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMWEATHERFORECASTSAMPLES, {DecoderUInt8().decode(bytes, pos)}));
        for (int i = 0; i < 56; ++i)
        {
            weatherforecastsamples.push_back(std::make_shared<WeatherForecastSample>(bytes, pos));
        }
        telemetry_.insert(std::pair<Element, Values>(FORECASTACCURACY, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SEASONLINKIDENTIFIER, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(WEEKENDLINKIDENTIFIER, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(SESSIONLINKIDENTIFIER, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITSTOPWINDOWIDEALLAP, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITSTOPWINDOWLATESTLAP, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITSTOPREJOINPOSITION, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(STEERINGASSIST, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(BRAKINGASSIST, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(GEARBOXASSIST, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITASSIST, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(PITRELEASEASSIST, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(ERSASSIST, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(DRSASSIST, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(DYNAMICRACINGLINE, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(DYNAMICRACINGLINETYPE, {DecoderUInt8().decode(bytes, pos)}));
    }

    PacketSessionData::PacketSessionData(const Bytes &bytes)
    {
        unsigned int pos = 0;
        Packet::add(PacketHeader::PACKETHEADER, SubPackets{std::make_shared<PacketHeader>(bytes, pos)});
        std::shared_ptr<SessionData> session = std::make_shared<SessionData>(bytes, pos);
        SubPackets sessions = {session};
        Packet::add(SessionData::SESSIONDATA, sessions);
        Packet::add(MarshalZone::MARSHALZONE, session->marshalzones);
        Packet::add(WeatherForecastSample::WEATHERFORECASTSAMPLE, session->weatherforecastsamples);
    }

} // namespace ris
