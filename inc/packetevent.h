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

        static const Element EVENTSTRINGCODE;

        PacketEvent(const Bytes &, Pos &);
        ~PacketEvent() override = default;
    };

} // namespace ris
