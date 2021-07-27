#pragma once

#include <memory>
#include <cstdint>

#include "definitions.h"

namespace ris
{
    class Decoder
    {
    public:
        using Ptr = std::shared_ptr<Decoder>;
        using Pos = unsigned int;

        virtual ~Decoder() = default;

        virtual void decode(const Bytes &, Pos &) = 0;

        inline uint64_t uint() const
        {
            return uint_; 
        }

        inline int sint() const
        {
            return sint_;
        }

        float float32() const
        {
            return float_;
        }

    protected:
        uint64_t uint_ = 0;
        int sint_ = 0;
        float float_ = 0;
    };
} // namespace ris
