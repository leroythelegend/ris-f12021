#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderUInt16 : public Decoder
    {
    public:
        using Pos = Decoder::Pos;

        DecoderUInt16() = default;
        ~DecoderUInt16() override = default;

        void decode(const Bytes &, Pos &) override;
    };
} // namespace ris
