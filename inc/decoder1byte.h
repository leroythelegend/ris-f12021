#pragma once

#include "decoder.h"

namespace ris
{
    class Decoder1Byte : public Decoder
    {
    public:
        using Pos = Decoder::Pos;

        Decoder1Byte() = default;
        ~Decoder1Byte() override = default;

        void decode(const Bytes &, Pos &) override;
    };
} // namespace ris
