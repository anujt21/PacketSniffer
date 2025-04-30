cmake_minimum_required(VERSION 3.10)
project(PacketSniffer)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/include)

# Force C++ mode (for tools like clang)
add_compile_options(
    -x c++
)

# Find the libpcap package
find_library(PCAP_LIBRARY pcap REQUIRED)

# Find all source files
file(GLOB SOURCES
  ${CMAKE_SOURCE_DIR}/src/base/*.cpp
  ${CMAKE_SOURCE_DIR}/src/application/*.cpp
  ${CMAKE_SOURCE_DIR}/src/network/*.cpp
  ${CMAKE_SOURCE_DIR}/src/link/*.cpp
  ${CMAKE_SOURCE_DIR}/src/transport/*.cpp
  ${CMAKE_SOURCE_DIR}/src/session/*.cpp
  ${CMAKE_SOURCE_DIR}/src/utils/*.cpp
  ${CMAKE_SOURCE_DIR}/src/*.cpp
  ${CMAKE_SOURCE_DIR}/main.cpp
)

# Create executable
add_executable(${PROJECT_NAME} ${SOURCES})

# Link against libpcap
target_link_libraries(${PROJECT_NAME} ${PCAP_LIBRARY})

# Install target
install(TARGETS ${PROJECT_NAME} DESTINATION bin)

