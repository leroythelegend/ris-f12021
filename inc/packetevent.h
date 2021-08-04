#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketEvent : public Packet
    {
    public:
        class Buttons : public SubPacket
        {
        public:
            static const Element BUTTONSTATUS;
            static const Element BUTTONS;

            Buttons(const Bytes &, Pos &);
            ~Buttons() override = default;
        };

        class Flashback : public SubPacket
        {
        public:
            static const Element FLASHBACKFRAMEIDENTIFIER;
            static const Element FLASHBACKSESSIONTIME;
            static const Element FLASHBACK;

            Flashback(const Bytes &, Pos &);
            ~Flashback() override = default;
        };

        class Event : public SubPacket
        {
        public:
            static const Element EVENTSTRINGCODE;
            static const Element EVENT;

            Event(const Bytes &, Pos &);
            ~Event() override = default;
        };

        PacketEvent(const Bytes &);
        ~PacketEvent() override = default;

    private:
        void addCorrectEventDetailsToPacket(const Bytes &, Pos &);
    };

} // namespace ris
