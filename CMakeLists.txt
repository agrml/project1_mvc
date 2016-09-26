cmake_minimum_required(VERSION 3.6)
project(align_project)

message("Cmake is able to speak! Starting...")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -Wall -std=c++0x")  # ${CMAKE_CXX_FLAGS} -- nothing if not defined
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wformat-security -Wignored-qualifiers -Winit-self
		-Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith \
		-Wtype-limits -Wempty-body -Wlogical-op \
		-Wmissing-field-initializers -Wctor-dtor-privacy \
		-Wnon-virtual-dtor -Wstrict-null-sentinel -Wold-style-cast \
		-Woverloaded-virtual -Wsign-promo -Weffc++

        -Wno-unused-variable -Wno-unused-but-set-variable")

set(PROJECT_SOURCE_DIR src)  # for "src:include": ":" instead of whitespace
set(PROJECT_BUILD_DIR build)
#OBJ_DIR = $(BUILD_DIR)/obj
set(PROJECT_BINARY_DIR $(PROJECT_BUILD_DIR)/bin)
#DEP_DIR = $(BUILD_DIR)/deps  # dependences (automaticly recompile project if a .hh chenged)
set(PROJECT_LIB_DIR externals)

#[[
set (CMAKE_INCLUDE_PATH ${${PROJECT}_SOURCE_DIR})
set (CMAKE_LIBRARY_PATH ${${PROJECT}_LIB_DIR})
set (EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/${${PROJECT}_BINARY_DIR})
set (CMAKE_VERBOSE_MAKEFILE ON)
set (CMAKE_BUILD_TYPE Debug)
]]

# add a list of dirs to the list in which headers will be searched
include_directories(
        ${CMAKE_SOURCE_DIR}/include
        ${CMAKE_SOURCE_DIR}/externals/EasyBMP/include
)

set(SOURCE_FILES
            externals/EasyBMP/include/EasyBMP.h
            externals/EasyBMP/include/EasyBMP_BMP.h
            externals/EasyBMP/include/EasyBMP_DataStructures.h
            externals/EasyBMP/include/EasyBMP_VariousBMPutilities.h
            externals/EasyBMP/src/EasyBMP.cpp

        src/core/align.hpp
        src/core/io.hpp
        src/core/matrix.hpp
        src/core/matrix.cpp
        src/core/MatrixMath.hpp
        src/core/align.cpp
        src/core/io.cpp
        src/core/main.cpp
        src/core/matrix_example.cpp
        src/core/MatrixMath.cpp
        )

message("going to process subdirs...")
#add_subdirectory(src)  # jump to subdir in search of an CMakeLists for it's processing. "process_subdirectory"

#add_subdirectory(externals)
add_custom_target(align_project COMMAND make -C ${PROJECT_SOURCE_DIR}/externals/EasyBMP
        CLION_EXE_DIR=${PROJECT_BINARY_DIR})

add_executable(align_project ${SOURCE_FILES}) # создание цели сборки, зависящей от таких-то файлов?

# LDFLAGS = -leasybmp

