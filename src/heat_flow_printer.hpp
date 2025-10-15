#pragma once

#include "heat_flow.hpp"

#include <string>

class HeatFlowPrinter
{
public:
    HeatFlowPrinter(HeatFlow& flow);

    std::string prettyPrint();

private:
    HeatFlow& flow_;
};
