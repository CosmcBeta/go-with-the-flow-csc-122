#include "../src/heat_flow.hpp"
#include "../src/heat_flow_printer.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include <vector>


TEST_CASE("one element") {
    HeatFlow flow(10, 5, 0.1, {Source(0, 10.5)});
    HeatFlowPrinter printer(flow);
    std::string output = printer.prettyPrint();

    REQUIRE(output.find("10.50") != std::string::npos);
    REQUIRE(std::count(output.begin(), output.end(), '+') >= 3);
}
