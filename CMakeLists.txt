cmake_minimum_required(VERSION 3.0)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14")

include_directories("/usr/local/Cellar/spdlog/1.3.1/include/")

project("Graph")

# MySql linking stuff borrowed from https://osdevlab.blogspot.com/2016/02/how-to-install-mysql-connectorc-on.html
set(MYSQLCONNECTORCPP_ROOT_DIR
        "${MYSQLCONNECTORCPP_ROOT_DIR}"
        CACHE
        PATH
        "Where to start looking for this component.")

if(WIN32)
    find_path(MYSQLCONNECTORCPP_INCLUDE_DIR
            NAMES
            mysql_connection.h
            PATHS
            "C:\\Program Files"
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            include)

    find_library(MYSQLCONNECTORCPP_LIBRARY
            NAMES
            mysqlcppconn
            mysqlcppconn-static
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            lib)

else()
    find_path(MYSQLCONNECTORCPP_INCLUDE_DIR
            mysql_connection.h
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            include)

    find_library(MYSQLCONNECTORCPP_LIBRARY
            NAMES
            mysqlcppconn
            mysqlcppconn-static
            HINTS
            ${MYSQLCONNECTORCPP_ROOT_DIR}
            PATH_SUFFIXES
            lib64
            lib)
endif()

mark_as_advanced(MYSQLCONNECTORCPP_INCLUDE_DIR MYSQLCONNECTORCPP_LIBRARY)

include(FindPackageHandleStandardArgs)
find_package_handle_standard_args(MysqlConnectorCpp
        DEFAULT_MSG
        MYSQLCONNECTORCPP_INCLUDE_DIR
        MYSQLCONNECTORCPP_LIBRARY)

if(MYSQLCONNECTORCPP_FOUND)
    set(MYSQLCONNECTORCPP_INCLUDE_DIRS "${MYSQLCONNECTORCPP_INCLUDE_DIR}") # Add any dependencies here
    set(MYSQLCONNECTORCPP_LIBRARIES "${MYSQLCONNECTORCPP_LIBRARY}") # Add any dependencies here
    mark_as_advanced(MYSQLCONNECTORCPP_ROOT_DIR)
endif()

find_library(spdlog CONFIG REQUIRED)

add_executable(
  "${PROJECT_NAME}" 
  main.cpp
  Graph.cpp
  node.cpp
  database.cpp
)

target_link_libraries("${PROJECT_NAME}" ${MYSQLCONNECTORCPP_LIBRARY})

add_executable(
  "${PROJECT_NAME}Tests"
  tests/main.cpp
  Graph.cpp
  node.cpp
  database.cpp
)

target_link_libraries("${PROJECT_NAME}Tests" ${MYSQLCONNECTORCPP_LIBRARY})
