#pragma once

#include <memory>

#include "capturestate.h"
#include "state.h"

namespace ris
{
    class CaptureFrontEndState : public CaptureState
    {
    public:
        CaptureFrontEndState(Capture *, State::Ptr, ProcessLap::Ptr);
        virtual ~CaptureFrontEndState() = default;

        void sessionStarted() override;
    };
} // namespace ris
