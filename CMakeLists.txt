cmake_minimum_required(VERSION 3.10)

# set the project name and version
project(can-sample LANGUAGES C CXX VERSION 1.0)

include(CheckFunctionExists)
include(CheckSymbolExists)
include(GNUInstallDirs)


# set the C++ standard
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)
set(CMAKcd ..E_CXX_EXTENSIONS OFF)

file(GLOB cansample_SRC
     "src/*.c"
     "src/*.cpp"

)

# add the executable
add_executable(can-sample ${cansample_SRC})



target_include_directories(can-sample PUBLIC "hdr")

message(STATUS "CMake version: ${CMAKE_VERSION}")


if(NOT CMAKE_BUILD_TYPE)
  set(CMAKE_BUILD_TYPE Release)
endif()

if(CMAKE_EXPORT_COMPILE_COMMANDS STREQUAL "")
  set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE BOOL "project default" FORCE)
endif()

# Add an option to enable treating warnings as errors
option(ENABLE_WERROR "Treat all compiler warnings as errors" ON)
option(BUILD_SHARED_LIBS "Build shared libraries" OFF)


if(ENABLE_WERROR)
  add_compile_options(-Werror)
endif()

add_definitions(-D_GNU_SOURCE)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wno-parentheses -Wsign-compare")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -fno-strict-aliasing")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSO_RXQ_OVFL=40")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DPF_CAN=29")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DAF_CAN=PF_CAN")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DN_SLCAN=17")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSCM_TIMESTAMPING_OPT_STATS=54")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DCLOCK_TAI=11")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSO_TXTIME=61")
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -DSCM_TXTIME=SO_TXTIME")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wno-parentheses -Wsign-compare")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-strict-aliasing")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSO_RXQ_OVFL=40")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DPF_CAN=29")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DAF_CAN=PF_CAN")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DN_SLCAN=17")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSCM_TIMESTAMPING_OPT_STATS=54")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DCLOCK_TAI=11")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSO_TXTIME=61")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DSCM_TXTIME=SO_TXTIME")

set (CMAKE_C_LINKER_WRAPPER_FLAG "-Wl")
set (CMAKE_CXX_LINKER_WRAPPER_FLAG "-Wl")

include_directories(.)
include_directories(./hdr)


set(PROGRAMS_CANLIB
  hdr
)


