cmake_minimum_required(VERSION 3.6)
project(align_project)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -O0 -g -Wall -std=gnu++14")
# note: linebrakes are imposible in `set` comand. May use `add_definitions`, but it adds flagues only for compiller (not for linker)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Werror -Wformat-security -Wignored-qualifiers -Winit-self -Wswitch-default -Wfloat-equal -Wshadow -Wpointer-arith -Wtype-limits -Wempty-body -Wlogical-op -Wmissing-field-initializers -Wctor-dtor-privacy	-Wnon-virtual-dtor -Wstrict-null-sentinel -Wold-style-cast -Woverloaded-virtual -Wsign-promo -Weffc++")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-unused-variable -Wno-unused-but-set-variable")

find_package(PkgConfig)
pkg_check_modules(GLOG REQUIRED libglog)

find_package(Qt5Core)
find_package(Qt5Widgets)


# assume that EasyBMP has already been built
include_directories(
#        SYSTEM
        ${CMAKE_SOURCE_DIR}/src
        ${CMAKE_SOURCE_DIR}/lib/EasyBMP/include
        ${GLOG_INCLUDE_DIRS}
        ${Qt5Core_INCLUDE_DIRS}
        ${Qt5Widgets_INCLUDE_DIRS}
)

link_directories(
        ${CMAKE_SOURCE_DIR}/lib/EasyBMP/lib
        ${GLOG_LIBRARY_DIRS}
        Qt5::Core
        Qt5::Widgets

)


## We need add -DQT_WIDGETS_LIB when using QtWidgets in Qt 5.
#add_definitions(${Qt5Widgets_DEFINITIONS})

## Executables fail to build with Qt 5 in the default configuration
## without -fPIE. We add that here.
#set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

#find_package(EasyBMP)
#if(${EasyBMP_FOUND} EQUAL 1)
#    message("***easybmp found***")
#endif()

#find_library(EasyBMP
#        EasyBMP
#        PATHS ${CMAKE_SOURCE_DIR}/lib/EasyBMP
#        PATH_SUFFIXES lib obj)

add_subdirectory(src)