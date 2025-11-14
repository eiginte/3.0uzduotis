cmake_minimum_required(VERSION 3.10)

project(StudentuGrupe CXX)


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)


set(SOURCES
    main.cpp
    StudentuGrupe.cpp
    Studentas.cpp
)


add_executable(studentai ${SOURCES})


