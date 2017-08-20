cmake_minimum_required(VERSION 3.0)
project(create_mesh)

# -DTRILIBRARY is required to create the triangle object file 
set(CMAKE_C_FLAGS "-DTRILIBRARY")

set(SOURCE_DIR "createmesh_files")
set(TRIANGLE "lib/triangle_files")

# Include path for Python header files
include_directories(${PYTHON_INCLUDE_DIRS})

# set path for triangle header file
include_directories(lib/triangle_files)

add_subdirectory(lib/pybind11)
pybind11_add_module(createmesh ${SOURCE_DIR}/wrap_call_triangle.cpp
                               ${SOURCE_DIR}/calltri.cpp
                               ${TRIANGLE}/triangle.c)


