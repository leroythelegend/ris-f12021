#include "../inc/capturelapstate.h"
#include "../inc/capturefrontendstate.h"
#include "../inc/capturepitstate.h"
#include "../inc/capturerecordstate.h"
#include "../inc/capture.h"

#include <iostream>

namespace ris
{
    CaptureLapState::CaptureLapState(Capture *capture, State::Ptr state, ProcessLap::Ptr process)
        : CaptureState(capture, state, process)
    {
        std::cout << "Recording lap " << static_cast<unsigned int>(state_->getCurrentLap()) << std::endl;
        process_->reset();
    }

    void CaptureLapState::sessionEnded()
    {
        if (state_->hasSessionEnded())
        {
            capture_->change(std::make_shared<CaptureRecordState>(capture_, state_, process_));
        }
    }

    void CaptureLapState::returnToPits()
    {
        if (state_->returnedToPits())
        {
            capture_->change(std::make_shared<CapturePitState>(capture_, state_, process_));
        }
    }

    void CaptureLapState::startLap()
    {
        process_->process(state_->getPackets());
    }

    void CaptureLapState::finishLap()
    {
        if (state_->hasLapFinished())
        {
            capture_->change(std::make_shared<CaptureRecordState>(capture_, state_, process_));
        }
    }
} // namespace ris
