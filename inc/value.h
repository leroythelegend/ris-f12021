#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace ris
{
    using Values = std::vector<double>;
    // struct Value
    // {
    //     uint64_t UInt = 0;
    //     int64_t SInt = 0;
    //     float Float = 0;
    // };

    // enum class Prefered
    // {
    //     UINT,
    //     SINT,
    //     FLOAT
    // };

    // class Values
    // {
    // public:
    //     Values() = default;
    //     Values(const Value, const Prefered);

    //     const double at(int) const;
    //     const Value value(int) const;

    //     void push_back(const Value &element, const Prefered);

    //     std::vector<Value>::const_iterator begin() const noexcept;
    //     std::vector<Value>::const_iterator end() const noexcept;

    //     unsigned int size() const;

    //     std::string to_string() const;

    // private:
    //     Prefered prefered_;
    //     std::vector<Value> elements;
    // };

} // namespace ris
