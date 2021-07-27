#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderFloat : public Decoder
    {
    public:
        using Pos = Decoder::Pos;

        DecoderFloat() = default;
        ~DecoderFloat() override = default;

        void decode(const Bytes &, Pos &) override;
    };
} // namespace ris
