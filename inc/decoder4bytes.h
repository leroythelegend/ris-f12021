#pragma once

#include "decoder.h"

namespace ris
{
    class Decoder4Bytes : public Decoder
    {
    public:
        using Pos = Decoder::Pos;

        Decoder4Bytes() = default;
        ~Decoder4Bytes() override = default;

        void decode(const Bytes &, Pos &) override;

    private:
        float getFloatFromBytes(const Bytes &, Pos &);
        uint64_t getUIntFromBytes(const Bytes &, Pos &);
        int64_t getSIntFromBytes(const Bytes &, Pos &);
    };
} // namespace ris
