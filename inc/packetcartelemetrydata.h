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
            inline static const Element SPEED{"SPEED"};
            inline static const Element THROTTLE{"THROTTLE"};
            inline static const Element STEER{"STEER"};
            inline static const Element BRAKE{"BRAKE"};
            inline static const Element CLUTCH{"CLUTCH"};
            inline static const Element GEAR{"GEAR"};
            inline static const Element ENGINERPM{"ENGINERPM"};
            inline static const Element DRS{"DRS"};
            inline static const Element REVLIGHTSPERCENT{"REVLIGHTSPERCENT"};
            inline static const Element REVLIGHTSBITVALUE{"REVLIGHTSBITVALUE"};
            inline static const Element BRAKESTEMPERATURE{"BRAKESTEMPERATURE"};
            inline static const Element TYRESSURFACETEMPERATURE{"TYRESSURFACETEMPERATURE"};
            inline static const Element TYRESINNERTEMPERATURE{"TYRESINNERTEMPERATURE"};
            inline static const Element ENGINETEMPERATURE{"ENGINETEMPERATURE"};
            inline static const Element TYRESPRESSURE{"TYRESPRESSURE"};
            inline static const Element SURFACETYPE{"SURFACETYPE"};

            inline static const Element CARTELEMETRY{"CARTELEMETRY"};

            CarTelemetry(const Bytes &, Pos &);
            ~CarTelemetry() override = default;
        };

        class CarTelemetryData : public SubPacket
        {
        public:
            inline static const Element MFDPANELINDEX{"MFDPANELINDEX"};
            inline static const Element MFDPANELINDEXSECONDARYPLAYER{"MFDPANELINDEXSECONDARYPLAYER"};
            inline static const Element SUGGESTEDGEAR{"SUGGESTEDGEAR"};

            inline static const Element CARTELEMETRYDATA{"CARTELEMETRYDATA"};

            CarTelemetryData(const Bytes &, Pos &);
            ~CarTelemetryData() override = default;
        };

        PacketCarTelemetryData(const Bytes &);
        ~PacketCarTelemetryData() override = default;

    private:
        Packet::SubPackets getParticpantsCarTelemetry(const Bytes &, Pos &);
    };

} // namespace ris
