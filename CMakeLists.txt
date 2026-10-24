cmake_minimum_required(VERSION 3.15)
project(cx_lib VERSION 1.6.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(cx STATIC
   src/Plane.cpp
   src/Rect.cpp
   src/Sprite.cpp
   src/Text.cpp
   src/Button.cpp
   src/Bar.cpp
   src/TextInput.cpp
   src/Slider.cpp
   src/UIElement.cpp
   src/ParticleManager.cpp
   src/AssetManager.cpp
   src/EventHandler.cpp
   src/AudioManager.cpp
   src/NavigationManager.cpp
   src/Camera.cpp
)

target_compile_definitions(cx PRIVATE CX_SHADER_PATH="${CMAKE_INSTALL_PREFIX}/share/cx/shaders/")
target_include_directories(cx PUBLIC
   $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
   $<INSTALL_INTERFACE:include>)

install(TARGETS cx
   EXPORT cxTargets
   ARCHIVE DESTINATION lib
   LIBRARY DESTINATION lib
   RUNTIME DESTINATION bin)

install(EXPORT cxTargets
   FILE cxTargets.cmake
   DESTINATION lib/cmake/cx)

install(DIRECTORY ${PROJECT_SOURCE_DIR}/include/ DESTINATION include)
install(DIRECTORY ${PROJECT_SOURCE_DIR}/shaders/ DESTINATION share/cx/shaders)

include(CMakePackageConfigHelpers)
configure_package_config_file(
   ${CMAKE_CURRENT_SOURCE_DIR}/cxConfig.cmake.in
   ${CMAKE_CURRENT_BINARY_DIR}/cxConfig.cmake
   INSTALL_DESTINATION lib/cmake/cx)

write_basic_package_version_file(
   ${CMAKE_CURRENT_BINARY_DIR}/cxConfigVersion.cmake
   VERSION ${PROJECT_VERSION}
   COMPATIBILITY SameMajorVersion)

install(FILES
   ${CMAKE_CURRENT_BINARY_DIR}/cxConfig.cmake
   ${CMAKE_CURRENT_BINARY_DIR}/cxConfigVersion.cmake
   DESTINATION lib/cmake/cx)
