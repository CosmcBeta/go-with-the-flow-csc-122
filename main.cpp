#include "src/heat_flow.hpp"
#include "src/heat_flow_printer.hpp"
#include "src/config.hpp"

#include <vector>

int main()
{
    Configure configure {};
    Config c = configure.configureHeatFlow();
    HeatFlow flow(c.initialTemperature, c.numberOfSections, c.k, c.sourcesAndSinks);
    HeatFlowPrinter printer(flow);

    printer.prettyPrint();

    flow.tick();
    printer.prettyPrint();

    flow.tick();
    printer.prettyPrint();

    flow.tick();
    printer.prettyPrint();

    flow.tick();
    printer.prettyPrint();

    flow.tick();
    printer.prettyPrint();

    flow.tick();
    printer.prettyPrint();
}
