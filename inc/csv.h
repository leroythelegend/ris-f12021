#pragma once

#include <string>

#include "telemetry.h"
#include "networkfile.h"

namespace ris
{
    class CSV
    {
    public:

        using FileName = std::string;

        CSV(const FileName &);
        ~CSV() = default;

        void write(const Telemetries &) const;

    private:
        NetworkFile network;
    };
} // namespace ris
