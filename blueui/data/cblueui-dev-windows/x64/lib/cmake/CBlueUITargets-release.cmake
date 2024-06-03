#----------------------------------------------------------------
# Generated CMake target import file for configuration "Release".
#----------------------------------------------------------------

# Commands may need to know the format version.
set(CMAKE_IMPORT_FILE_VERSION 1)

# Import target "CBlueUI" for configuration "Release"
set_property(TARGET CBlueUI APPEND PROPERTY IMPORTED_CONFIGURATIONS RELEASE)
set_target_properties(CBlueUI PROPERTIES
  IMPORTED_IMPLIB_RELEASE "${_IMPORT_PREFIX}/lib/CBlueUI.lib"
  IMPORTED_LOCATION_RELEASE "${_IMPORT_PREFIX}/bin/CBlueUI.dll"
  )

list(APPEND _cmake_import_check_targets CBlueUI )
list(APPEND _cmake_import_check_files_for_CBlueUI "${_IMPORT_PREFIX}/lib/CBlueUI.lib" "${_IMPORT_PREFIX}/bin/CBlueUI.dll" )

# Commands beyond this point should not need to know the version.
set(CMAKE_IMPORT_FILE_VERSION)
