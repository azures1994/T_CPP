cmake_minimum_required(VERSION 3.16.3)
project(T_CPP VERSION 0.1.0 LANGUAGES C CXX)

set(CMAKE_BUILD_TYPE Debug)

add_subdirectory(src/Template/)
add_subdirectory(src/rvalue/)
add_subdirectory(src/volatile/)
add_subdirectory(src/MiniVector/)

set(LIB_LIST )
set(SRC_LIST )

list(APPEND SRC_LIST main.cpp)

message(STATUS "[${PROJECT_NAME}] SRC_LIST: ${SRC_LIST}")
message(STATUS "[${PROJECT_NAME}] LIB_LIST: ${LIB_LIST}")
add_executable(${PROJECT_NAME} ${SRC_LIST})
target_link_libraries(${PROJECT_NAME} ${LIB_LIST})

set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/)

include(CTest)
enable_testing()

set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
