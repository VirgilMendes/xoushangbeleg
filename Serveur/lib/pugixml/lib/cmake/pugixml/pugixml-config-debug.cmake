#----------------------------------------------------------------
# Generated CMake target import file for configuration "Debug".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "pugixml" for configuration "Debug"
set_property(TARGET pugixml APPEND PROPERTY IMPORTED_CONFIGURATIONS DEBUG)
set_target_properties(pugixml PROPERTIES
  IMPORTED_IMPLIB_DEBUG "${_IMPORT_PREFIX}/lib/pugixml.lib"
  IMPORTED_LOCATION_DEBUG "${_IMPORT_PREFIX}/bin/pugixml.dll"
  )

list(APPEND _IMPORT_CHECK_TARGETS pugixml )
list(APPEND _IMPORT_CHECK_FILES_FOR_pugixml "${_IMPORT_PREFIX}/lib/pugixml.lib" "${_IMPORT_PREFIX}/bin/pugixml.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
