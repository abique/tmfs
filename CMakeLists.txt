cmake_minimum_required(VERSION 2.8)

project(TMFS C CXX)

find_package(PkgConfig)
pkg_check_modules(FUSE REQUIRED fuse)

add_definitions(${FUSE_CFLAGS})

add_executable(tmfs
  src/main.cc
  src/opendir.cc
  src/readdir.cc
  src/getattr.cc
)

link_directories(${FUSE_LIBRARY_DIRS})
target_link_libraries(tmfs ${FUSE_LIBRARIES})
