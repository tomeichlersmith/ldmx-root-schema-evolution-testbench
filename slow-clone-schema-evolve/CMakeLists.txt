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

set(executables write read copy)
foreach(executable ${executables})
  add_executable(${executable}-v1 ${executable}.cxx)
  target_link_libraries(${executable}-v1 PRIVATE HeaderV1 ROOT::TreePlayer)

  add_executable(${executable}-v2 ${executable}.cxx)
  target_link_libraries(${executable}-v2 PRIVATE HeaderV2 ROOT::TreePlayer)
  target_compile_definitions(${executable}-v2 PRIVATE USE_HEADER_V2=1)
endforeach()
