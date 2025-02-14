cmake_minimum_required(VERSION 3.28)
project(FlappyBordAI)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

function(include_dependency libName gitURL gitTag)
    FetchContent_Declare(${libName}
            GIT_REPOSITORY ${gitURL}
            GIT_TAG    ${gitTag}
            GIT_SHALLOW TRUE
            GIT_PROGRESS TRUE
    )
    FetchContent_MakeAvailable(${libName})
endfunction()

set(LIB1 raylib)
find_package(${LIB1} QUIET)
if (NOT ${LIB1}_FOUND)
    include_dependency(${LIB1} https://github.com/raysan5/raylib.git 5.0)
endif()

add_executable(FlappyBordAI main.cpp
        main.cpp
        math/neuralmath.h
        math/neuralmath.cpp
        math/neuralmath_tests.cpp
        math/neuralmath_tests.h
        math/activation.h
        math/activation_tests.cpp
        math/activation_tests.h
)

target_include_directories(FlappyBordAI PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(FlappyBordAI PRIVATE ${LIB1})