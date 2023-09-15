cmake_minimum_required(VERSION 3.10)

project(proxy VERSION 1.0)

add_executable(proxy base64.cc proxy.cc)
target_compile_features(proxy PRIVATE cxx_std_17)
target_link_libraries(proxy PRIVATE pthread)

add_executable(base64_test base64.cc base64_test.cc)
target_compile_features(base64_test PRIVATE cxx_std_17)

