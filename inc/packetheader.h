#pragma once

#include <memory>
#include <map>

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketHeader : public Packet
    {
    public:
        using Unit = Packet::Unit;

        PacketHeader(const Bytes &, Pos &);
        ~PacketHeader() override = default;
    };

} // namespace ris
