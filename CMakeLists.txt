cmake_minimum_required(VERSION 3.10)
project(StudentManager CXX)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
if(MSVC)
    add_compile_options(/utf-8)
endif()

add_executable(${PROJECT_NAME}
    main.cpp
    StudentManager.cpp
    class.cpp
)
