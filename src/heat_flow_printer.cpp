#include "heat_flow_printer.hpp"

#include <iostream>
#include <iomanip>
#include <sstream>

HeatFlowPrinter::HeatFlowPrinter(HeatFlow& flow)
:flow_(flow)
{}

std::string HeatFlowPrinter::prettyPrint()
{
    std::ostringstream valueLine {};
    valueLine << std::fixed << std::setprecision(2) << "|";

    std::string dashLine {"+"};

    for (float value : flow_.getRod())
    {
        std::ostringstream oss {};
        oss << std::fixed << std::setprecision(2) << value;
        std::string valueString = oss.str();

        std::string dashes(valueString.length(), '-');

        dashLine += "--" + dashes + "--+";
        valueLine << "  " << value << "  |";
    }

    std::string fullLine = dashLine + "\n" + valueLine.str() + "\n" + dashLine;

    std::cout << fullLine << std::endl;
    return fullLine;
}
