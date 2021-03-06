cmake_minimum_required (VERSION 3.1)

project(UrlEncoderProject LANGUAGES CXX)
include(CTest)

##############################################
# Set C++ standard
# Use c++11 if not set by the user
##############################################
if(NOT CMAKE_CXX_STANDARD)
    set(CMAKE_CXX_STANDARD 11)
endif()
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(CODE_COVERAGE "Enable coverage reporting" OFF)

##############################################
# Url Encoder Library
# Header only so no build
##############################################
add_library(url_encoder INTERFACE)
target_include_directories(url_encoder INTERFACE include/)

##############################################
# Test Builds
##############################################
if(BUILD_TESTING)
    enable_testing()
    add_subdirectory(test)
endif(BUILD_TESTING)

###########################################################
# Install target
###########################################################

install(DIRECTORY include/ DESTINATION include/)
