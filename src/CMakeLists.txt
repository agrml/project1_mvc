set(SOURCE_FILES
    align.cpp
    io.cpp
    main.cpp
    matrix_example.cpp
    math.cpp)

include_directories(
        ${CMAKE_SOURCE_DIR}/../include
)

add_executable(align_project ${SOURCE_FILES}) # создание цели сборки, зависящей от таких-то файлов?
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#target_link_libraries()