#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderUInt8 : public Decoder
    {
    public:
        DecoderUInt8() = default;
        ~DecoderUInt8() override = default;

        double decode(const Bytes &, Pos &) override;
        Values decode(const Bytes &, Pos &, const Amount&) override;
    };
} // namespace ris
