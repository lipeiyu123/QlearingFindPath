cmake_minimum_required(VERSION 3.10.2)

project(Q_learing)

SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")

add_subdirectory(q_learing)


set(Qlearing_DIR ${PROJECT_SOURCE_DIR}/q_learing)

include_directories(${PROJECT_SOURCE_DIR}
    ${Qlearing_DIR} 
)


add_executable(${PROJECT_NAME} main.cpp )
target_link_libraries(${PROJECT_NAME} Qlearing)

