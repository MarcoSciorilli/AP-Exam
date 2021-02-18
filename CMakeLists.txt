cmake_minimum_required(VERSION 3.17)
project(AP_Exam C CXX)

set(CMAKE_C_STANDARD 11)

include_directories(exam/cpp/include)

add_executable(AP_Exam
        exam/cpp/include/bst.h
        exam/cpp/include/methods.h
        exam/cpp/include/main.cpp)