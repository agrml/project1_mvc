set(SOURCE_FILES
        main.cpp

#        align.cpp
#        io.cpp
#        matrix.cpp
#        MatrixMath.cpp
#
#        model.cpp
#        view.cpp
#        controller.cpp
        )



add_executable(align_project ${SOURCE_FILES})
# todo: add lib rebuilding target
target_link_libraries(align_project ${CMAKE_SOURCE_DIR}/lib/EasyBMP/lib/libeasybmp.a)
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})