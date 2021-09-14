#pragma once

#include <memory>
#include <string>

#include "definitions.h"

namespace ris
{
    class Network
    {
    public:
        using Ptr = std::shared_ptr<Network>;

        virtual ~Network() = default;

        virtual Bytes read() const = 0;
        virtual void write(const std::string &) const = 0;
    };

} // namespace ris
