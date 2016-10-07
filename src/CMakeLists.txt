set(SOURCE_FILES
        main.cpp

#        matrix.cpp -- no! Read note at the end of matrix.hpp

        align.cpp
        io.cpp
        MatrixMath.cpp

        AppModel.cpp
        SubViews.cpp
        AppController.cpp
        Ui.cpp
)

# Instruct CMake to run moc automatically when needed.
set(CMAKE_AUTOMOC ON)

include_directories(
        ${CMAKE_CURRENT_BINARY_DIR} # for Qt-generated moc files
)

# *********************CLI***********************
# todo: implement switching view mod in compil time
add_executable(align_project ${SOURCE_FILES})
target_link_libraries(align_project
        easybmp
        ${GLOG_LIBRARIES}
        Qt5::Core  # ${Qt5Core_INCLUDE_LIBRARIES} ???
        )
# fixme
add_custom_command(TARGET align_project
        PRE_LINK
        COMMAND /bin/bash -c "make -C ${CMAKE_SOURCE_DIR}/lib/EasyBMP")

# *********************GUI***********************
# todo: implement


set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

