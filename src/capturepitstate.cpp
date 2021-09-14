#include "../inc/capturepitstate.h"
#include "../inc/capturelapstate.h"
#include "../inc/capturefrontendstate.h"
#include "../inc/capture.h"

namespace ris
{
    CapturePitState::CapturePitState(Capture *capture, State::Ptr state, ProcessLap::Ptr process)
        : CaptureState(capture, state, process) {}

    void CapturePitState::sessionEnded()
    {
        if (state_->hasSessionEnded())
        {
            capture_->change(std::make_shared<CaptureFrontEndState>(capture_, state_, process_));
        }
    }

    void CapturePitState::startLap()
    {
        if (state_->hasStartedLap())
        {
            capture_->change(std::make_shared<CaptureLapState>(capture_, state_, process_));
        }
    }
} // namespace ris
