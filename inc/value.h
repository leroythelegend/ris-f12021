#pragma once

#include <cstdint>
#include <vector>
#include <string>

namespace ris
{
    struct Value
    {
        uint64_t UInt = 0;
        int64_t SInt = 0;
        float Float = 0;
    };

    class Values
    {
    public:
        Values() = default;
        Values(const Value element, const int prefered);

        const double at(int index) const;
        const Value value(int index) const;

        void push_back(const Value &element, const int prefered);

        std::vector<Value>::const_iterator begin() const noexcept;
        std::vector<Value>::const_iterator end() const noexcept;

        unsigned int size() const;

        std::string to_string() const;

    private:
        int prefered_;
        std::vector<Value> elements;
    };

} // namespace ris
