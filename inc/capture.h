#pragma once

#include <memory>

#include "capturestate.h"

namespace ris
{
    class Capture
    {
    public:
        using Ptr = std::shared_ptr<Capture>;

        virtual ~Capture() = default;

        virtual void start() = 0;
    
        virtual void change(CaptureState::Ptr) = 0;
    };
} // namespace ris
