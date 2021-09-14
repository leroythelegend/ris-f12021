#include "../inc/capturerecordstate.h"
#include "../inc/capturelapstate.h"
#include "../inc/capturefrontendstate.h"
#include "../inc/capturepitstate.h"
#include "../inc/capturerecordstate.h"
#include "../inc/capture.h"

namespace ris
{
    CaptureRecordState::CaptureRecordState(Capture *capture, State::Ptr state, ProcessLap::Ptr process)
        : CaptureState(capture, state, process)
    {
    }
    
    void CaptureRecordState::startLap()
    {
        process_->record();
        capture_->change(std::make_shared<CaptureLapState>(capture_, state_, process_));
    }
} // namespace ris
