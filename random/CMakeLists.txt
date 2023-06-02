cmake_minimum_required(VERSION 3.10.2)

project(random)

aux_source_directory(${PROJECT_SOURCE_DIR} random_FILES)
add_library(${PROJECT_NAME} STATIC ${random_FILES})
