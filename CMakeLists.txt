cmake_minimum_required(VERSION 3.6)
project(align_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O2 -g -Wall -std=gnu++14")
# note: linebrakes are imposible in `set` comand. May use `add_definitions`, but itadds flagues only for compiller (not for linker)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wctor-dtor-privacy	-Wnon-virtual-dtor -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wno-unused-but-set-variable")

add_subdirectory(src)
