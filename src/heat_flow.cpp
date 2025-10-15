#include "heat_flow.hpp"

#include <algorithm>
#include <stdexcept>
#include <vector>

HeatFlow::HeatFlow(float initialTemp, int numberOfSections, float k, std::vector<Source> sources)
{
    if ( k <= 0 || k > 0.5)
    {
        throw std::runtime_error("K value is outside of bounds. K must be between 0 and 0.5");
    }
    else
    {
        k_ = k;
    }

    if (numberOfSections <= 0)
    {
        throw std::runtime_error("number of sections must be greater than 0");
    }
    else
    {
        rod_ = std::vector<float>(numberOfSections, initialTemp);
    }

    for (Source s : sources)
    {
        if (s.index < 0 || s.index >= numberOfSections)
        {
            throw std::runtime_error("source index is out of range");
        }

        rod_[s.index] = s.sourceAmount;
        sourceIndexes_.push_back(s.index);
    }
}

void HeatFlow::tick()
{
    // Skips tick if the size is one since there is nothing to calculate
    if (rod_.size() == 1)
    {
        return;
    }

    std::vector<float> nextStep {};

    // Does first section if it is not a source - skips the prev since there is none
    if (sourceIndexes_[0] != 0)
    {
        float first {rod_[0]};
        float second {rod_[1]};
        // curr + k * (next - 2 * curr + next) -> curr + k * (2 * next - 2 * curr) -> curr + k * 2 * (next - curr)
        float T {first + 2 * k_ * (second - first)};
        nextStep.push_back(T);
    }
    else
    {
        nextStep.push_back(rod_[0]);
    }


    // Loops starting at second element and going to second to last element
    for (int j = 1; j < rod_.size() - 1; j++)
    {
        // Returns vector.end if the value it NOT in the vector
        if (std::find(sourceIndexes_.begin(), sourceIndexes_.end(), j) != sourceIndexes_.end())
        {
            nextStep.push_back(rod_[j]);
            continue;
        }

        float prev {rod_[j - 1]};
        float curr {rod_[j]};
        float next {rod_[j + 1]};

        float T {curr + k_ * (prev - 2 * curr + next)};
        nextStep.push_back(T);
    }

    // Does last section just like first section
    int lastElementIndex = rod_.size() - 1;
    if (sourceIndexes_[sourceIndexes_.size() - 1] != lastElementIndex)
    {
        float last {rod_[lastElementIndex]};
        float second {rod_[lastElementIndex - 1]};
        // curr + k * (prev - 2 * curr + prev) -> curr + k * (2 * prev - 2 * curr) -> curr + 2 * k * (prev - curr)
        float T {last + 2 * k_ * (second - last)};
        nextStep.push_back(T);
    }
    else
    {
        nextStep.push_back(rod_[lastElementIndex]);
    }
    rod_ = nextStep;
}

std::vector<float>& HeatFlow::getRod()
{
    return rod_;
}

Source::Source(int i, float s)
:index(i), sourceAmount(s)
{}
