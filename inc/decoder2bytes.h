#pragma once

#include "decoder.h"

namespace ris
{
    class Decoder2Bytes : public Decoder
    {
    public:
        Decoder2Bytes() = default;
        ~Decoder2Bytes() override = default;

        Value decode(const Bytes &, Pos &) override;

    private:
        float getFloatFromBytes(const Bytes &, Pos &);
        uint64_t getUIntFromBytes(const Bytes &, Pos &);
        int64_t getSIntFromBytes(const Bytes &, Pos &);
    };
} // namespace ris
