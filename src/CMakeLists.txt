set(SOURCE_FILES
        main.cpp

        matrix.cpp
        #                align.cpp
        #        io.cpp
#        MatrixMath.cpp
#
#        model.cpp
#        view.cpp
#        controller.cpp
        )



add_executable(align_project ${SOURCE_FILES})

# todo: add lib rebuilding target
target_link_libraries(align_project
        easybmp)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

# fixme
add_custom_command(TARGET align_project
        PRE_LINK
        COMMAND /bin/bash -c "make -C ${CMAKE_SOURCE_DIR}/lib/EasyBMP")