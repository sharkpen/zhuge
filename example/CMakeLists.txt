cmake_minimum_required(VERSION 3.10)

project(example VERSION 1.0)

add_executable(socket_echo_server echo_server.cc)
target_compile_features(socket_echo_server PRIVATE cxx_std_17)

add_executable(client client.cc)
target_compile_features(client PRIVATE cxx_std_17)
