#include "../inc/value.h"

namespace ris
{
    Values::Values(const Value element)
    {
        elements.push_back(element);
    }

    const Value Values::at(int index) const
    {
        return elements.at(index);
    }

    void Values::push_back(const Value &element)
    {
        elements.push_back(element);
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
        for (auto element : elements)
        {
            result.append(1, static_cast<char>(element.UInt));
        }
        return result;
    }

} // namespace ris
