#pragma once

#include "decoder.h"

namespace ris
{
    class DecoderUInt8 : public Decoder
    {
    public:
        using Pos = Decoder::Pos;

        DecoderUInt8() = default;
        ~DecoderUInt8() override = default;

        void decode(const Bytes &, Pos &) override;

    protected:
        unsigned int uint_ = 0;
        int sint_ = 0;
        float float_ = 0;
    };
} // namespace ris
