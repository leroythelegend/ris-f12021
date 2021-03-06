#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderInt8 : public Decoder
    {
    public:
        DecoderInt8() = default;
        ~DecoderInt8() override = default;

        double decode(const Bytes &, Pos &) override;
        Values decode(const Bytes &, Pos &, const Amount&) override;
    };
} // namespace ris
