cmake_minimum_required(VERSION 3.24)

project("Go With the Flow")

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

Include(FetchContent)

FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.8.1
)

FetchContent_MakeAvailable(Catch2)

add_executable(heat_flow_test tests/heat_flow_test.cpp src/heat_flow.cpp)
add_executable(heat_flow_printer_test tests/heat_flow_printer_test.cpp src/heat_flow_printer.cpp)
add_executable(main main.cpp src/heat_flow.cpp src/heat_flow_printer.cpp)

target_link_libraries(heat_flow_test PRIVATE Catch2::Catch2WithMain)
target_link_libraries(heat_flow_printer_test PRIVATE Catch2::Catch2WithMain)
