#pragma once

#include <memory>

#include "capturestate.h"
#include "state.h"

namespace ris
{
    class CapturePitState : public CaptureState
    {
    public:
        CapturePitState(Capture *, State::Ptr, ProcessLap::Ptr);
        virtual ~CapturePitState() = default;

        void sessionEnded() override;
        void startLap() override;
    };
} // namespace ris
