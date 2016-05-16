# CMake minimum version
cmake_minimum_required (VERSION 2.8)

# Project Infomation
project (CriminalsRDancing)

add_compile_options(-std=c++11)

set (CMAKE_BUILD_TYPE "Debug")
set (CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAS} -O0 -Wall -g -ggdb")
set (CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# Add dirs
aux_source_directory (source SRC_DIR)

# Targets
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_executable(main ${SRC_DIR})
	target_link_libraries(main ${Boost_LIBRARIES})
endif()
