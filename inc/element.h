#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace ris
{
    struct Element
    {
        uint64_t UInt = 0;
        int64_t  SInt = 0;
        float Float = 0;
    };

    struct Elements
    {
        Elements() = default;
        Elements(const Element element)
        {
            elements.push_back(element);
        }

        Element at(int index)
        {
            return elements.at(index);
        }

        void push_back(const Element& element)
        {
            elements.push_back(element);
        }

        std::vector<Element>::const_iterator begin() const noexcept
        {
            return elements.begin();
        }

        std::vector<Element>::const_iterator end() const noexcept
        {
            return elements.end();
        }

        std::string to_string()
        {
            std::string result;
            for (auto element : elements)
            {
                result.append(1, static_cast<char>(element.UInt));
            }
            return result;
        }

        std::vector<Element> elements;
    };

} // namespace ris
