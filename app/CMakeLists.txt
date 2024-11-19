project (app VERSION 1.0.0 LANGUAGES CXX)
include(GNUInstallDirs)

set(CLSERV_INCLUDE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(CLSERV_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/src)

file(GLOB CLSERV_HEADERS ${CLSERV_INCLUDE_DIR}/*.h)
file(GLOB CLSERV_SOURCE ${CLSERV_SOURCE_DIR}/*.cpp)

set(CLSERV_HEADERS_LIST ${CLSERV_INCLUDE_DIR})

include_directories(${CLSERV_HEADERS_LIST})

add_executable(client ${CLSERV_SOURCE_DIR}/client.cpp)
add_executable(server ${CLSERV_SOURCE_DIR}/server.cpp)


target_link_libraries(client PRIVATE transport.socket)
target_link_libraries(server PRIVATE transport.socket)


target_compile_features(client PUBLIC cxx_std_17)
target_compile_features(server PUBLIC cxx_std_17)
target_compile_options(client PRIVATE "-Wall")
target_compile_options(server PRIVATE "-Wall")

install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/client DESTINATION bin)
install(PROGRAMS ${CMAKE_CURRENT_BINARY_DIR}/server DESTINATION bin)



