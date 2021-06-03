cmake_minimum_required(VERSION 3.12)

set(APP Polynomial)
project(${APP} LANGUAGES CXX)

add_executable(${APP}
    main.cpp
    polynomial.cpp
)

target_compile_features(${APP} PRIVATE
    cxx_std_17
)
