cmake_minimum_required(VERSION 3.6)

# Lock the process
file(LOCK "${LOCKDIR}/${OUTFILE}.lock")

# Set output full file path
set(MANIFEST_FILE "${OUTDIR}/${OUTFILE}")

# Decode files or directories
if( NOT "${FILENAMES}" STREQUAL "" )
	string(REPLACE "\*" ";" FILENAMES ${FILENAMES})
elseif( NOT "${DIRNAMES}" STREQUAL "" )
	string(REPLACE "\*" ";" DIRNAMES ${DIRNAMES})
	string(REPLACE "\\" "/" DIRNAMES ${DIRNAMES})
	string(REPLACE "//" "/" DIRNAMES ${DIRNAMES})
	foreach(DIR ${DIRNAMES})
		file(GLOB FILES_IN_DIR "${DIR}/*")
		list(APPEND FILENAMES ${FILES_IN_DIR})
	endforeach()
else()
	set(FILENAMES)
endif()

# Loop through all files
foreach(FILENAME ${FILENAMES})
	# Filter out some file by extensions
	if( NOT "${FILENAME}" MATCHES ".*(\.exe$|\.dll$)" )
		continue()
	endif()

	# Workaround for using correct plugin path
	if( NOT "${PLUGIN_DLL_FILEPATH}" STREQUAL "" )
		get_filename_component(A ${FILENAME} NAME)
		get_filename_component(B ${PLUGIN_DLL_FILEPATH} NAME)
		if( "${A}" STREQUAL "${B}" )
			set(FILENAME "${PLUGIN_DLL_FILEPATH}")
		endif()
	endif()

	# Get file name only
	if( "${FILENAME}" MATCHES "${OUTDIR}" )
		string(REPLACE "${OUTDIR}/" "" FILENAME ${FILENAME})
	else()
		get_filename_component(FILENAME ${FILENAME} NAME)
	endif()

	# Check if FILENAME is already present in MANIFEST_FILE
	set(FOUND 0)
	if( EXISTS "${MANIFEST_FILE}" )
		file(STRINGS "${MANIFEST_FILE}" LINES)
		foreach(LINE ${LINES})
			if( "${LINE}" MATCHES "${FILENAME}" )
				set(FOUND 1)
				break()
			endif()
		endforeach()
	endif()

	# Append FILENAME to MANIFEST_FILE
	if( NOT FOUND )
		file(APPEND "${MANIFEST_FILE}" "${FILENAME}\n")
	endif()
endforeach()

# Unlock the process
file(LOCK "${LOCKDIR}/${OUTFILE}.lock" RELEASE)
