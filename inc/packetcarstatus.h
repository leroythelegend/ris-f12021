#pragma once

#include "packet.h"
#include "definitions.h"

namespace ris
{
    class PacketCarStatus : public Packet
    {
    public:
        // class CarStatusData : public Packet
        // {
        // public:
        //     CarStatusData(const Bytes &, Pos &pos);
        //     ~CarStatusData() override = default;
        // };

        PacketCarStatus(const Bytes &, Pos &);
        ~PacketCarStatus() override = default;
    };

} // namespace ris
