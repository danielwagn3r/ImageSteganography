cmake_minimum_required (VERSION 3.0)

project(ImageSteganography)

set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)

set(SOURCE
  steg.c
  ppm.c
)

set(HEADERS
  steg.h
  ppm.h
)

add_executable(steg ${SOURCE} ${HEADERS})