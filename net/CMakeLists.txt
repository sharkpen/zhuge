cmake_minimum_required(VERSION 3.10)

project(net VERSION 1.0)

add_executable(ring_buffer_test ring_buffer_test.cc)
target_include_directories(ring_buffer_test PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_features(ring_buffer_test PRIVATE cxx_std_17)
target_link_libraries(ring_buffer_test PRIVATE pthread)


#add_executable(data_read_thread_test data_read_thread_test.cc)
#target_include_directories(data_read_thread_test  PUBLIC
#  ${CMAKE_CURRENT_SOURCE_DIR}
#  /usr/local/include)
#target_compile_features(data_read_thread_test PRIVATE cxx_std_17)
#target_link_libraries(data_read_thread_test PUBLIC /usr/local/lib64)
#target_link_libraries(data_read_thread_test PRIVATE
#  pthread
#  rte_eal
#  rte_ethdev
#  rte_mbuf
#  rte_mempool
#  )
#target_compile_options(data_read_thread_test PRIVATE -mssse3)

