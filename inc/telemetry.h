#pragma once

#include "packet.h"

#include <vector>
#include <memory>

namespace ris
{
    struct Telemetry
    {
        double currentlap;
        double time;
        double distance;
        std::vector<SubPacket::Ptr> packets;
    };

    using Telemetries = std::unique_ptr<std::vector<Telemetry>>;
} // namespace ris
