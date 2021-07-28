#pragma once

#include "decoder.h"

namespace ris
{
    class Decoder2Bytes : public Decoder
    {
    public:
        using Pos = Decoder::Pos;

        Decoder2Bytes() = default;
        ~Decoder2Bytes() override = default;

        void decode(const Bytes &, Pos &) override;

    private:
        float getFloatFromBytes(const Bytes &, Pos &);
        uint64_t getUIntFromBytes(const Bytes &, Pos &);
        int64_t getSIntFromBytes(const Bytes &, Pos &);
    };
} // namespace ris
