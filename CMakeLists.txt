cmake_minimum_required(VERSION 3.12 FATAL_ERROR)
set(CMAKE_CXX_STANDARD 11)
project(kaleidoscope)

# This tells the compiler to not aggressively optimize and
# to include debugging information so that the debugger
# can properly read what's going on.
set(CMAKE_BUILD_TYPE Debug)

# Let's ensure -std=c++xx instead of -std=g++xx
set(CMAKE_CXX_EXTENSIONS OFF)

# Let's nicely support folders in IDE's
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

# Warning flags
if(MSVC)
    # warning level 3 and all warnings as errors
    add_compile_options(/W3 /WX)
else()
    # lots of warnings and all warnings as errors
    add_compile_options(-Wall -Wpedantic -Werror)
endif()

# FetchContent added in CMake 3.11, downloads during the configure step
include(FetchContent)

# FetchContent_MakeAvailable was not added until CMake 3.14
if(${CMAKE_VERSION} VERSION_LESS 3.14)
    include(cmake/add_FetchContent_MakeAvailable.cmake)
endif()

# Get catch2 from git
find_package(Git REQUIRED)
FetchContent_Declare(
        catch2
        GIT_REPOSITORY https://github.com/catchorg/Catch2.git
        GIT_TAG        v2.13.2
)

# Adds Catch2 testing library
FetchContent_GetProperties(catch2)
if(NOT catch2_POPULATED)
    FetchContent_Populate(catch2)
    add_library(catch2 OBJECT ${catch2_SOURCE_DIR}/single_include
            include/visualizer/kaleidoscope_app.h
            include/visualizer/sketchpad.h
            include/core/stroke_maker.h
            include/core/button.h
            include/core/slider.h
            include/visualizer/toolbar.h
            include/core/command_type.h
            include/core/saver.h)
    target_include_directories(catch2 INTERFACE ${catch2_SOURCE_DIR}/single_include)
endif()

# Add Native File Dialog Library
find_library(Git REQUIRED)
FetchContent_Declare(
        nativefiledialog
        GIT_REPOSITORY https://github.com/mlabbe/nativefiledialog.git
)

FetchContent_GetProperties(nativefiledialog)
if(NOT nativefiledialog_POPULATED)
    FetchContent_Populate(nativefiledialog)
endif()

set(NFD_SOURCES ${nativefiledialog_SOURCE_DIR}/src/nfd_common.c)
list(APPEND NFD_SOURCES ${nativefiledialog_SOURCE_DIR}/src/include)

if (WIN32)
    list(APPEND NFD_SOURCES ${nativefiledialog_SOURCE_DIR}/src/nfd_win.cpp)
elseif (APPLE)
    list(APPEND NFD_SOURCES ${nativefiledialog_SOURCE_DIR}/src/nfd_cocoa.m)
elseif (UNIX)
    list(APPEND NFD_SOURCES ${nativefiledialog_SOURCE_DIR}/src/nfd_gtk.c)
elseif (UNIX)
    message(FATAL_ERROR "Cannot detect your system, please report to https://github.com/aarcangeli/nativefiledialog-cmake/issues")
endif ()


add_library(nativefiledialog OBJECT ${NFD_SOURCES}
        include/core/saver.h)
target_include_directories(nativefiledialog INTERFACE ${NFD_SOURCES})

##FetchContent_GetProperties(nativefiledialog)
##if(NOT nativefiledialog_POPULATED)
##    FetchContent_Populate(nativefiledialog)
##    add_library(nativefiledialog OBJECT ${nativefiledialog_SOURCE_DIR}/src/include
##            include/core/saver.h)
##    target_include_directories(nativefiledialog INTERFACE ${nativefiledialog_SOURCE_DIR}/src/include)
##endif()

get_filename_component(CINDER_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cinder/../../" ABSOLUTE)
get_filename_component(APP_PATH "${CMAKE_CURRENT_SOURCE_DIR}/" ABSOLUTE)

include("${CINDER_PATH}/proj/cmake/modules/cinderMakeApp.cmake")

list(APPEND CORE_SOURCE_FILES
        src/core/stroke_maker.cc
        src/core/button.cc
        src/core/slider.cc
        src/core/saver.cc)

list(APPEND SOURCE_FILES
        ${CORE_SOURCE_FILES}
        src/visualizer/kaleidoscope_app.cc
        src/visualizer/sketchpad.cc
        src/visualizer/toolbar.cc)

list(APPEND TEST_FILES
        test/sample_test.cc)

ci_make_app(
        APP_NAME        kaleidoscope.cc
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         apps/cinder_app_main.cc ${SOURCE_FILES}
        INCLUDES        include
        LIBRARIES       nativefiledialog
)

ci_make_app(
        APP_NAME        kaleidoscope-test
        CINDER_PATH     ${CINDER_PATH}
        SOURCES         test/test_main.cc ${SOURCE_FILES} ${TEST_FILES}
        INCLUDES        include
        LIBRARIES       catch2
)

if(MSVC)
    set_property(TARGET kaleidoscope-test APPEND_STRING PROPERTY LINK_FLAGS " /SUBSYSTEM:CONSOLE")
endif()