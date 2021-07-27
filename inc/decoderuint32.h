#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderUInt32 : public Decoder
    {
    public:
        using Pos = Decoder::Pos;

        DecoderUInt32() = default;
        ~DecoderUInt32() override = default;

        void decode(const Bytes &, Pos &) override;
    };
} // namespace ris
