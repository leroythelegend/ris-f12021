#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderFloat : public Decoder
    {
    public:
        DecoderFloat() = default;
        ~DecoderFloat() override = default;

        double decode(const Bytes &, Pos &) override;
    };
} // namespace ris
