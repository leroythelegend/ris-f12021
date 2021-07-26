#pragma once

#include <memory>

#include "definitions.h"

namespace ris
{
    class Network
    {
    public:
        using Ptr = std::unique_ptr<Network>;

        virtual ~Network() = default;

        virtual Bytes read() const = 0;
    };

} // namespace ris
