
CMAKE_MINIMUM_REQUIRED(VERSION 3.13)

set(PROJECT_NAME "test")
project( ${PROJECT_NAME} )

file( GLOB sources *.cpp *.h )

add_executable( ${PROJECT_NAME} ${sources} )

# Eigen (Tuxfamily)
find_package(Eigen3)
MESSAGE(STATUS "Eigen3 include dir: ${EIGEN3_INCLUDE_DIR}")
target_include_directories( ${PROJECT_NAME} PRIVATE ${EIGEN3_INCLUDE_DIR} )

#target_precompile_headers( ${PROJECT_NAME} PRIVATE stdafx.h )

set_property( TARGET ${PROJECT_NAME} PROPERTY CXX_STANDARD 26 )

set_property( DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR} PROPERTY VS_STARTUP_PROJECT ${PROJECT_NAME} ) # VS property

