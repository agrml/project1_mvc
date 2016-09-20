cmake_minimum_required(VERSION 3.6)
project(align_project)

message("Cmake is able to speak! Starting...")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -Wall -std=c++0x")  # ${CMAKE_CXX_FLAGS} -- nothing if not defined
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wformat-security -Wignored-qualifiers -Winit-self
		-Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith \
		-Wtype-limits -Wempty-body -Wlogical-op \
		-Wmissing-field-initializers -Wctor-dtor-privacy \
		-Wnon-virtual-dtor -Wstrict-null-sentinel -Wold-style-cast \
		-Woverloaded-virtual -Wsign-promo -Weffc++")

set(PROJECT_SOURCE_DIR src:include)  # : instead of whitespace
set(BUILD_DIR build)
#OBJ_DIR = $(BUILD_DIR)/obj
set(BIN_DIR $(BUILD_DIR)/bin)
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
#            externals/EasyBMP/include/EasyBMP.h
#            externals/EasyBMP/include/EasyBMP_BMP.h
#            externals/EasyBMP/include/EasyBMP_DataStructures.h
#            externals/EasyBMP/include/EasyBMP_VariousBMPutilities.h
#            externals/EasyBMP/src/EasyBMP.cpp
#            externals/EasyBMP/BSD_revised_license.txt
#            externals/EasyBMP/Makefile

            include/align.h
            include/io.h
            include/matrix.h
            include/matrix.hpp
            include/math.hpp
            src/align.cpp
            src/io.cpp
            src/main.cpp
            src/matrix_example.cpp
            src/math.cpp
        src/MyMatrix.cpp src/MyMatrix.hpp)

message("going to process subdirs...")
#add_subdirectory(src)  # jump to subdir in search of an CMakeLists for it's processing. "process_subdirectory"
#add_subdirectory(externals)

add_executable(align_project ${SOURCE_FILES}) # создание цели сборки, зависящей от таких-то файлов?


