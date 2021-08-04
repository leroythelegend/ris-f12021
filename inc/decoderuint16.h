#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderUInt16 : public Decoder
    {
    public:
        DecoderUInt16() = default;
        ~DecoderUInt16() override = default;

        double decode(const Bytes &, Pos &) override;
        Values decode(const Bytes &, Pos &, const Amount&) override;
    };
} // namespace ris
