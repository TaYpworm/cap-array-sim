cmake_minimum_required (VERSION 2.8)
project (CapArraySim)
set (CapArraySim_VERSION_MAJOR 0)
set (CapArraySim_VERSION_MINOR 1)
set (CapArraySim_VERSION_PATCH 0)
set (CapArraySim_VERSION "${CapArraySim_VERSION_MAJOR}.${CapArraySim_VERSION_MINOR}.${CapArraySim_VERSION_PATCH}")

message("CapArraySim version ${CapArraySim_VERSION}")

set (PROJECT_SOURCE_DIR "./src")
set (PROJECT_INCLUDE_DIR "./include")

# Configure a header file for cmake settings
configure_file (
	"${PROJECT_INCLUDE_DIR}/config.hpp.in"
	"${PROJECT_INCLUDE_DIR}/config.hpp"
)

# Compiler arguments
if ("${CMAKE_CXX_COMPILER_ID}" MATCHES "GNU")
	set (CMAKE_CXX_FLAGS "-Wall -std=c++11 -I${PROJECT_INCLUDE_DIR}")
endif ()

# Includes
include_directories(${PROJECT_INCLUDE_DIR})

# Source
set (SOURCES ${PROJECT_SOURCE_DIR}/capacitor.cc ${PROJECT_SOURCE_DIR}/cap_array_sim.cc ${PROJECT_SOURCE_DIR}/terminal.cc ${PROJECT_SOURCE_DIR}/connection.cc ${PROJECT_SOURCE_DIR}/arraysystem.cc ${PROJECT_SOURCE_DIR}/sourcesystem.cc ${PROJECT_SOURCE_DIR}/drainsystem.cc ${PROJECT_SOURCE_DIR}/balancersystem.cc)

# Libraries
set (EXTRA_LIBS entityx)

# Executable
add_executable (CapArraySim ${SOURCES})
target_link_libraries (CapArraySim ${EXTRA_LIBS})
