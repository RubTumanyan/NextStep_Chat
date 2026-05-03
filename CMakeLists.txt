cmake_minimum_required(VERSION 3.20)
project(NextStepChat VERSION 1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)      # -> don't use older versions

include_directories(${CMAKE_SOURCE_DIR}/shared)

add_subdirectory(server)
# add_subdirectory(client)
