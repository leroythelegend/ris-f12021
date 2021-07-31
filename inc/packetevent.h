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
            inline static const Element BUTTONSTATUS{"BUTTONSTATUS"};

            Buttons(const Bytes &bytes, Pos &pos);
            ~Buttons() override = default;
        };

        inline static const Element EVENTSTRINGCODE{"EVENTSTRINGCODE"};

        PacketEvent(const Bytes &, Pos &);
        ~PacketEvent() override = default;
    };

} // namespace ris
