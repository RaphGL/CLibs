cmake_minimum_required(VERSION 3.15)

project(bstr DESCRIPTION "high level string library")

add_library(bstr STATIC bstr.c)
target_compile_features(bstr PUBLIC c_std_11)

