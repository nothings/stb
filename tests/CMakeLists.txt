# -*- coding: utf-8-unix -*-

cmake_minimum_required(VERSION 3.4.1)

project(stb_test C CXX)

include_directories(
  .
  ..
  )

if(MSVC)
  add_definitions(-D_CRT_SECURE_NO_WARNINGS=1)
endif()

############
# image_test
add_executable(
  image_test
  image_test.c
  ../stb_image.h
  ../stb_image_write.h
  )

if(MSVC)
  target_compile_options(
	image_test
	#  PRIVATE "/W4"
	PRIVATE "/W3"
	)
else()
  target_compile_options(
	image_test
	PRIVATE "-std=gnu90"
	)
endif()


set_target_properties(
  image_test
  PROPERTIES
  VS_DEBUGGER_WORKING_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}
  )

if(UNIX)
  target_link_libraries(
	image_test
	-lm
    )
endif()

############
# herringbone
add_executable(
  herringbone
  herringbone_generator.c
  ../stb_herringbone_wang_tile.h
  ../stb_image_write.h
  )

############
# herringbone_map
add_executable(
  herringbone_map
  herringbone_map.c
  ../stb_herringbone_wang_tile.h
  ../stb_image.h
  ../stb_image_write.h
  )

############
# resize
add_executable(
  resize
  resample_test.cpp
  ../stb_image_resize.h
  ../stb_image.h
  ../stb_image_write.h
  )

############
# stb
add_executable(
  stb
  grid_reachability.c
  stb.c
  stretchy_buffer_test.c
  test_c_compilation.c
  test_truetype.c
  test_vorbis.c
  textedit_sample.c
  ../stb.h
  ../stb_c_lexer.h
  ../stb_connected_components.h
  ../stb_divide.h
  ../stb_dxt.h
  ../stb_easy_font.h
  ../stb_herringbone_wang_tile.h
  ../stb_image.h
  ../stb_image_resize.h
  ../stb_image_write.h
  ../stb_leakcheck.h
#  ../stb_malloc.h
  ../stb_perlin.h
#  ../stb_pg.h
  ../stb_rect_pack.h
  ../stb_sprintf.h
  ../stb_textedit.h
  ../stb_tilemap_editor.h
  ../stb_truetype.h
  ../stb_vorbis.c
  ../stb_voxel_render.h
  ../stretchy_buffer.h
  )

if(MSVC)
  target_compile_options(
	stb
	PRIVATE "/W0"
	)
endif()

############
# stretch_test
add_executable(
  stretch_test
  stretch_test.c
  ../stretchy_buffer.h
  ../stb_truetype.h
  )

############
# stb_cpp
add_executable(
  stb_cpp
  stb_cpp.cpp
  test_cpp_compilation.cpp
  ../stb_vorbis.c
  ../stb.h
  ../stb_c_lexer.h
  ../stb_connected_components.h
  ../stb_divide.h
  ../stb_dxt.h
  ../stb_easy_font.h
  ../stb_herringbone_wang_tile.h
  ../stb_image.h
  ../stb_image_resize.h
  ../stb_image_write.h
  ../stb_leakcheck.h
  ../stb_perlin.h
  ../stb_rect_pack.h
  ../stb_sprintf.h
  ../stb_textedit.h
  ../stb_tilemap_editor.h
  ../stb_truetype.h
  ../stb_voxel_render.h
  ../stretchy_buffer.h
  )

if(MSVC)
  target_compile_options(
	stb_cpp
	PRIVATE "/W0"
	)
endif()

############
# stb_borbis from Makefile
if(0)
  add_executable(
	stb_borbis
	../stb_vorbis.c
	test_c_compilation.c
	test_cpp_compilation.cpp
	)

  target_link_libraries(
	stb_borbis
	-lm
	)
endif()
