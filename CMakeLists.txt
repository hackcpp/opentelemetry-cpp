cmake_minimum_required(VERSION 3.5)

project("opentelemetry-cpp")

macro(use_cxx11)
  if(CMAKE_VERSION VERSION_LESS "3.1")
    if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
      set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
    endif()

  else()
    set(CMAKE_CXX_STANDARD 11)
    message(STATUS "CMAKE_CXX_STANDARD=${CMAKE_CXX_STANDARD}")
  endif()
endmacro(use_cxx11)


# 添加头部文件
include_directories(
  .
  ./api/include
  ./sdk/include)
 
# 添加代码源文件
aux_source_directory(./sdk/src SOURCE_FILES)
aux_source_directory(./sdk/src/metrics SOURCE_FILES)
aux_source_directory(./sdk/src/metrics/state SOURCE_FILES)
aux_source_directory(./sdk/src/metrics/aggregation SOURCE_FILES)

aux_source_directory(./sdk/src/resource SOURCE_FILES)

 
# 输出
add_library(opentelemetry STATIC ${SOURCE_FILES})

# 添加可执行文件
add_executable(test_opentelemetry main.cpp)
target_link_libraries(test_opentelemetry opentelemetry)
 

message(STATUS "")
message(STATUS "")
message(STATUS "${TARGET_NAME} configuration summary:")
message(STATUS "")

message(STATUS "  SOURCE_FILES .................... : ${SOURCE_FILES}")
message(STATUS "  Build type ...................... : ${CMAKE_BUILD_TYPE}")
message(STATUS "  Install prefix .................. : ${CMAKE_INSTALL_PREFIX}")
message(STATUS "  C compiler ...................... : ${CMAKE_C_COMPILER}")
message(STATUS "  CMAKE_C_FLAGS ................... : ${CMAKE_C_FLAGS}")
message(STATUS "  CMAKE_C_FLAGS_RELEASE ........... : ${CMAKE_C_FLAGS_RELEASE}")
message(STATUS "  CMAKE_C_FLAGS_DEBUG ............. : ${CMAKE_C_FLAGS_DEBUG}")
message(STATUS "  C++ compiler .................... : ${CMAKE_CXX_COMPILER}")
message(STATUS "  CMAKE_CXX_FLAGS ................. : ${CMAKE_CXX_FLAGS}")
message(STATUS "  CMAKE_CXX_FLAGS_RELEASE ......... : ${CMAKE_CXX_FLAGS_RELEASE}")
message(STATUS "  CMAKE_CXX_FLAGS_DEBUG ........... : ${CMAKE_CXX_FLAGS_DEBUG}")
message(STATUS "  THIRD_PARTY_LIBS_PATH............ : ${libpath}")
message(STATUS "  BONREE_SDK_VERSION............... : ${BONREE_SDK_VERSION}")
message(STATUS "  ONREE_SDK_NAME .................. : ${SDK_NAME}")
message(STATUS "")
message(STATUS "")
