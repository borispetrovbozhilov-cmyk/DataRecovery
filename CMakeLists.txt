cmake_minimum_required(VERSION 4.0.2)
project(DataRecovery)

set(CMAKE_CXX_STANDARD 20)

add_executable(DataRecovery main.cpp
        FileHandling.cpp
        FileHandling.h
        StringUtils.cpp
        StringUtils.h
        TextCorruption.cpp
        TextCorruption.h
        GameLogic.cpp
        GameLogic.h
)
add_executable(test test.cpp
        TextCorruption.cpp
        TextCorruption.h
)

set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -static -static-libgcc -static-libstdc++")

# address sanitizer
if(MSVC)
    add_compile_options(/fsanitize=address)
else()
    add_compile_options(-fsanitize=address)
    link_libraries(-fsanitize=address)
endif()
