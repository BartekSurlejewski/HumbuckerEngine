cmake_minimum_required(VERSION 4.0)
project(CppSandbox)

set(CMAKE_CXX_STANDARD 14)

include_directories(CppSandbox)
include_directories(CppSandbox/DiningPhilosophers)

add_executable(CppSandbox
        CppSandbox/DiningPhilosophers/DiningPhilosophersManager.cpp
        CppSandbox/DiningPhilosophers/DiningPhilosophersManager.h
        CppSandbox/DiningPhilosophers/Fork.cpp
        CppSandbox/DiningPhilosophers/Fork.h
        CppSandbox/DiningPhilosophers/Philosopher.cpp
        CppSandbox/DiningPhilosophers/Philosopher.h
        CppSandbox/AlgorithmsImplementations.cpp
        CppSandbox/AlgorithmsImplementations.h
        CppSandbox/CppSandbox.cpp)
