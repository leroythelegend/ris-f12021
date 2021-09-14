#pragma once

#include "capture.h"
#include "packetlapdata.h"
#include "definitions.h"
#include "network.h"
#include "../inc/processlap.h"

namespace ris
{
    class CaptureCSV : public Capture
    {
    public:
        using Port = unsigned int;

        CaptureCSV(Port, ProcessLap::Ptr);
        virtual ~CaptureCSV() = default;

        void start() override;

        void change(CaptureState::Ptr) override;

    private:
        Port port_;
        CaptureState::Ptr state_;

        void sessionStarted();
        void sessionEnded();
        void returnToPits();
        void startLap();
        void finishLap();
    };
} // namespace ris
