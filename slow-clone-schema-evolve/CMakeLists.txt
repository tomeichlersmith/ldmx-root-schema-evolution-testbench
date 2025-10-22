cmake_minimum_required(VERSION 3.12)
project(rename_map_member)

find_package(ROOT 6.16 CONFIG REQUIRED)
include("${ROOT_DIR}/RootMacros.cmake")
message(STATUS "Using ROOT ${ROOT_VERSION}")

add_library(HeaderV1 SHARED v1/Header.cxx)
target_link_libraries(HeaderV1 PUBLIC ROOT::Core)
target_include_directories(HeaderV1 PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/v1)
root_generate_dictionary(
  HeaderV1Dict
  v1/Header.h
  LINKDEF v1/LinkDef.h
  MODULE HeaderV1
)

add_library(HeaderV2 SHARED v2/Header.cxx)
target_link_libraries(HeaderV2 PUBLIC ROOT::Core)
target_include_directories(HeaderV2 PUBLIC ${PROJECT_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/v2)
root_generate_dictionary(
  HeaderV2Dict
  v2/Header.h
  LINKDEF v2/LinkDef.h
  MODULE HeaderV2
)

set(executables write read)
foreach(executable ${executables})
  add_executable(${executable}-v1 ${executable}.cxx)
  target_link_libraries(${executable}-v1 PRIVATE HeaderV1 ROOT::TreePlayer)

  add_executable(${executable}-v2 ${executable}.cxx)
  target_link_libraries(${executable}-v2 PRIVATE HeaderV2 ROOT::TreePlayer)
  target_compile_definitions(${executable}-v2 PRIVATE USE_HEADER_V2=1)
endforeach()

add_executable(copy-v1 copy.cxx)
target_link_libraries(copy-v1 PRIVATE HeaderV1 ROOT::TreePlayer)

add_executable(copy-v2-clone-tree copy.cxx)
target_link_libraries(copy-v2-clone-tree PRIVATE HeaderV2 ROOT::TreePlayer)
target_compile_definitions(copy-v2-clone-tree PRIVATE USE_HEADER_V2=1 USE_TTREE_CLONETREE=1)

add_executable(copy-v2-manual copy.cxx)
target_link_libraries(copy-v2-manual PRIVATE HeaderV2 ROOT::TreePlayer)
target_compile_definitions(copy-v2-manual PRIVATE USE_HEADER_V2=1 MANUAL_ADDR_SYNC=1)

add_executable(copy-v2-copy-addr copy.cxx)
target_link_libraries(copy-v2-copy-addr PRIVATE HeaderV2 ROOT::TreePlayer)
target_compile_definitions(copy-v2-copy-addr PRIVATE USE_HEADER_V2=1)
