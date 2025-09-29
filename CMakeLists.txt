cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 23)
project(symbol_remover)

add_executable(app 
    main.cpp
    parser.cpp
    process.cpp
)