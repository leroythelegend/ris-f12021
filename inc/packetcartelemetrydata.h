#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketCarTelemetryData : public Packet
    {
    public:
        class CarTelemetry : public SubPacket
        {
        public:
            static const Element SPEED;
            static const Element THROTTLE;
            static const Element STEER;
            static const Element BRAKE;
            static const Element CLUTCH;
            static const Element GEAR;
            static const Element ENGINERPM;
            static const Element DRS;
            static const Element REVLIGHTSPERCENT;
            static const Element REVLIGHTSBITVALUE;
            static const Element BRAKESTEMPERATURE;
            static const Element TYRESSURFACETEMPERATURE;
            static const Element TYRESINNERTEMPERATURE;
            static const Element ENGINETEMPERATURE;
            static const Element TYRESPRESSURE;
            static const Element SURFACETYPE;

            static const Element CARTELEMETRY;

            CarTelemetry(const Bytes &, Pos &);
            ~CarTelemetry() override = default;
        };

        class CarTelemetryData : public SubPacket
        {
        public:
            static const Element MFDPANELINDEX;
            static const Element MFDPANELINDEXSECONDARYPLAYER;
            static const Element SUGGESTEDGEAR;

            static const Element CARTELEMETRYDATA;

            CarTelemetryData(const Bytes &, Pos &);
            ~CarTelemetryData() override = default;
        };

        PacketCarTelemetryData(const Bytes &);
        ~PacketCarTelemetryData() override = default;

    private:
        Packet::SubPackets getParticpantsCarTelemetry(const Bytes &, Pos &);
    };

} // namespace ris
