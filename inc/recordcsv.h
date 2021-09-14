#pragma once

#include "record.h"

namespace ris
{

    class RecordCSV : public Record
    {
    public:
        virtual ~RecordCSV() = default;

        void record(Telemetries &) override;
    };

} // namespace rix
