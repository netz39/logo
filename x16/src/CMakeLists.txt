#
# Copyright 2012 Netz39 e.V.
#
configure_file(
	${CMAKE_CURRENT_SOURCE_DIR}/x16_build.h.in
	${CMAKE_CURRENT_BINARY_DIR}/x16_build.h
)

set(X16_SRC
	x16.c
)

# direct includes
include_directories(
	${CMAKE_CURRENT_BINARY_DIR}
)

add_executable(${PROJECT_NAME} ${X16_SRC})

target_link_libraries(${PROJECT_NAME}
	${LIBGD2_LIBRARY}
)

install(TARGETS ${PROJECT_NAME} DESTINATION bin)
