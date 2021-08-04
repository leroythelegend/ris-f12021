#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderInt16 : public Decoder
    {
    public:
        DecoderInt16() = default;
        ~DecoderInt16() override = default;

        double decode(const Bytes &, Pos &) override;
    };
} // namespace ris
