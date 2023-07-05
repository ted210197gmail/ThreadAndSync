cmake_minimum_required(VERSION 3.25)
project(ThreadAndSync)

set(CMAKE_CXX_STANDARD 17)

add_executable(ThreadAndSync main.cpp BasicPromise.cpp BasicPromise.h PromiseMyPractice.cpp PromiseMyPractice.h)
