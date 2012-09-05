#
# Copyright 2012 Netz39 e.V.
#
project(x16)
cmake_minimum_required(VERSION 2.8)

set(PACKAGE_MAJOR_VERSION "0")
set(PACKAGE_MINOR_VERSION "1")
set(PACKAGE_BUILD_VERSION "0")
set(PACKAGE_VERSION "${PACKAGE_MAJOR_VERSION}.${PACKAGE_MINOR_VERSION}.${PACKAGE_BUILD_VERSION}")

find_library(LIBGD2_LIBRARY NAMES gd)
set(LOGO_FILENAME "logo.png"
    CACHE STRING "filename of the created file")

add_subdirectory("src")
