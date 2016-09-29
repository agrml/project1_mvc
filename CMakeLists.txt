cmake_minimum_required(VERSION 3.6)
project(align_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -Wall -std=gnu++14")
# note: linebrakes are imposible in `set` comand. May use `add_definitions`, but it adds flagues only for compiller (not for linker)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wctor-dtor-privacy	-Wnon-virtual-dtor -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wno-unused-but-set-variable")

# assume that EasyBMP has already been built
include_directories(${CMAKE_SOURCE_DIR}/lib/EasyBMP/include)
#link_directories(${CMAKE_SOURCE_DIR}/lib/EasyBMP)

#find_package(EasyBMP)
#if(${EasyBMP_FOUND} EQUAL 1)
#    message("***easybmp found***")
#endif()

#find_library(EasyBMP
#        EasyBMP
#        PATHS ${CMAKE_SOURCE_DIR}/lib/EasyBMP
#        PATH_SUFFIXES lib obj)

add_subdirectory(src)
