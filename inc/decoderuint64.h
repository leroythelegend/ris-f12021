#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderUInt64 : public Decoder
    {
    public:
        DecoderUInt64() = default;
        ~DecoderUInt64() override = default;

        double decode(const Bytes &, Pos &) override;
    };
} // namespace ris
