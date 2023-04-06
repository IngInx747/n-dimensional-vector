cmake_minimum_required(VERSION 3.5.0)
project(NVEC VERSION 1.0 LANGUAGES CXX)

string(COMPARE EQUAL "${CMAKE_CURRENT_SOURCE_DIR}" "${CMAKE_SOURCE_DIR}" NVEC_STANDALONE)

if (NVEC_STANDALONE)
    add_subdirectory(test/template)
endif()
