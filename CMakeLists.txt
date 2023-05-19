
# project
cmake_minimum_required (VERSION 3.3)
project(TinyGL LANGUAGES C)

# options
option(TINYGL_BUILD_EXAMPLES "Build TinyGL Examples" ON)
option(TINYGL_FIXED_POINT "Use Fixed-Point Math" OFF)
option(TINYGL_BITCH_MODE "Enable pedantic and all warnings" OFF)

add_subdirectory(extras)

# compile options
if(TINYGL_BITCH_MODE)
	add_compile_options(-pedantic -Wall -Wextra)
endif()

if(TINYGL_FIXED_POINT)
	message(STATUS "TinyGL Fixed Point Enabled")
	add_compile_definitions(-DTGL_FIXED=1)
endif()

if(${CMAKE_BUILD_TYPE} STREQUAL "Release")
	add_compile_options(-O3)
endif()

if(NOT MSVC)
	link_libraries(m)
endif()

# sources
# see: https://stackoverflow.com/questions/1027247/is-it-better-to-specify-source-files-with-glob-or-each-file-individually-in-cmak/1060061#1060061
set(TINYGL_SOURCES
	source/api.c
	source/arrays.c
	source/clear.c
	source/clip.c
	source/error.c
	source/get.c
	source/glu.c
	source/image_util.c
	source/init.c
	source/light.c
	source/list.c
	source/matrix.c
	source/memory.c
	source/misc.c
	source/msghandling.c
	source/ostinygl.c
	source/select.c
	source/specbuf.c
	source/texture.c
	source/vertex.c
	source/zbuffer.c
	source/zdither.c
	source/zline.c
	source/zmath.c
	source/ztriangle.c
)

# library
add_library(TinyGL STATIC ${TINYGL_SOURCES})
target_include_directories(TinyGL PUBLIC ${PROJECT_SOURCE_DIR}/include source/)
target_link_libraries(TinyGL fixmath)

# examples
if(TINYGL_BUILD_EXAMPLES AND NOT DJGPP)

	find_package(SDL2 REQUIRED)
	link_libraries(TinyGL SDL2::SDL2)
	if(WIN32)
		include_directories(${SDL2_INCLUDE_DIR}/../) # HACK: this is if using the official SDL2 release and not the Linux distro ones.
	endif()
	add_executable(gears
		${PROJECT_SOURCE_DIR}/examples/gears.c
		${PROJECT_SOURCE_DIR}/examples/ui.c
	)

	add_executable(mech
		${PROJECT_SOURCE_DIR}/examples/mech.c
		${PROJECT_SOURCE_DIR}/examples/ui.c
	)

	add_executable(spin
		${PROJECT_SOURCE_DIR}/examples/spin.c
		${PROJECT_SOURCE_DIR}/examples/ui.c
	)

	add_executable(texobj
		${PROJECT_SOURCE_DIR}/examples/texobj.c
		${PROJECT_SOURCE_DIR}/examples/ui.c
	)

endif()
