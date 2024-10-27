cmake_minimum_required(VERSION 3.10)

project(base64 DESCRIPTION "base64 implemention")

add_library(base64 STATIC base64.c)
target_link_libraries(base64 PRIVATE m)
target_compile_features(base64 PUBLIC c_std_11)
