project(prog.exe)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

file(GLOB CPPS "./*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})

target_include_directories(${PROJECT_NAME} PRIVATE include)

# ****** SFML   ******

find_package(SFML REQUIRED COMPONENTS system window graphics  )
target_link_libraries(${PROJECT_NAME} sfml-graphics sfml-window sfml-system)

