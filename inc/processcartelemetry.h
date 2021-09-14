#pragma once

#include <memory>

#include "processlap.h"
#include "telemetry.h"
#include "record.h"

namespace ris
{

    class ProcessCarTelemetry : public ProcessLap
    {
    public:
        ProcessCarTelemetry(Record::Ptr record)
            : record_{record} {}
        virtual ~ProcessCarTelemetry() = default;

        void process(Packets) override;
        void record() override;
        void reset() override;
    
    private:
        Telemetries telemetries_;
        Record::Ptr record_;
    };

} // namespace rix
