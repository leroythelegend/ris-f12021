#pragma once

#include <memory>
#include <cstdint>

#include "definitions.h"

namespace ris
{
    class Decoder
    {
    public:
        struct Element
        {
            uint64_t UInt = 0;
            int64_t SInt = 0;
            float Float = 0;
        };

        using Ptr = std::shared_ptr<Decoder>;
        using Pos = unsigned int;

        virtual ~Decoder() = default;

        virtual void decode(const Bytes &, Pos &) = 0;

        inline Element element() const
        {
            return element_;
        }

    protected:
        Element element_;

        float convertUIntToFloat(const uint32_t) const;
    };
} // namespace ris
