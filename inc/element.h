#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace ris
{
    struct Element
    {
        uint64_t UInt = 0;
        int64_t SInt = 0;
        float Float = 0;
    };

    class Elements
    {
    public:
        Elements() = default;
        Elements(const Element element);

        const Element at(int index) const;

        void push_back(const Element &element);

        std::vector<Element>::const_iterator begin() const noexcept;
        std::vector<Element>::const_iterator end() const noexcept;

        std::string to_string() const;

    private:
        std::vector<Element> elements;
    };

} // namespace ris
