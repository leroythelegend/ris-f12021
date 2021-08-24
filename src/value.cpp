#include "../inc/value.h"

namespace ris
{
    std::string Values::to_string() const
    {
        std::string result;
        for (auto value : *this)
        {
            result.append(1, static_cast<char>(value));
        }
        return result;
    }

    bool Values::at_bitWiseAND(size_t index, size_t a)
    {
        return static_cast<size_t>(at(index)) & a; 
    }

} // namespace ris
