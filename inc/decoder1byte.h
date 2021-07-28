#pragma once

#include "decoder.h"

namespace ris
{
    class Decoder1Byte : public Decoder
    {
    public:
        Decoder1Byte() = default;
        ~Decoder1Byte() override = default;

        Element decode(const Bytes &, Pos &) override;
    };
} // namespace ris
