#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderUInt32 : public Decoder
    {
    public:
        DecoderUInt32() = default;
        ~DecoderUInt32() override = default;

        double decode(const Bytes &, Pos &) override;
        Values decode(const Bytes &, Pos &, const Amount&) override;
    };
} // namespace ris
