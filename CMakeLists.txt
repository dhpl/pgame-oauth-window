cmake_minimum_required(VERSION 3.21)
project(PGameOAuthWindows VERSION 1.3.11 LANGUAGES C CXX)

if(NOT WIN32)
  message(FATAL_ERROR "PGame OAuth Windows SDK only supports Windows")
endif()

add_library(PGameSDK SHARED IMPORTED GLOBAL)
set_target_properties(PGameSDK PROPERTIES
  IMPORTED_IMPLIB "${CMAKE_CURRENT_LIST_DIR}/native/lib/libPGameSDK.dll.a"
  IMPORTED_LOCATION "${CMAKE_CURRENT_LIST_DIR}/native/bin/PGameSDK.dll"
  INTERFACE_INCLUDE_DIRECTORIES "${CMAKE_CURRENT_LIST_DIR}/native/include"
)
add_library(PGameSDK::PGameSDK ALIAS PGameSDK)
