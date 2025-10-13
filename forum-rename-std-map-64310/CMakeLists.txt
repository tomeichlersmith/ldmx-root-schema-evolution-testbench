cmake_minimum_required(VERSION 3.12)
project(rename_map_member)

find_package(ROOT 6.16 CONFIG REQUIRED)
include("${ROOT_DIR}/RootMacros.cmake")
message(STATUS "Using ROOT ${ROOT_VERSION}")

add_library(HeaderV1 SHARED Header_v1.cxx)
target_link_libraries(HeaderV1 PUBLIC ROOT::Core)
target_include_directories(HeaderV1 PUBLIC ${PROJECT_SOURCE_DIR})
root_generate_dictionary(
  HeaderV1Dict
  Header_v1.h
  LINKDEF LinkDef_v1.h
  MODULE HeaderV1
)

add_library(HeaderV2 SHARED Header_v2.cxx)
target_link_libraries(HeaderV2 PUBLIC ROOT::Core)
target_include_directories(HeaderV2 PUBLIC ${PROJECT_SOURCE_DIR})
root_generate_dictionary(
  HeaderV2Dict
  Header_v2.h
  LINKDEF LinkDef_v2.h
  MODULE HeaderV2
)

add_library(HeaderBoth SHARED Header_both.cxx)
target_link_libraries(HeaderBoth PUBLIC ROOT::Core)
target_include_directories(HeaderBoth PUBLIC ${PROJECT_SOURCE_DIR})
root_generate_dictionary(
  HeaderBothDict
  Header_both.h
  LINKDEF LinkDef_both.h
  MODULE HeaderBoth
)

enable_testing()
add_executable(write write.cxx)
target_link_libraries(write PRIVATE HeaderV1 ROOT::TreePlayer)
add_test(NAME write COMMAND write)

add_executable(read-v1 read.cxx)
target_link_libraries(read-v1 PRIVATE HeaderV1 ROOT::TreePlayer)
add_test(NAME read-v1 COMMAND read-v1)

add_executable(read-v2 read.cxx)
target_link_libraries(read-v2 PRIVATE HeaderV2 ROOT::TreePlayer)
target_compile_definitions(read-v2 PRIVATE USE_HEADER_V2=1)
add_test(NAME read-v2 COMMAND read-v2)

add_executable(read-both read.cxx)
target_link_libraries(read-both PRIVATE HeaderBoth ROOT::TreePlayer)
target_compile_definitions(read-both PRIVATE USE_HEADER_V2=1)
add_test(NAME read-both COMMAND read-both)

