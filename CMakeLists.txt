cmake_minimum_required(VERSION 3.19)
project(FinalProject)

set(CMAKE_CXX_STANDARD 14)

include_directories(FinalProject)
include_directories(FinalProject/Debug)

add_executable(FinalProject
        FinalProject/Debug/FinalProject.pch
        FinalProject/Adaptor.cpp
        FinalProject/Adaptor.h
        FinalProject/Book.cpp
        FinalProject/Book.h
        FinalProject/File.cpp
        FinalProject/File.h
        FinalProject/FinalProject.cpp
        FinalProject/Library.cpp
        FinalProject/Library.h
        FinalProject/stdafx.cpp
        FinalProject/stdafx.h
        FinalProject/Student.cpp
        FinalProject/Student.h
        FinalProject/targetver.h)
