SET(this_target "capi-message-port")

INCLUDE_DIRECTORIES (
	${CMAKE_SOURCE_DIR}/include
	)

SET (${this_target}_SOURCE_FILES
	message_port_internal.cpp
	message_port.cpp
	)

SET(requires "message-port dlog")

INCLUDE(FindPkgConfig)
pkg_check_modules(${this_target} REQUIRED ${requires})

FOREACH(flag ${${this_target}_CFLAGS})
    SET(EXTRA_CFLAGS "${EXTRA_CFLAGS} ${flag}")
ENDFOREACH(flag)

SET(EXTRA_CFLAGS  "${EXTRA_CFLAGS} -fPIC -Wall -Werror -fvisibility=hidden -fvisibility-inlines-hidden")

## SET C COMPILER FLAGS
SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${EXTRA_CFLAGS}")

## SET CPP COMPILER FLAGS
SET(CMAKE_CXX_FLAGS "${OSP_DEBUG_FLAGS} ${CMAKE_CXX_FLAGS} ${EXTRA_CFLAGS} ${OSP_COMPILER_FLAGS}")

## SET LINKER FLAGS
SET(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -Wl,--no-undefined -Wl,--as-needed")

## Create Library
ADD_LIBRARY (${this_target} SHARED ${${this_target}_SOURCE_FILES})
TARGET_LINK_LIBRARIES(${this_target} ${${this_target}_LDFLAGS})

SET_TARGET_PROPERTIES(${this_target}
	PROPERTIES
	VERSION ${FULLVER}
	SOVERSION ${MAJORVER}
	CLEAN_DIRECT_OUTPUT 1
	)

# pkgconfig file
SET(PC_NAME ${this_target})
SET(PACKAGE_DESCRIPTION "Message Port managed library")
SET(VERSION ${FULLVER})
SET(PC_REQUIRED ${requires})
SET(PC_LDFLAGS "-l${this_target}")
CONFIGURE_FILE(${CMAKE_SOURCE_DIR}/${this_target}.pc.in ${CMAKE_SOURCE_DIR}/${this_target}.pc @ONLY)
INSTALL(FILES ${CMAKE_SOURCE_DIR}/${this_target}.pc DESTINATION ${LIB_INSTALL_DIR}/pkgconfig)

# install
INSTALL(DIRECTORY ${CMAKE_SOURCE_DIR}/include/ DESTINATION include/appfw FILES_MATCHING PATTERN "*.h")
INSTALL(DIRECTORY ${LIBRARY_OUTPUT_PATH}/ DESTINATION ${LIB_INSTALL_DIR}
		FILES_MATCHING PATTERN "*.so*"
		PERMISSIONS OWNER_EXECUTE OWNER_WRITE OWNER_READ
                    GROUP_EXECUTE GROUP_READ
                    WORLD_EXECUTE WORLD_READ)
