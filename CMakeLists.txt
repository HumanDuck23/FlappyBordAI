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
        src/math/neuralmath.h
        src/math/neuralmath.cpp
        src/math/neuralmath_tests.cpp
        src/math/neuralmath_tests.h
        src/math/activation.h
        src/math/activation_tests.cpp
        src/math/activation_tests.h
        src/math/randomutil.h
        src/neuralnet/Layer.h
        src/neuralnet/Layer.cpp
        src/neuralnet/layer_tests.h
        src/neuralnet/layer_tests.cpp
        src/neuralnet/Network.h
        src/neuralnet/Network.cpp
        src/neuralnet/network_tests.h
        src/neuralnet/network_tests.cpp
        src/game/GameRect.h
        src/game/GameRect.cpp
        src/game/Pipe.h
        src/game/Pipe.cpp
        src/game/Bord.h
        src/game/Bord.cpp
        src/game/FlappyBord.h
        src/game/FlappyBord.cpp
)

target_include_directories(FlappyBordAI PRIVATE ${raylib_INCLUDE_DIRS})
target_link_libraries(FlappyBordAI PRIVATE ${LIB1})