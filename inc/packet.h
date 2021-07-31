#pragma once

#include <memory>
#include <map>
#include <vector>

#include "value.h"

namespace ris
{
    class Packet
    {
    public:
        using Ptr = std::shared_ptr<Packet>;
        using Unit = int;

        virtual ~Packet() = default;

        virtual Values element(const Unit &) const;

        void add(const Packet::Ptr &);

    protected:
        std::map<Unit, Values> telemetry_;
        std::vector<Packet::Ptr> packets_;

        Packet() = default;
    };

} // namespace ris
