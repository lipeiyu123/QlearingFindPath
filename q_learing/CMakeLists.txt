cmake_minimum_required(VERSION 3.10.2)

project(Qlearing)

add_subdirectory(../random  random_binary_dir)
set(random_DIR ${PROJECT_SOURCE_DIR} ../random)

include_directories(${PROJECT_SOURCE_DIR}
    ${random_DIR} 
)

aux_source_directory(${PROJECT_SOURCE_DIR} Qlearing_FILES)
add_library(${PROJECT_NAME} STATIC ${Qlearing_FILES})

target_link_libraries(${PROJECT_NAME} random)

