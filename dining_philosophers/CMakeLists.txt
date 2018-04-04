set (CMAKE_CXX_STANDARD 11)

set (CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} "-Wall")

add_executable(
    dining_philosophers 
        "src/dining_philosophers.cpp"
		"include/Barrier.hpp"
		"src/Barrier.cpp"
)

target_include_directories(dining_philosophers PUBLIC "./include")

add_executable(
    deadlocked_philosophers 
        "src/deadlocked_philosophers.cpp"
		"include/Barrier.hpp"
		"src/Barrier.cpp"
)

target_include_directories(deadlocked_philosophers PUBLIC "./include")

add_executable(
    starving_philosophers
        "src/starving_philosophers.cpp"
		"include/Barrier.hpp"
		"src/Barrier.cpp"
)

target_include_directories(starving_philosophers PUBLIC "./include")

add_executable(
    semaphore_philosophers
        "src/semaphore_philosophers.cpp"
		"include/Barrier.hpp"
		"src/Barrier.cpp"
)

target_include_directories(semaphore_philosophers PUBLIC "./include")