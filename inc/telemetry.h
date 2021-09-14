#pragma once

#include "packet.h"

#include <vector>

namespace ris
{
    struct Telemetry
    {
        double currentlap;
        double time;
        double distance;
        std::vector<SubPacket::Ptr> packets;
    };

    using Telemetries = std::vector<Telemetry>;
} // namespace ris
