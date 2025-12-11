add_subdirectory(os_api)

# Platform-specific OS controls
if(WIN32)
	add_subdirectory(windows)
elseif(UNIX)
	add_subdirectory(unix)
else()
	message(FATAL_ERROR "Unsupported platform")
endif()
