# CMake minimum version
cmake_minimum_required(VERSION 2.8)

# Project Infomation
project(CriminalsRDancing)

add_compile_options(-std=c++11)

set(CMAKE_BUILD_TYPE "Debug")
set(CMAKE_CXX_FLAGS_DEBUG "$ENV{CXXFLAS} -O0 -Wall -g -ggdb")
set(CMAKE_CXX_FLAGS_RELEASE "$ENV{CXXFLAGS} -O3 -Wall")

# Add dirs
aux_source_directory(client_src CLI_SRC_DIR)
aux_source_directory(server_src SER_SRC_DIR)

# Targets
set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME ON)

find_package(Boost 1.60.0 REQUIRED system regex thread)
if(Boost_FOUND)
	include_directories(${Boost_INCLUDE_DIRS})
	add_executable(client ${CLI_SRC_DIR})
	add_executable(server ${SER_SRC_DIR})
	target_link_libraries(client
		${Boost_LIBRARIES}
		${Boost_SYSTEM_LIBRARIES}
		${Boost_FILESYSTEM_LIBRARIES}
		${Boost_LOG_LIBRARIES}
		${Boost_LOG_SETUP_LIBRARIES}
		${Boost_THREAD_LIBRARY})
	target_link_libraries(server
		${Boost_LIBRARIES}
		${Boost_SYSTEM_LIBRARIES}
		${Boost_FILESYSTEM_LIBRARIES}
		${Boost_LOG_LIBRARIES}
		${Boost_LOG_SETUP_LIBRARIES}
		${Boost_THREAD_LIBRARY})
endif()

