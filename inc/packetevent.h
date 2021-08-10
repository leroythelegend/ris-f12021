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
            inline static const Element BUTTONSTATUS{"BUTTONSTATUS"};
            inline static const Element BUTTONS{"BUTTONS"};

            Buttons(const Bytes &, Pos &);
            ~Buttons() override = default;
        };

        class Flashback : public SubPacket
        {
        public:
            inline static const Element FLASHBACKFRAMEIDENTIFIER{"FLASHBACKFRAMEIDENTIFIER"};
            inline static const Element FLASHBACKSESSIONTIME{"FLASHBACKSESSIONTIME"};
            inline static const Element FLASHBACK{"FLASHBACK"};

            Flashback(const Bytes &, Pos &);
            ~Flashback() override = default;
        };

        class Event : public SubPacket
        {
        public:
            inline static const Element EVENTSTRINGCODE{"EVENTSTRINGCODE"};
            inline static const Element EVENT{"EVENT"};

            Event(const Bytes &, Pos &);
            ~Event() override = default;
        };

        PacketEvent(const Bytes &);
        ~PacketEvent() override = default;

    private:
        void addCorrectEventDetailsToPacket(const Bytes &, Pos &);
    };

} // namespace ris
