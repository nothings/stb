# Tell CMake we are cross-compiling to iOS
set(CMAKE_SYSTEM_NAME Darwin)
set(CMAKE_SYSTEM_VERSION 1)
set(UNIX True)
set(APPLE True)
set(IOS True)

# Set compilers to the Apple Clang
set(CMAKE_C_COMPILER "/usr/bin/clang")
set(CMAKE_CXX_COMPILER "/usr/bin/clang++")

# Force compilers to skip detecting compiler ABI info and compile features
set(CMAKE_C_COMPILER_FORCED True)
set(CMAKE_CXX_COMPILER_FORCED True)
set(CMAKE_ASM_COMPILER_FORCED True)

# All iOS/Darwin specific settings - some may be redundant
set(CMAKE_SHARED_LIBRARY_PREFIX "lib")
set(CMAKE_SHARED_LIBRARY_SUFFIX ".dylib")
set(CMAKE_SHARED_MODULE_PREFIX "lib")
set(CMAKE_SHARED_MODULE_SUFFIX ".so")
set(CMAKE_MODULE_EXISTS 1)
set(CMAKE_DL_LIBS "")

set(CMAKE_C_OSX_COMPATIBILITY_VERSION_FLAG "-compatibility_version ")
set(CMAKE_C_OSX_CURRENT_VERSION_FLAG "-current_version ")
set(CMAKE_CXX_OSX_COMPATIBILITY_VERSION_FLAG "${CMAKE_C_OSX_COMPATIBILITY_VERSION_FLAG}")
set(CMAKE_CXX_OSX_CURRENT_VERSION_FLAG "${CMAKE_C_OSX_CURRENT_VERSION_FLAG}")

# Hidden visibility is required for CXX on iOS
set(CMAKE_C_FLAGS_INIT "")
set(CMAKE_CXX_FLAGS_INIT "-fvisibility=hidden -fvisibility-inlines-hidden")

set(CMAKE_C_LINK_FLAGS "-Wl,-search_paths_first ${CMAKE_C_LINK_FLAGS}")
set(CMAKE_CXX_LINK_FLAGS "-Wl,-search_paths_first ${CMAKE_CXX_LINK_FLAGS}")

set(CMAKE_PLATFORM_HAS_INSTALLNAME 1)
set(CMAKE_SHARED_LIBRARY_CREATE_C_FLAGS "-dynamiclib")
set(CMAKE_SHARED_MODULE_CREATE_C_FLAGS "-bundle")
set(CMAKE_SHARED_MODULE_LOADER_C_FLAG "-Wl,-bundle_loader,")
set(CMAKE_SHARED_MODULE_LOADER_CXX_FLAG "-Wl,-bundle_loader,")
set(CMAKE_FIND_LIBRARY_SUFFIXES ".dylib" ".so" ".a")

# hack: if a new cmake (which uses CMAKE_INSTALL_NAME_TOOL) runs on an old build tree
# (where install_name_tool was hardcoded) and where CMAKE_INSTALL_NAME_TOOL isn't in the cache
# and still cmake didn't fail in CMakeFindBinUtils.cmake (because it isn't rerun)
# hardcode CMAKE_INSTALL_NAME_TOOL here to install_name_tool, so it behaves as it did before, Alex
if( NOT DEFINED CMAKE_INSTALL_NAME_TOOL )
	find_program(CMAKE_INSTALL_NAME_TOOL install_name_tool)
endif()

# Setup iOS platform
if( NOT DEFINED CMAKE_IOS_PLATFORM )
	set(CMAKE_IOS_PLATFORM "OS")
endif()
set(CMAKE_IOS_PLATFORM ${CMAKE_IOS_PLATFORM} CACHE STRING "Type of iOS platform.")
set_property(CACHE CMAKE_IOS_PLATFORM PROPERTY STRINGS OS Simulator)

# Check the platform selection and setup for developer root
set(CMAKE_IOS_PLATFORM_LOCATION "iPhone${CMAKE_IOS_PLATFORM}.platform")

# Setup iOS developer location
if( NOT DEFINED CMAKE_IOS_DEVELOPER_ROOT )
	set(CMAKE_IOS_DEVELOPER_ROOT "/Applications/Xcode.app/Contents/Developer/Platforms/${CMAKE_IOS_PLATFORM_LOCATION}/Developer")
endif(NOT DEFINED CMAKE_IOS_DEVELOPER_ROOT)

# Find and use the most recent iOS sdk
if( NOT DEFINED CMAKE_IOS_SDK_ROOT )
	file(GLOB _CMAKE_IOS_SDKS "${CMAKE_IOS_DEVELOPER_ROOT}/SDKs/*")
	if( _CMAKE_IOS_SDKS )
		list(SORT _CMAKE_IOS_SDKS)
		list(REVERSE _CMAKE_IOS_SDKS)
		list(GET _CMAKE_IOS_SDKS 0 CMAKE_IOS_SDK_ROOT)
	else()
		message(FATAL_ERROR "No iOS SDK's found in default seach path ${CMAKE_IOS_DEVELOPER_ROOT}. Manually set CMAKE_IOS_SDK_ROOT or install the iOS SDK.")
	endif()
endif()

# Set the sysroot default to the most recent SDK
set(CMAKE_OSX_SYSROOT ${CMAKE_IOS_SDK_ROOT})

# Set the target architectures for iOS, separated by a space
set(CMAKE_OSX_ARCHITECTURES "arm64" CACHE string "iOS architecture deployment target.")

# Set iOS deployment target version
set(CMAKE_IOS_DEPLOYMENT_TARGET "9.0" CACHE string "iOS deployment target version (using latest iOS SDK regardless).")

# Set the find root to the iOS developer roots and to user defined paths
set(CMAKE_FIND_ROOT_PATH ${CMAKE_IOS_DEVELOPER_ROOT} ${CMAKE_IOS_SDK_ROOT} ${CMAKE_PREFIX_PATH} CACHE string  "iOS find search path root.")

# Default to searching for frameworks first
set(CMAKE_FIND_FRAMEWORK FIRST)

# Set up the default search directories for frameworks
set(CMAKE_SYSTEM_FRAMEWORK_PATH
	${CMAKE_IOS_SDK_ROOT}/System/Library/Frameworks
	${CMAKE_IOS_SDK_ROOT}/System/Library/PrivateFrameworks
	${CMAKE_IOS_SDK_ROOT}/Developer/Library/Frameworks
)

# Only search the iOS SDK, not the remainder of the host file system
set(CMAKE_FIND_ROOT_PATH_MODE_PROGRAM ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_LIBRARY ONLY)
set(CMAKE_FIND_ROOT_PATH_MODE_INCLUDE ONLY)
