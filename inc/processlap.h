#pragma once

#include <memory>

#include "definitions.h"

namespace ris
{

    class ProcessLap
    {
    public:
        using Ptr = std::shared_ptr<ProcessLap>;

        virtual ~ProcessLap() = default;

        virtual void process(Packets) = 0;
        virtual void record() = 0;
        virtual void reset() = 0;
    };

} // namespace rix
