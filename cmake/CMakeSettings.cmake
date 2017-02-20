cmake_minimum_required(VERSION 3.6)

# This module is shared; use include blocker.
if( _SETTINGS_ )
	return()
endif()
set(_SETTINGS_ 1)

include(CMakePlatforms)
include(CMakeMacros)

# Define product build options
set(PRODUCT_NAME "Stingray")
set(PRODUCT_COMPANY "Autodesk")
set(PRODUCT_COPYRIGHT "Copyright (C) 2016 ${PRODUCT_COMPANY}, Inc. All rights reserved.")
set(PRODUCT_VERSION_MAJOR "1")
set(PRODUCT_VERSION_MINOR "8")
set(PRODUCT_VERSION_REVISION "0")

# Bump this revision if projects require any migration.
# Reset to 0 if you increase MAJOR or MINOR versions.
set(PRODUCT_DEV_VERSION_REVISION "0")

# Build options controlled by TeamCity - do not change here!
set_default(PRODUCT_VERSION_LABEL "$ENV{SR_PRODUCT_VERSION_LABEL}" "Developer Build")
set_default(PRODUCT_VERSION_TCID "$ENV{SR_PRODUCT_VERSION_TCID}" "0")
set_default(PRODUCT_BUILD_TIMESTAMP "$ENV{SR_PRODUCT_BUILD_TIMESTAMP}" "")
set_default(PRODUCT_LICENSING_KEY "$ENV{SR_PRODUCT_LICENSING_KEY}" "A72I1")
set_default(PRODUCT_LICENSING_VERSION "$ENV{SR_PRODUCT_LICENSING_VERSION}" "2017.0.0.F")
set_default(PRODUCT_EDITOR_STEAM_APPID "$ENV{SR_PRODUCT_EDITOR_STEAM_APPID}" "0")

# Generate timestamp if not overriden by TeamCity option
if( "${PRODUCT_BUILD_TIMESTAMP}" STREQUAL "" AND NOT "${PRODUCT_VERSION_LABEL}" STREQUAL "Developer Build" )
	string(TIMESTAMP PRODUCT_BUILD_TIMESTAMP "%Y-%m-%dT%H:%M:%SZ" UTC)
endif()

# Allow environment variables to override some build options
set(ENGINE_BUILD_IDENTIFIER $ENV{SR_BUILD_IDENTIFIER})

if( NOT CMAKE_INSTALL_PREFIX OR CMAKE_INSTALL_PREFIX STREQUAL "" )
	message(FATAL_ERROR "CMAKE_INSTALL_PREFIX not set! Please set CMAKE_INSTALL_PREFIX to appropriate location when running this CMake script.")
endif()
string(REGEX REPLACE "\\\\" "/" BINARIES_DIR ${CMAKE_INSTALL_PREFIX})

set(ENGINE_LIB_DIR $ENV{SR_LIB_DIR})
if( NOT ENGINE_LIB_DIR OR ENGINE_LIB_DIR STREQUAL "" )
	message(FATAL_ERROR "Environment variable SR_LIB_DIR not set! Please set environment variable SR_LIB_DIR to appropriate location before running this CMake script.")
endif()
string(REGEX REPLACE "\\\\" "/" ENGINE_LIB_DIR ${ENGINE_LIB_DIR})

# Set install directories
if( PLATFORM_WINDOWS )
	set(ENGINE_INSTALL_DIR "${BINARIES_DIR}/engine/win${ARCH_BITS}/$<LOWER_CASE:$<CONFIG>>")
elseif( PLATFORM_WINUWP )
	set(ENGINE_INSTALL_DIR "${BINARIES_DIR}/engine/winuwp${ARCH_BITS}/$<LOWER_CASE:$<CONFIG>>")
else()
	set(ENGINE_INSTALL_DIR "${BINARIES_DIR}/engine/${PLATFORM_NAME}/$<LOWER_CASE:$<CONFIG>>")
endif()
set(ENGINE_PLUGINS_INSTALL_DIR "${ENGINE_INSTALL_DIR}/plugins")
set(EDITOR_INSTALL_DIR "${BINARIES_DIR}/editor")
set(TOOLS_INSTALL_DIR "${BINARIES_DIR}/tools")
set(TOOLS_EXTERNAL_INSTALL_DIR "${BINARIES_DIR}/tools_external")

if( PLATFORM_WINDOWS )
	set(ENGINE_PLUGIN_SUFFIX "w${ARCH_BITS}")
else()
	set(ENGINE_PLUGIN_SUFFIX "")
endif()

# Global options
if( PLATFORM_WINDOWS )
	set(BUILD_SHARED_LIBS ON CACHE BOOL "Build plug-ins as shared libraries.")
else()
	set(BUILD_SHARED_LIBS OFF CACHE BOOL "Build plug-ins as static libraries.")
endif()

if( PLATFORM_IOS )
	set_default(ENGINE_IOS_CODE_SIGN_IDENTITY "$ENV{SR_IOS_CODE_SIGN_IDENTITY}" "iPhone Developer")
	set_default(ENGINE_IOS_DEVELOPMENT_TEAM "$ENV{SR_IOS_DEVELOPMENT_TEAM}" "")
endif()

set(BUILD_RUN_TEST OFF CACHE BOOL "Enable special build for run test mode.")

# Engine options
set(ENGINE_USE_DEBUG_INFO ON CACHE BOOL "Enable debug information in all configurations.")
set(ENGINE_USE_SOUND ON CACHE BOOL "Enable Sound (Timpani) support.")
set(ENGINE_USE_APEX OFF CACHE BOOL "Enable APEX clothing support.")
set(ENGINE_USE_AVX OFF CACHE BOOL "Enable AVX instructions set support.")
set(ENGINE_USE_UNWRAPLIB ON CACHE BOOL "Enable UV-unwrapping.")
set(ENGINE_USE_STEAM OFF CACHE BOOL "Enable Steamworks support.")
set(ENGINE_USE_STEAM_DEDICATED_SERVER OFF CACHE BOOL "Enable Steamworks dedicated server support.")
set(ENGINE_USE_EXPERIMENTAL_CRITICALSECTIONS OFF CACHE BOOL "Enable experimental spinlocks on Android.")
set(ENGINE_USE_WEBGL_SIMD OFF CACHE BOOL "Enable SIMD support on WebGL.")
set(ENGINE_USE_D3D12 OFF CACHE BOOL "Enable D3D12 support.")

# Set folder names inside solution files
set(ENGINE_FOLDER_NAME "runtime")
set(ENGINE_PLUGINS_FOLDER_NAME "plugins")
set(ENGINE_USE_SOLUTION_FOLDERS ON)

# Define if platform can compile game data
if( PLATFORM_64BIT AND (PLATFORM_WINDOWS OR PLATFORM_OSX) )
	set(ENGINE_CAN_COMPILE 1)
endif()

# Verify configuration validity
if( NOT ENGINE_CAN_COMPILE )
	set(ENGINE_USE_CAPTURE_FRAME_PLUGIN OFF)
	set(ENGINE_USE_UNWRAPLIB OFF)
	set(ENGINE_USE_TEXTUREREADER_PLUGIN OFF)
	set(ENGINE_USE_FBXSDK_PLUGIN OFF)
	set(ENGINE_USE_PROTEIN_PLUGIN OFF)
	set(ENGINE_USE_XB1_DATA_COMPILER_PLUGIN OFF)
	set(ENGINE_USE_PS4_DATA_COMPILER_PLUGIN OFF)
endif()

if( ENGINE_USE_SOUND AND (PLATFORM_WEBGL OR PLATFORM_WINUWP) )
	message(STATUS "Sound (Timpani) support disabled, unsupported by platform ${PLATFORM_NAME}.")
	set(ENGINE_USE_SOUND OFF)
endif()

if( ENGINE_USE_APEX AND NOT (PLATFORM_WINDOWS OR PLATFORM_XBOXONE OR PLATFORM_PS4) )
	message(STATUS "APEX support disabled, unsupported by platform ${PLATFORM_NAME}.")
	set(ENGINE_USE_APEX OFF)
endif()

if( ENGINE_USE_OCULUS_PLUGIN AND NOT PLATFORM_WINDOWS )
	message(STATUS "Oculus support disabled, unsupported by platform ${PLATFORM_NAME}.")
	set(ENGINE_USE_OCULUS_PLUGIN OFF)
endif()

if( ENGINE_USE_STEAMVR_PLUGIN AND NOT PLATFORM_WINDOWS )
	message(STATUS "SteamVR support disabled, unsupported by platform ${PLATFORM_NAME}.")
	set(ENGINE_USE_STEAMVR_PLUGIN OFF)
endif()

if( ENGINE_USE_GEARVR_PLUGIN AND NOT PLATFORM_ANDROID )
	message(STATUS "GearVR support disabled, unsupported by platform ${PLATFORM_NAME}.")
	set(ENGINE_USE_GEARVR_PLUGIN OFF)
endif()

if( ENGINE_USE_GOOGLEVR_PLUGIN AND NOT (PLATFORM_ANDROID OR PLATFORM_IOS) )
	message(STATUS "GoogleVR support disabled, unsupported by platform ${PLATFORM_NAME}.")
	set(ENGINE_USE_GOOGLEVR_PLUGIN OFF)
endif()

if( ENGINE_USE_GEARVR_PLUGIN AND ENGINE_USE_GOOGLEVR_PLUGIN )
	message(FATAL_ERROR "Cannot enable both GearVR and GoogleVR plug-ins at once.")
endif()

if( ENGINE_USE_D3D12 AND NOT PLATFORM_WINDOWS )
	message(STATUS "D3D12 support disabled, unsupported by platform ${PLATFORM_NAME}.")
	set(ENGINE_USE_D3D12 OFF)
endif()

if( ENGINE_USE_D3D12 AND MSVC_VERSION LESS 1900 )
	message(FATAL_ERROR "D3D12 requires msvc14 or above.")
	set(ENGINE_USE_D3D12 OFF)
endif()

if( PLATFORM_WEBGL )
	set(ENGINE_USE_HUMANIK_PLUGIN OFF)
	message(STATUS "HumanIK plug-in support disabled, not supported yet by platform ${PLATFORM_NAME}.")
	set(ENGINE_USE_WWISE_PLUGIN OFF)
	message(STATUS "WWise plug-in support disabled, not supported yet by platform ${PLATFORM_NAME}.")
endif()

if( PLATFORM_WINUWP )
	set(ENGINE_USE_SCALEFORMSTUDIO_PLUGIN OFF)
	message(STATUS "Scaleform plug-in support disabled, not supported yet by platform ${PLATFORM_NAME}.")
endif()

if( PLATFORM_LINUX )
	set(ENGINE_USE_SCALEFORMSTUDIO_PLUGIN OFF)
	message(STATUS "Scaleform plug-in support disabled, not supported yet by platform ${PLATFORM_NAME}.")
	set(ENGINE_USE_HUMANIK_PLUGIN OFF)
	message(STATUS "HumanIK plug-in support disabled, not supported yet by platform ${PLATFORM_NAME}.")
	set(ENGINE_USE_WWISE_PLUGIN OFF)
	message(STATUS "WWise plug-in support disabled, not supported yet by platform ${PLATFORM_NAME}.")
endif()

# Editor options
set(EDITOR_SHIPPING OFF CACHE BOOL "Enable editor shipping mode.")
set(EDITOR_USE_STEAM OFF CACHE BOOL "Enable Steamworks support for editor.")
set(EDITOR_USE_CLIC OFF CACHE BOOL "Enable CLIC support.")
set(EDITOR_USE_CER OFF CACHE BOOL "Enable CER support.")
set(EDITOR_USE_UPI OFF CACHE BOOL "Enable UPI support.")
set(EDITOR_USE_MC3 OFF CACHE BOOL "Enable MC3 support.")
set(EDITOR_USE_TEMPLATES OFF CACHE BOOL "Enable editor template install.")
set(EDITOR_USE_GEARVR OFF CACHE BOOL "Enable editor GearVR support.")

# Verify configuration validity
if( EDITOR_USE_STEAM )
	if( EDITOR_USE_CLIC )
		message(STATUS "CLIC support disabled, implied by editor's steam mode.")
		set(EDITOR_USE_CLIC OFF)
	endif()
endif()

if( EDITOR_SHIPPING )
	if( NOT EDITOR_USE_STEAM )
		if( NOT EDITOR_USE_CLIC )
			message(STATUS "CLIC support enabled, implied by editor's shipping mode.")
			set(EDITOR_USE_CLIC ON)
		endif()
	endif()
	if( NOT EDITOR_USE_CER )
		message(STATUS "CER support enabled, implied by editor's shipping mode.")
		set(EDITOR_USE_CER ON)
	endif()
	if( NOT EDITOR_USE_UPI )
		message(STATUS "UPI support enabled, implied by editor's shipping mode.")
		set(EDITOR_USE_UPI ON)
	endif()
	if( NOT EDITOR_USE_MC3 )
		message(STATUS "MC3 support enabled, implied by editor's shipping mode.")
		set(EDITOR_USE_MC3 ON)
	endif()
endif()

# Exporter options
set(EXPORTERS_USE_BSI OFF CACHE BOOL "Enable bsi plugins.")
set(EXPORTERS_USE_DCC_LINK ON CACHE BOOL "Enable dcc link plugins.")
set(EXPORTERS_USE_MOTION_BUILDER ON CACHE BOOL "Enable Motion Builder plugins.")
set(EXPORTERS_USE_DCC_LINK_WORKFLOW OFF CACHE BOOL "Enable dcc link workflow application.")

if( EDITOR_USE_STEAM )
	set(PRODUCT_VERSION_REGKEY "Steam-${PRODUCT_EDITOR_STEAM_APPID}")
else()
	set(PRODUCT_VERSION_REGKEY "${PRODUCT_VERSION_MAJOR}.${PRODUCT_VERSION_MINOR}.${PRODUCT_VERSION_TCID}.${PRODUCT_VERSION_REVISION}")
endif()
