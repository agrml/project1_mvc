set(SOURCE_FILES
#    externals/EasyBMP/include/EasyBMP.h
#    externals/EasyBMP/include/EasyBMP_BMP.h
#    externals/EasyBMP/include/EasyBMP_DataStructures.h
#    externals/EasyBMP/include/EasyBMP_VariousBMPutilities.h
#    externals/EasyBMP/src/EasyBMP.cpp
#    externals/EasyBMP/BSD_revised_license.txt
#    externals/EasyBMP/Makefile
#    include/align.h
#    include/io.h
#    include/matrix.h
#    include/matrix.hpp
    align.cpp
    io.cpp
    main.cpp
    matrix_example.cpp)



add_executable(align_project ${SOURCE_FILES}) # создание цели сборки, зависящей от таких-то файлов?
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR})

#target_link_libraries()