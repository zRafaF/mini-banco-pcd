cmake_minimum_required(VERSION 3.20)

project (mini_banco_pcd)

# set(SOURCES
    
# )

file(GLOB_RECURSE SRC_FILES src/*.c)

add_executable(mini_banco_pcd ${SRC_FILES})

target_include_directories(mini_banco_pcd
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)