cmake_minimum_required(VERSION 3.12)
project(rename_map_member)

find_package(ROOT 6.16 CONFIG REQUIRED)
include("${ROOT_DIR}/RootMacros.cmake")
message(STATUS "Using ROOT ${ROOT_VERSION}")

set(options v1 v2 both)
foreach(option ${options})
  add_library(Header${option} SHARED ${option}/Header.cxx)
  target_link_libraries(Header${option} PUBLIC ROOT::Core)
  target_include_directories(Header${option} PUBLIC ${PROJECT_SOURCE_DIR}/${option})
  root_generate_dictionary(
    Header${option}Dict
    ${option}/Header.h
    LINKDEF ${option}/LinkDef.h
    MODULE Header${option}
  )

  add_executable(read-${option} read.cxx)
  target_link_libraries(read-${option} PRIVATE Header${option} ROOT::TreePlayer)
endforeach()

add_executable(write write.cxx)
target_link_libraries(write PRIVATE Headerv1 ROOT::TreePlayer)
