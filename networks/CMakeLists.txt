include_directories(${CMAKE_CURRENT_SOURCE_DIR})
include_directories("${CMAKE_CURRENT_SOURCE_DIR}/activation")

add_subdirectory(parts)
set(networks_source classic_network.h feature_net.h fullhidden.h fullhidden.cpp taylornet.cpp)
add_library(libnetworks ${networks_source})

target_include_directories(libnetworks PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}")
target_link_libraries(libnetworks libparts)




