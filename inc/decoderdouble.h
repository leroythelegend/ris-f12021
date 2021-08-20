#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderDouble : public Decoder
    {
    public:
        DecoderDouble() = default;
        ~DecoderDouble() override = default;

        double decode(const Bytes &, Pos &) override;
        Values decode(const Bytes &, Pos &, const Amount&) override;
    };
} // namespace ris
