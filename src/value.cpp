#include "../inc/value.h"

namespace ris
{
    Values::Values(const Value value)
    {
        elements.push_back(value);
    }

    const Value Values::at(int index) const
    {
        return elements.at(index);
    }

    void Values::push_back(const Value &value)
    {
        elements.push_back(value);
    }

    std::vector<Value>::const_iterator Values::begin() const noexcept
    {
        return elements.begin();
    }

    std::vector<Value>::const_iterator Values::end() const noexcept
    {
        return elements.end();
    }

    std::string Values::to_string() const
    {
        std::string result;
        for (auto value : elements)
        {
            result.append(1, static_cast<char>(value.UInt));
        }
        return result;
    }

} // namespace ris
