cmake_minimum_required(VERSION 3.6)

set(CMAKE_CONFIGURATION_TYPES "Debug;Dev;Release"
    CACHE STRING
    "List of supported configurations."
    FORCE)

project(stb)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CMakeSettings)

set(CMAKE_C_FLAGS)
set(CMAKE_CXX_FLAGS)
set(CMAKE_C_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_CXX_FLAGS_DEBUG "-D_DEBUG")
set(CMAKE_C_FLAGS_RELEASE "-DNDEBUG")
set(CMAKE_CXX_FLAGS_RELEASE "-DNDEBUG")

# Setup platforms
if( PLATFORM_WINDOWS )
	add_compile_options(-DWINDOWSPC)
endif()

# Define standard configurations
if( CMAKE_CONFIGURATION_TYPES AND NOT CMAKE_CONFIGURATION_TYPES MATCHES "Debug;Dev;Release" )
	list(APPEND Configs Debug Dev Release)
	set(CMAKE_CONFIGURATION_TYPES ${Configs} CACHE STRING "List of supported configurations." FORCE)
	set(CMAKE_INSTALL_PREFIX $ENV{SR_BIN_DIR} CACHE STRING "Default installation directory." FORCE)
	message(FATAL_ERROR "Default configuration was reset, please re-run CMake.")
endif()

# Initialize the development configuration using release configuration
set(CMAKE_C_FLAGS_DEV "${CMAKE_C_FLAGS_RELEASE}")
set(CMAKE_CXX_FLAGS_DEV "${CMAKE_CXX_FLAGS_RELEASE}")
set(CMAKE_STATIC_LINKER_FLAGS_DEV "${CMAKE_STATIC_LINKER_FLAGS_RELEASE}")

set(root ${CMAKE_CURRENT_SOURCE_DIR})
set(INCLUDE_FILES ${root}/stb_image.h ${root}/stb_image_write.h)
set(ALL_SOURCE_FILES ${INCLUDE_FILES} ${root}/stb_shared.c)

add_library(${PROJECT_NAME} STATIC ${ALL_SOURCE_FILES})

export(TARGETS ${PROJECT_NAME} APPEND FILE ${CMAKE_BINARY_DIR}/${PROJECT_NAME}-targets.cmake)

install(TARGETS ${PROJECT_NAME} EXPORT ${PROJECT_NAME}-targets DESTINATION lib/$<LOWER_CASE:$<CONFIG>>)
install(FILES ${INCLUDE_FILES} DESTINATION include)
