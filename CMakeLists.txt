cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

project("Graph")

add_executable(
  "${PROJECT_NAME}" 
  "main.cpp"
)

# install(TARGETS "${PROJECT_NAME}" DESTINATION bin)
# install(FILES "main.cpp" DESTINATION src)
