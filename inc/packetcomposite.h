#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketComposite : public Packet
    {
    public:
        using Ptr = std::shared_ptr<PacketComposite>;

        ~PacketComposite() override = default;

        Values value(const Element &) const override;

        PacketComposite() = default;
    };

} // namespace ris
