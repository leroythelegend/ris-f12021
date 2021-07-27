#pragma once

#include <memory>
#include <vector>

#include "../inc/decoder.h"

namespace ris
{
    class Packet
    {
    public:
        using Ptr = std::shared_ptr<Packet>;
        using Decoders = std::vector<Decoder::Ptr>;
        using Pos = unsigned int;

        virtual ~Packet() = default;

        virtual void decode(const Bytes &, Pos &);

    protected:
        Decoders decoders_;
    };
} // namespace ris
