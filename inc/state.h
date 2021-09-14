#pragma once

#include <memory>
#include "networkudp.h"
#include "definitions.h"

namespace ris
{
    class State
    {
    public:
        using Ptr = std::shared_ptr<State>;

        State(Network::Ptr);
        ~State() = default;

        void initialisePacketsFromNetwork();

        bool hasSessionStarted();
        bool hasSessionEnded();
        bool returnedToPits();
        bool hasStartedLap();
        bool hasLapFinished();

        Packets getPackets() const;
        double getCurrentLap() const;

    private:
        Network::Ptr network_;
        Packets packets_;
        double currentlap_ = 0;
    };
} // namespace ris
