#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace ris
{
    class Values : private std::vector<double>
    {
        typedef double T;
        typedef std::vector<double> vector;

    public:
        using vector::at;
        using vector::begin;
        using vector::end;
        using vector::push_back;
        using vector::size;

        Values() = default;
        Values(std::initializer_list<double> il)
            : vector(il) {}
        virtual ~Values() = default;

        std::string to_string() const;

        bool at_bitWiseAND(size_t index, size_t a);
    };
} // namespace ris
