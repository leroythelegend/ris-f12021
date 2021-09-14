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

        friend bool operator<(const Element &l, const Element &r)
        {
            return l.to_string() < r.to_string();
        }

        friend bool operator==(const Element &lhs, Element &rhs)
        {
            return lhs.to_string() == rhs.to_string();
        }

        friend bool operator!=(const Element &lhs, Element &rhs)
        {
            return !(lhs == rhs);
        }

    private:
        Name name_;
    };
} // namespace ris
