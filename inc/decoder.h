#pragma once

#include <memory>

#include "definitions.h"
#include "value.h"

namespace ris
{
    class Decoder
    {
    public:
        using Ptr = std::shared_ptr<Decoder>;

        virtual ~Decoder() = default;

        virtual Value decode(const Bytes &, Pos &) = 0;

    protected:
        float convertUIntToFloat(const uint32_t) const;
    };
} // namespace ris
