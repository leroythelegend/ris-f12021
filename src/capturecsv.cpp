#include "../inc/capturecsv.h"
#include "../inc/capturefrontendstate.h"
#include "../inc/networkudp.h"
#include "../inc/state.h"

namespace ris
{
    CaptureCSV::CaptureCSV(CaptureCSV::Port port, ProcessLap::Ptr process)
        : state_{std::make_shared<CaptureFrontEndState>(this, 
                                std::make_shared<State>(std::make_shared<NetworkUDP>(port)), 
                                process)}
    {
    }

    void CaptureCSV::start()
    {
        while (true)
        {
            sessionStarted();
            sessionEnded();
            returnToPits();
            finishLap();
            startLap();
        }
    }

    void CaptureCSV::change(CaptureState::Ptr state)
    {
        state_ = state;
    }

    void CaptureCSV::sessionStarted()
    {
        state_->initPackets();
        state_->sessionStarted();
    }

    void CaptureCSV::sessionEnded()
    {
        state_->sessionEnded();
    }

    void CaptureCSV::returnToPits()
    {
        state_->returnToPits();
    }

    void CaptureCSV::startLap()
    {
        state_->startLap();
    }

    void CaptureCSV::finishLap()
    {
        state_->finishLap();
    }
} // namespace ris
