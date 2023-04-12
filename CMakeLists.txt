cmake_minimum_required(VERSION 3.5)
project(lua_config)

set(CMAKE_CXX_STANDARD 17)

find_package(GLog REQUIRED)
set(GLOG_INCLUDE_DIRS /usr/local/include)
set(GLOG_LIBRARIES glog::glog)
include_directories(${GLOG_INCLUDE_DIRS})

find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

set(LUA_INCLUDE_DIRS /usr/include/lua5.2)
set(LUA_LIBRARIES lua5.2)
include_directories(${LUA_INCLUDE_DIRS})

include_directories(${PROJECT_SOURCE_DIR})

set(SRC_DIR lua_config)
add_library(lua_config
  ${SRC_DIR}/configuration_file_resolver.cc
  ${SRC_DIR}/lua_parameter_dictionary.cc
)
target_link_libraries(lua_config
  ${GLOG_LIBRARIES}
  ${LUA_LIBRARIES}
)

add_executable(lua_config_test ${SRC_DIR}/lua_parameter_dictionary_test.cc)
target_link_libraries(lua_config_test lua_config ${GTEST_BOTH_LIBRARIES} pthread)

add_executable(lua_config_test2 ${SRC_DIR}/real_test.cc lua_config/real_test.cc)
target_link_libraries(lua_config_test2 lua_config ${GTEST_BOTH_LIBRARIES} pthread)