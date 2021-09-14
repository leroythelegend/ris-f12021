#pragma once

#include <memory>

#include "capturestate.h"
#include "state.h"

namespace ris
{
    class CaptureLapState : public CaptureState
    {
    public:
        CaptureLapState(Capture *, State::Ptr, ProcessLap::Ptr);
        virtual ~CaptureLapState() = default;

        void sessionEnded() override;
        void returnToPits() override;
        void startLap() override;
        void finishLap() override;
    };
} // namespace ris
