cmake_minimum_required(VERSION 3.10)

project(cbp VERSION 1.0)

add_executable(test file_util.cc test.cc)
target_include_directories(test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(test PRIVATE cxx_std_17)
target_link_libraries(test PRIVATE stdc++fs)




