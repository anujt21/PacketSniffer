cmake_minimum_required(VERSION 3.10)
project(PacketSniffer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Find the libpcap package
find_library(PCAP_LIBRARY pcap REQUIRED)

# Find all source files
file(GLOB SOURCES
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/main.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against libpcap
target_link_libraries(${PROJECT_NAME} ${PCAP_LIBRARY})

# Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

