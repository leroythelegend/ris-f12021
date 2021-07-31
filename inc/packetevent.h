#pragma once

#include "packetcomposite.h"

namespace ris
{
    class PacketEvent : public PacketComposite
    {
    public:
        using Ptr = std::shared_ptr<Packet>;
        using Unit = Packet::Unit;

        PacketEvent(const Bytes &, Pos &);
        ~PacketEvent() override = default;
    };

} // namespace ris
