#pragma once

#include <memory>

#include "telemetry.h"

namespace ris
{

    class Record
    {
    public:
        using Ptr = std::shared_ptr<Record>;

        virtual ~Record() = default;

        virtual void record(Telemetries &) = 0;
    };

} // namespace rix
