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
        
        marshalzones = Packet::createSubPackets<WeatherForecastSample>(bytes, pos, 21);

        telemetry_.insert(std::pair<Element, Values>(SAFETYCARSTATUS, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NETWORKGAME, {DecoderUInt8().decode(bytes, pos)}));
        telemetry_.insert(std::pair<Element, Values>(NUMWEATHERFORECASTSAMPLES, {DecoderUInt8().decode(bytes, pos)}));
        
        weatherforecastsamples = Packet::createSubPackets<WeatherForecastSample>(bytes, pos, 56);

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
