#pragma once

#include <memory>

#include "definitions.h"

namespace ris
{
    class Decoder
    {
    public:
        using Ptr = std::shared_ptr<Decoder>;

        virtual ~Decoder() = default;

        virtual double decode(const Bytes &, Pos &) = 0;
    };
} // namespace ris
