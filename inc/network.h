#pragma once

#include <memory>

#include "definitions.h"

namespace ris
{
    class Network
    {
    public:
        using Ptr = std::unique_ptr<Network>;
        using Amount = unsigned int;

        virtual ~Network() = default;

        virtual Bytes read(const Amount&) const = 0;
    };

} // namespace ris
