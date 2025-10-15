#include "src/heat_flow.hpp"
#include "src/heat_flow_printer.hpp"
#include <vector>

int main()
{
    std::vector<Source> sources_and_sinks;
    sources_and_sinks.push_back({0, 100});
    sources_and_sinks.push_back({2, 8.0});
    float initial_temperature = 10;
    int number_of_sections = 5;
    float K = 0.1;

    HeatFlow flow(initial_temperature, number_of_sections, K, sources_and_sinks);
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
