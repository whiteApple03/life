project(prog)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++1y")

file(GLOB CPPS "src/*.cpp")

add_executable(${PROJECT_NAME} ${CPPS})

target_include_directories(${PROJECT_NAME} PRIVATE includes/database includes)

# ****** CTESTS ******

add_executable(test ./tests/main.cpp ./src/input.cpp ./src/logics.cpp ./tests/tests.cpp)

target_include_directories(test PRIVATE thirdparty includes/database includes)

add_test(NAME test COMMAND test)


