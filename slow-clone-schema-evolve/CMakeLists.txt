cmake_minimum_required(VERSION 3.12)
project(rename_map_member)

find_package(ROOT 6.16 CONFIG REQUIRED)
include("${ROOT_DIR}/RootMacros.cmake")
message(STATUS "Using ROOT ${ROOT_VERSION}")

add_library(HeaderV1 SHARED v1/Header.cxx)
target_link_libraries(HeaderV1 PUBLIC ROOT::Core)
target_include_directories(HeaderV1 PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/v1)
target_compile_definitions(HeaderV1 PUBLIC AS_OLD=1)
root_generate_dictionary(
  HeaderV1Dict
  v1/Header.h
  LINKDEF v1/LinkDef.h
  MODULE HeaderV1
)

add_library(HeaderV2 SHARED v2/Header.cxx v1/Header.cxx)
target_link_libraries(HeaderV2 PUBLIC ROOT::Core)
target_include_directories(HeaderV2 PUBLIC ${PROJECT_SOURCE_DIR})
root_generate_dictionary(
  HeaderV2Dict
  v1/Header.h
  v2/Header.h
  LINKDEF v2/LinkDef.h
  MODULE HeaderV2
)

add_executable(write write.cxx)
target_link_libraries(write PRIVATE HeaderV1 ROOT::TreePlayer)

add_executable(read-v1 read.cxx)
target_link_libraries(read-v1 PRIVATE HeaderV1 ROOT::TreePlayer)

add_executable(read-v2 read.cxx)
target_link_libraries(read-v2 PRIVATE HeaderV2 ROOT::TreePlayer)

add_executable(copy copy.cxx)
target_link_libraries(copy PRIVATE HeaderV2 ROOT::TreePlayer)
