#include "../inc/capturefrontendstate.h"
#include "../inc/capturepitstate.h"
#include "../inc/capture.h"

namespace ris
{
    CaptureFrontEndState::CaptureFrontEndState(Capture *capture, State::Ptr state, ProcessLap::Ptr process)
        : CaptureState(capture, state, process) {}

    void CaptureFrontEndState::sessionStarted()
    {
        if (state_->hasSessionStarted())
        {
            capture_->change(std::make_shared<CapturePitState>(capture_, state_, process_));
        }
    }
} // namespace ris
