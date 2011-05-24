
# Offer the user the choice of overriding the installation directories
set(INSTALL_LIB_DIR lib CACHE PATH "Installation directory for libraries")
set(INSTALL_BIN_DIR bin CACHE PATH "Installation directory for executables")
set(INSTALL_INCLUDE_DIR include CACHE PATH
  "Installation directory for header files")
set(INSTALL_DATA_DIR share CACHE PATH
  "Installation directory for data files")
 
# Make relative paths absolute (needed later on)
foreach(p LIB BIN INCLUDE DATA)
  set(var INSTALL_${p}_DIR)
  if(NOT IS_ABSOLUTE "${${var}}")
    set(${var} "${CMAKE_INSTALL_PREFIX}/${${var}}")
  endif()
endforeach()


export(TARGETS ${LIBDGTAL_NAME} ${LIBDGTALVISU3D_NAME} FILE "${PROJECT_BINARY_DIR}/DGtalLibraryDepends.cmake")
 
# Export the package for use from the build-tree
# (this registers the build-tree with a global CMake-registry)
export(PACKAGE DGtal)

# Create a DGtalConfig.cmake file for the use from the build tree
set(DGTAL_INCLUDE_DIRS "${PROJECT_SOURCE_DIR}" "${PROJECT_BINARY_DIR}")
set(DGTAL_LIB_DIR "${PROJECT_BINARY_DIR}/DGtal")
set(DGTAL_CMAKE_DIR "${PROJECT_BINARY_DIR}")

configure_file(${CMAKE_MODULE_PATH}/DGtalConfig.cmake.in
  "${PROJECT_BINARY_DIR}/DGtalConfig.cmake" @ONLY)

configure_file(${CMAKE_MODULE_PATH}/DGtalConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/DGtalConfigVersion.cmake" @ONLY)
 
# Install the export set for use with the install-tree
install(EXPORT DGtalLibraryDepends DESTINATION
  "${INSTALL_DATA_DIR}/DGtal/CMake"
  COMPONENT dev)
 
# Create a DGtalConfig.cmake file for the use from the install tree
# and install it
set(DGTAL_INCLUDE_DIRS "${INSTALL_INCLUDE_DIR}")
set(DGTAL_LIB_DIR "${INSTALL_LIB_DIR}")
set(DGTAL_CMAKE_DIR "${INSTALL_DATA_DIR}/DGtal/CMake")
configure_file(${CMAKE_MODULE_PATH}/DGtalConfig.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/DGtalConfig.cmake" @ONLY)

configure_file(${CMAKE_MODULE_PATH}/DGtalConfigVersion.cmake.in
  "${PROJECT_BINARY_DIR}/InstallFiles/DGtalConfigVersion.cmake" @ONLY)
install(FILES
  "${PROJECT_BINARY_DIR}/InstallFiles/DGtalConfig.cmake"
  "${PROJECT_BINARY_DIR}/InstallFiles/DGtalConfigVersion.cmake"
  DESTINATION "${DGTAL_CMAKE_DIR}" COMPONENT dev)
 
