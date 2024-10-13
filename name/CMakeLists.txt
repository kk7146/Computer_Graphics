cmake_minimum_required(VERSION 3.24)
PROJECT ( "test" )

SET ( OUTPUT_ELF
        "test.out"
        )
SET ( SRC_FILES
        "./main.cpp"
        )

# 공통 컴파일러
SET ( CMAKE_CXX_COMPILER "g++" )

find_package(OpenGL REQUIRED)


set(GLUT_LIBRARIES libglut.3.dylib)
set(GLUT_INCLUDE_DIRS /usr/local/include)
set(GLUT_LIBRARY_DIRS /usr/local/lib)

INCLUDE_DIRECTORIES ( ${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS} )
ADD_COMPILE_OPTIONS ( "-g" )

LINK_LIBRARIES ( ${OPENGL_LIBRRARIES} ${GLUT_LIBRARIES})

LINK_DIRECTORIES ( ${OPENGL_LIBRARY_DIRS} ${GLUT_LIBRARY_DIRS})

ADD_EXECUTABLE( ${OUTPUT_ELF} ${SRC_FILES} )
target_link_libraries( ${OUTPUT_ELF} ${OPENGL_LIBRARIES} )