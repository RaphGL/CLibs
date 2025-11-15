cmake_minimum_required(VERSION 3.15)

project(clibs)

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

if(CMAKE_BUILD_TYPE STREQUAL Debug)
  set(SANITIZERS -fsanitize=address,undefined)
  add_link_options(${SANITIZERS})
  add_compile_options(${SANITIZERS})
  message(STATUS "Enabled sanitizers with: ${SANITIZERS}")
endif()

# --- Adding libraries ---

add_subdirectory(bstr)

add_subdirectory(flag)
target_link_libraries(flag PRIVATE bstr m)

add_subdirectory(base64)

# --- Executables --- 

add_executable(bstr_test bstr/maintest.c)
target_link_libraries(bstr_test bstr)

add_executable(vec_test vec/maintest.c)
target_link_libraries(vec_test m)

add_executable(flag_test flag/maintest.c)
target_link_libraries(flag_test flag)

add_executable(base64_test base64/maintest.c)
target_link_libraries(base64_test base64)

# --- Testing ---

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  include(CTest)

  add_test(NAME bstr COMMAND bstr_test)
  add_test(NAME vec COMMAND vec_test)
  add_test(NAME flag COMMAND flag_test)
  add_test(NAME base64 COMMAND base64_test)
endif()
