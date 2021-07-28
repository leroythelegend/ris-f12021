#pragma once

#include <memory>
#include <map>

#include "element.h"

namespace ris
{
    class Packet
    {
    public:
    using Ptr = std::shared_ptr<Packet>;
        using Unit = int;

        virtual ~Packet() = default;

        Element element(const Unit &) const;
    
    protected:
        std::map<Unit, Element> telemetry_;
    };

} // namespace ris
