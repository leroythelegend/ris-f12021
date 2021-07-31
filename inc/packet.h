#pragma once

#include <memory>
#include <map>
#include <vector>

#include "value.h"
#include "element.h"

namespace ris
{
    class Packet
    {
    public:
        using Ptr = std::shared_ptr<Packet>;

        virtual ~Packet() = default;

        virtual Values value(const Element &) const;

        void add(const Packet::Ptr &);

    protected:
        std::map<Element, Values> telemetry_;
        std::vector<Packet::Ptr> packets_;

        Packet() = default;
    };

} // namespace ris
