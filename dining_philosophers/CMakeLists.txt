set (CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")

add_executable(
    dining_philosophers 
        "src/dining_philosophers.cpp"
		"include/Barrier.hpp"
		"src/Barrier.cpp"
)

target_include_directories(dining_philosophers PUBLIC "./include")