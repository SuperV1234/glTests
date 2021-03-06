FIND_PATH(SSVUTILS_INCLUDE_DIR
  NAMES SSVUtils/SSVUtils.hpp
  PATH_SUFFIXES include/
  PATHS "${PROJECT_SOURCE_DIR}/../SSVUtils/"
  "${PROJECT_SOURCE_DIR}/extlibs/SSVUtils/"
  ${SSVUTILS_ROOT}
  $ENV{SSVUTILS_ROOT}
  /usr/local/
  /usr/
  /sw/       
  /opt/local/
  /opt/csw/  
  /opt/
)

message("\nFound SSVUtils include at: ${SSVUTILS_INCLUDE_DIR}.\n")

IF(SSVUTILS_INCLUDE_DIR)
  SET(SSVUTILS_FOUND TRUE)
ELSE(SSVUTILS_INCLUDE_DIR)
  SET(SSVUTILS_FOUND FALSE)
ENDIF(SSVUTILS_INCLUDE_DIR)

IF(SSVUTILS_FOUND)
  MESSAGE(STATUS "Found SSVUtils in ${SSVUTILS_INCLUDE_DIR}")
ELSE(SSVUTILS_FOUND)
  IF(SSVUTILS_FIND_REQUIRED)
    MESSAGE(FATAL_ERROR "Could not find SSVUtils library")
  ENDIF(SSVUTILS_FIND_REQUIRED)
ENDIF(SSVUTILS_FOUND)

MARK_AS_ADVANCED(
  SSVUTILS_INCLUDE_DIR
)
