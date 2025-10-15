#pragma once

#include <vector>

struct Source
{
    Source(int i, float s);
    int index;
    float sourceAmount;
};

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
