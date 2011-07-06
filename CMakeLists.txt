cmake_minimum_required(VERSION 2.8)

project(fuse-time-machine C CXX)

find_package(PkgConfig)
pkg_check_modules(FUSE REQUIRED fuse)

add_definitions(-std=c99 ${FUSE_CFLAGS})

add_executable(fuse-time-machine
  src/main.c
  src/opendir.c
  src/readdir.c
)

link_directories(${FUSE_LIBRARY_DIRS})
target_link_libraries(fuse-time-machine ${FUSE_LIBRARIES})
