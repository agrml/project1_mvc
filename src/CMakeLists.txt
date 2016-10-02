set(SOURCE_FILES
        main.cpp

#        matrix.cpp -- no! Read note at the end of matrix.hpp
        align.cpp
        io.cpp
        MatrixMath.cpp

        model.cpp
        view.cpp
        controller.cpp
        Cli.cpp Cli.hpp)


# *********************CLI***********************
# todo: implement switching view mod in compil time
add_executable(align_project_CLI ${SOURCE_FILES})
target_link_libraries(align_project_CLI
        easybmp
        ${GLOG_LIBRARIES}
)
# fixme
add_custom_command(TARGET align_project_CLI
        PRE_LINK
        COMMAND /bin/bash -c "make -C ${CMAKE_SOURCE_DIR}/lib/EasyBMP")

# *********************GUI***********************
# todo: implement


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

