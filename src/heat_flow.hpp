#pragma once

#include "source.hpp"

#include <vector>


class HeatFlow
{
public:
    HeatFlow(float initialTemp, int numberOfSections, float k, std::vector<Source> sources);

    void tick();

    std::vector<float>& getRod();

private:
    float k_;
    std::vector<float> rod_;
    std::vector<int> sourceIndexes_;
};
