#pragma once

#include <memory>
#include <map>
#include <vector>

#include "element.h"

namespace ris
{
    class Packet
    {
    public:
        using Ptr = std::shared_ptr<Packet>;
        using Unit = int;

        virtual ~Packet() = default;

        virtual Elements element(const Unit &) const;

        void add(const Packet::Ptr &);

    protected:
        std::map<Unit, Elements> telemetry_;
        std::vector<Packet::Ptr> packets_;

        Packet() = default;
    };

} // namespace ris
