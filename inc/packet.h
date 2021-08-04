#pragma once

#include <memory>
#include <map>
#include <vector>

#include "value.h"
#include "element.h"

namespace ris
{

    class SubPacket
    {
    public:
        using Ptr = std::shared_ptr<SubPacket>;
        using TelemetryMap = std::map<Element, Values>;

        virtual ~SubPacket() = default;

        Values telemetry(const Element &) const;
        TelemetryMap telemetry() const;

    protected:
        TelemetryMap telemetry_;
    };

    class Packet
    {
    public:
        using Ptr = std::shared_ptr<Packet>;
        using SubPackets = std::vector<SubPacket::Ptr>;
        using PacketMap = std::map<Element, SubPackets>;

        virtual ~Packet() = default;

        SubPackets packets(const Element &) const;
        PacketMap packets() const;

    protected:
        void add(const Element &, const SubPackets &);
        PacketMap packets_;

        Packet() = default;
    };

} // namespace ris
