cmake_minimum_required(VERSION 3.10)

project(flag DESCRIPTION "flag parsing library")

add_library(flag flag.c)
target_compile_features(flag PUBLIC c_std_11)
