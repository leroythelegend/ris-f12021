#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketComposite : public Packet
    {
    public:
        using Ptr = std::shared_ptr<PacketComposite>;
        using Unit = Packet::Unit;

        ~PacketComposite() override = default;

        Elements element(const Unit &) const override;

        PacketComposite() = default;
    };

} // namespace ris
