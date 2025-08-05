cmake_minimum_required(VERSION 3.30)

find_package(Zephyr REQUIRED HINTS $ENV{ZEPHYR_BASE})

project(gale_net_app_relay)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# =============================================================================
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# =============================================================================
target_sources(app PRIVATE
  src/main.cpp
)

target_include_directories(app PRIVATE include)
