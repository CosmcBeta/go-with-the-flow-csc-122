#pragma once

#include "source.hpp"

#include <vector>


struct Config
{
    Config(float k_value, int n, float initial, std::vector<Source> s);
    float k;
    int numberOfSections;
    float initialTemperature;
    std::vector<Source> sourcesAndSinks;
};


class Configure
{
public:
    Configure() = default;

    Config configureHeatFlow();

private:
    int getInput(int lowerBound, int upperBound, const std::string& prompt, int defaultValue);
    float getInput(float lowerBound, float upperBound, const std::string& prompt, float defaultValue);

};
