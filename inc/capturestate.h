#pragma once

#include <memory>

#include "state.h"
#include "processlap.h"

namespace ris
{
    class Capture;

    class CaptureState
    {
    public:
        using Ptr = std::shared_ptr<CaptureState>;

        CaptureState(Capture *capture, State::Ptr state, ProcessLap::Ptr process)
            : capture_{capture}, state_{state}, process_{process} {}

        virtual ~CaptureState() = default;

        void initPackets()
        {
            state_->initialisePacketsFromNetwork();
        }

        virtual void sessionStarted(){};
        virtual void sessionEnded(){};
        virtual void returnToPits(){};
        virtual void startLap(){};
        virtual void finishLap(){};

    protected:
        Capture *capture_;
        State::Ptr state_;
        ProcessLap::Ptr process_;
    };
} // namespace ris
