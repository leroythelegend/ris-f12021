#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderUInt64 : public Decoder
    {
    public:
        using Pos = Decoder::Pos;

        DecoderUInt64() = default;
        ~DecoderUInt64() override = default;

        void decode(const Bytes &, Pos &) override;
    };
} // namespace ris
