
# Lists of directories with source files:
#  See "DeclareMRPTLib.cmake" for explanations
# -------------------------------------------------


# Embedded freeglut? Built-in into mrpt-opengl, and enable DLL-exporting it to other client libs.
IF(CMAKE_MRPT_HAS_OPENGL_GLUT AND NOT CMAKE_MRPT_HAS_GLUT_SYSTEM)
	LIST(APPEND opengl_EXTRA_SRCS		"${MRPT_LIBS_ROOT}/opengl/src/freeglut-2.4.0/*.c" "${MRPT_LIBS_ROOT}/opengl/src/freeglut-2.4.0/*.h")
	LIST(APPEND opengl_EXTRA_SRCS_NAME 	"freeglut" "freeglut")
	#ADD_DEFINITIONS(/DFREEGLUT_STATIC)
	ADD_DEFINITIONS(/DFREEGLUT_EXPORTS)
	INCLUDE_DIRECTORIES("${MRPT_LIBS_ROOT}/opengl/include/otherlibs/freeglut/")
ENDIF(CMAKE_MRPT_HAS_OPENGL_GLUT AND NOT CMAKE_MRPT_HAS_GLUT_SYSTEM)

# Embedded version of lib3ds?
IF(NOT CMAKE_MRPT_HAS_LIB3DS_SYSTEM)
	LIST(APPEND opengl_EXTRA_SRCS		"${MRPT_LIBS_ROOT}/opengl/src/lib3ds/*.c" "${MRPT_LIBS_ROOT}/opengl/src/lib3ds/*.h")
	LIST(APPEND opengl_EXTRA_SRCS_NAME 	"lib3ds" "lib3ds")
	INCLUDE_DIRECTORIES("${MRPT_SOURCE_DIR}/libs/opengl/src/")
ENDIF(NOT CMAKE_MRPT_HAS_LIB3DS_SYSTEM)

# Embedded version of Glew:
IF(WIN32)
	LIST(APPEND opengl_EXTRA_SRCS		"${MRPT_SOURCE_DIR}/libs/opengl/src/glew/src/*.c" "${MRPT_SOURCE_DIR}/libs/opengl/src/glew/include/*.h")
	LIST(APPEND opengl_EXTRA_SRCS_NAME 	"glew" "glew")
	INCLUDE_DIRECTORIES("${MRPT_SOURCE_DIR}/libs/opengl/src/glew/include")
ENDIF(WIN32)

# Glext headers only (for Windows)
INCLUDE_DIRECTORIES("${MRPT_SOURCE_DIR}/libs/opengl/src/glext")

# Assimp:
IF (CMAKE_MRPT_HAS_ASSIMP)
	# ASSIMP_ROOT_DIR - the root directory where the installation can be found
	# ASSIMP_CXX_FLAGS - extra flags for compilation
	# ASSIMP_LINK_FLAGS - extra flags for linking
	# ASSIMP_INCLUDE_DIRS - include directories
	# ASSIMP_LIBRARY_DIRS - link directories
	# ASSIMP_LIBRARIES - libraries to link plugins with
	IF (NOT ${ASSIMP_CXX_FLAGS} STREQUAL "")
		ADD_DEFINITIONS("${ASSIMP_CXX_FLAGS}")
	ENDIF(NOT ${ASSIMP_CXX_FLAGS} STREQUAL "")
	IF (NOT ${ASSIMP_INCLUDE_DIRS} STREQUAL "")
		INCLUDE_DIRECTORIES("${ASSIMP_INCLUDE_DIRS}")
	ENDIF(NOT ${ASSIMP_INCLUDE_DIRS} STREQUAL "")
	IF(NOT ${ASSIMP_VERSION} STREQUAL "")
		string(SUBSTRING "${ASSIMP_VERSION}" 0 1 MRPT_ASSIMP_VERSION_MAJOR)
		ADD_DEFINITIONS(-DMRPT_ASSIMP_VERSION_MAJOR=${MRPT_ASSIMP_VERSION_MAJOR})
	ENDIF(NOT ${ASSIMP_VERSION} STREQUAL "")
ENDIF (CMAKE_MRPT_HAS_ASSIMP)

#---------------------------------------------
# Macro declared in "DeclareMRPTLib.cmake":
#---------------------------------------------
define_mrpt_lib(
	# Lib name
	opengl 		
	# Dependencies: 
	mrpt-base		
	)

IF(BUILD_mrpt-opengl)
	# Ignore precompiled headers in some sources:
	IF(MRPT_ENABLE_PRECOMPILED_HDRS)
		IF (MSVC)
			set_source_files_properties(
				${lib3ds_FILES}
				${freeglut_FILES}
				${glew_FILES}
				PROPERTIES COMPILE_FLAGS "/Y-"
				)
			# Params for glew:	
			set_source_files_properties(${glew_FILES} PROPERTIES COMPILE_FLAGS "/Y- /DGLEW_STATIC")
	ENDIF (MSVC)
	ENDIF(MRPT_ENABLE_PRECOMPILED_HDRS)
	
	# Link against assimp:
	IF (CMAKE_MRPT_HAS_ASSIMP)
		IF (NOT CMAKE_MRPT_HAS_ASSIMP_SYSTEM)
			ADD_DEPENDENCIES(mrpt-opengl assimp)
		ENDIF (NOT CMAKE_MRPT_HAS_ASSIMP_SYSTEM)
		TARGET_LINK_LIBRARIES(mrpt-opengl ${ASSIMP_LIBRARIES})
	ENDIF (CMAKE_MRPT_HAS_ASSIMP)

ENDIF(BUILD_mrpt-opengl) 

