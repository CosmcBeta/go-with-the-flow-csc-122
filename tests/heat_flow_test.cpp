#include "../src/heat_flow.hpp"

#include <catch2/catch_test_macros.hpp>
#include <catch2/benchmark/catch_benchmark.hpp>
#include <catch2/benchmark/catch_constructor.hpp>
#include <catch2/generators/catch_generators_range.hpp>

#include <vector>


const std::vector<Source> SOURCES {{0, 100.0}};
const float INITIAL_TEMP {10};
const int NUMBER_OF_SECTIONS {5};
const float K {0.1};


TEST_CASE("k values out of bounds")
{
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, 0, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, -1, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, -0.1, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, -10, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, -2, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, -0.001, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, 10, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, 0.51, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, 0.7, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, 1, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, 100, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, 0.99, SOURCES));
}

TEST_CASE("k values in bounds")
{
    HeatFlow flow1 {INITIAL_TEMP, 5, 0.1, SOURCES};
    REQUIRE(flow1.getRod() == std::vector<float>{100.0, 10.0, 10.0, 10.0, 10.0});
    flow1.tick();
    REQUIRE(flow1.getRod() == std::vector<float>{100.0, 19.0, 10.0, 10.0, 10.0});
    flow1.tick();
    REQUIRE(flow1.getRod() == std::vector<float>{100.0, 26.2, 10.9, 10.0, 10.0});
    flow1.tick();
    REQUIRE(flow1.getRod() == std::vector<float>{100.0, 32.05, 12.34, 10.09, 10.0});

    HeatFlow flow2 {INITIAL_TEMP, 5, 0.2, SOURCES};
    REQUIRE(flow2.getRod() == std::vector<float>{100.0, 10.0, 10.0, 10.0, 10.0});
    flow2.tick();
    REQUIRE(flow2.getRod() == std::vector<float>{100.0, 28.0, 10.0, 10.0, 10.0});
    flow2.tick();
    REQUIRE(flow2.getRod() == std::vector<float>{100.0, 38.8, 13.6, 10.0, 10.0});
    flow2.tick();
    REQUIRE(flow2.getRod() == std::vector<float>{100.0, 46.00, 17.92, 10.72, 10.0});

    HeatFlow flow3 {INITIAL_TEMP, 5, 0.3, SOURCES};
    REQUIRE(flow3.getRod() == std::vector<float>{100.0, 10.0, 10.0, 10.0, 10.0});
    flow3.tick();
    REQUIRE(flow3.getRod() == std::vector<float>{100.0, 37.0, 10.0, 10.0, 10.0});
    flow3.tick();
    REQUIRE(flow3.getRod() == std::vector<float>{100.0, 47.8, 18.1, 10.0, 10.0});
    flow3.tick();
    REQUIRE(flow3.getRod() == std::vector<float>{100.0, 54.55, 24.58, 12.43, 10.0});

    HeatFlow flow4 {INITIAL_TEMP, 5, 0.05, SOURCES};
    REQUIRE(flow4.getRod() == std::vector<float>{100.0, 10.0, 10.0, 10.0, 10.0});
    flow4.tick();
    REQUIRE(flow4.getRod() == std::vector<float>{100.0, 14.5, 10.0, 10.0, 10.0});
    flow4.tick();
    REQUIRE(flow4.getRod() == std::vector<float>{100.0, 18.55, 10.225000381, 10.0, 10.0});
    flow4.tick();
    REQUIRE(flow4.getRod() == std::vector<float>{100.0, 22.206249237, 10.63, 10.011250496, 10.0});
}

TEST_CASE("number of sections outside of bounds")
{
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, 0, K, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, -1, K, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, -10, K, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, -5, K, SOURCES));
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, -100, K, SOURCES));
}

TEST_CASE("number of sections")
{
    HeatFlow flow1 {INITIAL_TEMP, 1, K, SOURCES};
    REQUIRE(flow1.getRod() == std::vector<float>{100.0});
    flow1.tick();
    REQUIRE(flow1.getRod() == std::vector<float>{100.0});

    HeatFlow flow2 {INITIAL_TEMP, 2, K, SOURCES};
    REQUIRE(flow2.getRod() == std::vector<float>{100.0, 10.0});
    flow2.tick();
    REQUIRE(flow2.getRod() == std::vector<float>{100.0, 28.0});
    flow2.tick();
    REQUIRE(flow2.getRod() == std::vector<float>{100.0, 42.40});

    HeatFlow flow4 {INITIAL_TEMP, 8, K, SOURCES};
    REQUIRE(flow4.getRod() == std::vector<float>{100.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0});
    flow4.tick();
    REQUIRE(flow4.getRod() == std::vector<float>{100.0, 19.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0});
    flow4.tick();
    REQUIRE(flow4.getRod() == std::vector<float>{100.0, 26.2, 10.9, 10.0, 10.0, 10.0, 10.0, 10.0});

    HeatFlow flow5 {INITIAL_TEMP, 10, K, SOURCES};
    REQUIRE(flow5.getRod() == std::vector<float>{100.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0});
    flow5.tick();
    REQUIRE(flow5.getRod() == std::vector<float>{100.0, 19.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0});
    flow5.tick();
    REQUIRE(flow5.getRod() == std::vector<float>{100.0, 26.2, 10.9, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0, 10.0});
}

TEST_CASE("invalid sources")
{
    std::vector<Source> invalid_sources = {Source(-1, 100.0)};
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, K, invalid_sources));

    invalid_sources = {Source(5, 100.0)};
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, K, invalid_sources));

    invalid_sources = {Source(10, 100.0)};
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, K, invalid_sources));

    invalid_sources = {Source(0, 100.0), Source(10, 50.0)};
    REQUIRE_THROWS(HeatFlow(INITIAL_TEMP, NUMBER_OF_SECTIONS, K, invalid_sources));
}

TEST_CASE("multiple sources at different positions")
{
    std::vector<Source> sources = {Source(0, 100.0), Source(4, 50.0)};
    HeatFlow flow1(INITIAL_TEMP, NUMBER_OF_SECTIONS, K, sources);
    REQUIRE(flow1.getRod() == std::vector<float>{100.0, 10.0, 10.0, 10.0, 50.0});
    flow1.tick();
    REQUIRE(flow1.getRod() == std::vector<float>{100.0, 19.0, 10.0, 14.0, 50.0});
    flow1.tick();
    REQUIRE(flow1.getRod() == std::vector<float>{100.0, 26.2, 11.3, 17.2, 50.0});
    flow1.tick();
    REQUIRE(flow1.getRod() == std::vector<float>{100.0, 32.090000153, 13.38, 19.890001297, 50.0});

    int number_of_sections = 6;
    sources = {Source(2, 80.0), Source(4, 60.0)};
    HeatFlow flow2(INITIAL_TEMP, number_of_sections, K, sources);
    REQUIRE(flow2.getRod() == std::vector<float>{10.0, 10.0, 80.0, 10.0, 60.0, 10.0});
    flow2.tick();
    REQUIRE(flow2.getRod() == std::vector<float>{10.0, 17.0, 80.0, 22.0, 60.0, 20.0});
    flow2.tick();
    REQUIRE(flow2.getRod() == std::vector<float>{11.4, 22.6, 80.0, 31.6, 60.0, 28.0});

    number_of_sections = 7;
    sources = {Source(0, 100.0), Source(3, 75.0), Source(6, 50.0)};
    HeatFlow flow3(INITIAL_TEMP, number_of_sections, K, sources);
    REQUIRE(flow3.getRod() == std::vector<float>{100.0, 10.0, 10.0, 75.0, 10.0, 10.0, 50.0});
    flow3.tick();
    REQUIRE(flow3.getRod() == std::vector<float>{100.0, 19.0, 16.5, 75.0, 16.5, 14.0, 50.0});
    flow3.tick();
    REQUIRE(flow3.getRod() == std::vector<float>{100.0, 26.85, 22.6, 75.0, 22.1, 17.85, 50.0});

    sources = {Source(2, 100.0)};
    HeatFlow flow4(INITIAL_TEMP, NUMBER_OF_SECTIONS, K, sources);
    REQUIRE(flow4.getRod() == std::vector<float>{10.0, 10.0, 100.0, 10.0, 10.0});
    flow4.tick();
    REQUIRE(flow4.getRod() == std::vector<float>{10.0, 19.0, 100.0, 19.0, 10.0});
    flow4.tick();
    REQUIRE(flow4.getRod() == std::vector<float>{11.8, 26.2, 100.0, 26.2, 11.8});

    number_of_sections = 5;
    sources = {Source(1, 90.0), Source(2, 80.0)};
    HeatFlow flow5(INITIAL_TEMP, number_of_sections, K, sources);
    REQUIRE(flow5.getRod() == std::vector<float>{10.0, 90.0, 80.0, 10.0, 10.0});
    flow5.tick();
    REQUIRE(flow5.getRod() == std::vector<float>{26.0, 90.0, 80.0, 17.0, 10.0});
    flow5.tick();
    REQUIRE(flow5.getRod() == std::vector<float>{38.8, 90.0, 80.0, 22.6, 11.4});

    sources = {Source(0, 5.0)};
    HeatFlow flow6(INITIAL_TEMP, NUMBER_OF_SECTIONS, K, sources);
    REQUIRE(flow6.getRod() == std::vector<float>{5.0, 10.0, 10.0, 10.0, 10.0});
    flow6.tick();
    REQUIRE(flow6.getRod() == std::vector<float>{5.0, 9.5, 10.0, 10.0, 10.0});
    flow6.tick();
    REQUIRE(flow6.getRod() == std::vector<float>{5.0, 9.1, 9.95, 10.0, 10.0});
    flow6.tick();
    REQUIRE(flow6.getRod() == std::vector<float>{5.0, 8.775000572, 9.87, 9.994999886, 10.0});

    sources = {Source(0, -50.0)};
    HeatFlow flow7(INITIAL_TEMP, NUMBER_OF_SECTIONS, K, sources);
    REQUIRE(flow7.getRod() == std::vector<float>{-50.0, 10.0, 10.0, 10.0, 10.0});
    flow7.tick();
    REQUIRE(flow7.getRod() == std::vector<float>{-50.0, 4.0, 10.0, 10.0, 10.0});
    flow7.tick();
    REQUIRE(flow7.getRod() == std::vector<float>{-50.0, -0.800000072, 9.4, 10.0, 10.0});
    flow7.tick();
    REQUIRE(flow7.getRod() == std::vector<float>{-50.0, -4.700000286, 8.44, 9.94, 10.0});

    sources = {Source(0, 100.0), Source(2, 8.0)};
    HeatFlow flow8(INITIAL_TEMP, NUMBER_OF_SECTIONS, K, sources);
    REQUIRE(flow8.getRod() == std::vector<float>{100.0, 10.0, 8.0, 10.0, 10.0});
    flow8.tick();
    REQUIRE(flow8.getRod() == std::vector<float>{100.0, 18.8, 8.0, 9.8, 10.0});
    flow8.tick();
    REQUIRE(flow8.getRod() == std::vector<float>{100.0, 25.84, 8.0, 9.64, 9.96});
    flow8.tick();
    REQUIRE(flow8.getRod() == std::vector<float>{100.0, 31.472000122, 8.0, 9.508000374, 9.895999908});
}
