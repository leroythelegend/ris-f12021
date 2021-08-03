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
        std::map<Element, Values> telemetry() const;

        std::vector<Packet::Ptr> packets(const Element &) const;

        std::map<Element, std::vector<Packet::Ptr>> packets() const;

    protected:
        void add(const Element &, const std::vector<Packet::Ptr> &);

        std::map<Element, Values> telemetry_;
        std::map<Element, std::vector<Packet::Ptr>> packets_;

        Packet() = default;
    };

} // namespace ris
