#pragma once

#include "packetcomposite.h"

namespace ris
{
    class PacketEvent : public PacketComposite
    {
    public:
        class Buttons : public Packet
        {
        public:
            static const Element BUTTONSTATUS;

            Buttons(const Bytes &, Pos &pos);
            ~Buttons() override = default;
        };

        static const Element EVENTSTRINGCODE;

        PacketEvent(const Bytes &, Pos &);
        ~PacketEvent() override = default;
    };

} // namespace ris
