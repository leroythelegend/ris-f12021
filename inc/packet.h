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

        virtual ~Packet() = default;

        void decode(const Bytes &);

    protected:
        Decoders decoders_;
    };
} // namespace ris
