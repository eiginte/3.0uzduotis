cmake_minimum_required(VERSION 3.10)
project(StudentuGrupe CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(SOURCES
    main.cpp
    Studentas.cpp
    StudentuGrupe.cpp
)

add_executable(studentai ${SOURCES})

set(GTEST_DIR "googletest-main/googletest")
set(GTEST_SOURCES
    ${GTEST_DIR}/src/gtest-all.cc
)

add_executable(tests
    test.cpp
    Studentas.cpp
    StudentuGrupe.cpp
    ${GTEST_SOURCES}
)

target_include_directories(tests PRIVATE
    ${GTEST_DIR}/include
    ${GTEST_DIR}
)


if(UNIX)
    target_link_libraries(tests pthread)
endif()

