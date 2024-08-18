cmake_minimum_required(VERSION 3.10)

project(vec DESCRIPTION "dynamically growable vector structure")

add_library(vec STATIC vector.c)
target_link_libraries(vec PRIVATE m)
target_compile_features(vec PUBLIC c_std_11)
