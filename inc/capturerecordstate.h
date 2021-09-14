#pragma once

#include <memory>

#include "capturestate.h"
#include "state.h"

namespace ris
{
    class CaptureRecordState : public CaptureState
    {
    public:
        CaptureRecordState(Capture *, State::Ptr, ProcessLap::Ptr);
        virtual ~CaptureRecordState() = default;

        void startLap() override;
    };
} // namespace ris
