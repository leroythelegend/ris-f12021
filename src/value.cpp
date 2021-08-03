#include "../inc/value.h"

namespace ris
{
    Values::Values(const Value value, const Prefered prefered)
        : prefered_(prefered)
    {
        elements.push_back(value);
    }

    const double Values::at(int index) const
    {
        double result;
        if (prefered_ == Prefered::UINT)
        {
            result = elements.at(index).UInt;
        }
        else if (prefered_ == Prefered::SINT)
        {
            result = elements.at(index).SInt;
        }
        else if (prefered_ == Prefered::FLOAT)
        {
            result = elements.at(index).Float;
        }
        return result;
    }

    const Value Values::value(int index) const
    {
        return elements.at(index);
    }

    void Values::push_back(const Value &value, const Prefered prefered)
    {
        prefered_ = prefered;
        elements.push_back(value);
    }

    std::vector<Value>::const_iterator Values::begin() const noexcept
    {
        return elements.begin();
    }

    std::vector<Value>::const_iterator Values::end() const noexcept
    {
        return elements.end();
    }

    unsigned int Values::size() const
    {
        return elements.size();
    }

    std::string Values::to_string() const
    {
        std::string result;
        for (auto value : elements)
        {
            result.append(1, static_cast<char>(value.UInt));
        }
        return result;
    }

} // namespace ris
