#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketEvent : public Packet
    {
    public:
        class Buttons : public Packet
        {
        public:
            static const Element BUTTONSTATUS;
            static const Element BUTTONS;

            Buttons(const Bytes &, Pos &pos);
            ~Buttons() override = default;
        };

        class Flashback : public Packet
        {
        public:
            static const Element FLASHBACKFRAMEIDENTIFIER;
            static const Element FLASHBACKSESSIONTIME;
            static const Element FLASHBACK;

            Flashback(const Bytes &, Pos &pos);
            ~Flashback() override = default;
        };

        static const Element EVENTSTRINGCODE;

        PacketEvent(const Bytes &, Pos &);
        ~PacketEvent() override = default;

    private:
        void addEventStringCodeToTelemetry(const Bytes &, Pos &);
        void addCorrectEventDetailsToPacket(const Bytes &, Pos &);
    };

} // namespace ris
