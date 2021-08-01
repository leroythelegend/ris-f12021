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

        Values value(const Element &) const;
        std::vector<Packet::Ptr> packets(const int) const;

        void add(const int, const std::vector<Packet::Ptr> &);

    protected:
        std::map<Element, Values> telemetry_;
        std::map<int, std::vector<Packet::Ptr>> packets_;

        // std::vector<Packet::Ptr> packets_;

        Packet() = default;
    };

} // namespace ris
