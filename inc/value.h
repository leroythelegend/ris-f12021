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

        Values() = default;
        Values(std::initializer_list<double> il)
            : vector(il) {}
        virtual ~Values() = default;

        std::string to_string() const;
    };
    // using Values = std::vector<double>;
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
