#include "../inc/element.h"

namespace ris
{
    Elements::Elements(const Element element)
    {
        elements.push_back(element);
    }

    const Element Elements::at(int index) const
    {
        return elements.at(index);
    }

    void Elements::push_back(const Element &element)
    {
        elements.push_back(element);
    }

    std::vector<Element>::const_iterator Elements::begin() const noexcept
    {
        return elements.begin();
    }

    std::vector<Element>::const_iterator Elements::end() const noexcept
    {
        return elements.end();
    }

    std::string Elements::to_string() const
    {
        std::string result;
        for (auto element : elements)
        {
            result.append(1, static_cast<char>(element.UInt));
        }
        return result;
    }

} // namespace ris
