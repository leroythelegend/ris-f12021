#pragma once

#include <string>

namespace ris
{
    class Element
    {
    public:
        using Name = std::string;

        Element(const Name &name)
            : name_{name} {}
        ~Element() = default;

        Name to_string() const
        {
            return name_;
        }

    private:
        Name name_;
    };

    inline bool operator==(const Element &lhs, Element &rhs)
    {
        return lhs.to_string() == rhs.to_string();
    }

    inline bool operator!=(const Element &lhs, Element &rhs)
    {
        return !(lhs == rhs);
    }
} // namespace ris
