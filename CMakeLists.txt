cmake_minimum_required(VERSION 2.8)

project(TMFS CXX)

set(Boost_USE_STATIC_LIBS        OFF)
set(Boost_USE_MULTITHREADED      OFF)
set(Boost_USE_STATIC_RUNTIME     OFF)
set(Boost_DEBUG                  OFF)
find_package(Boost 1.46 COMPONENTS system filesystem)

find_package(PkgConfig)
pkg_check_modules(FUSE REQUIRED fuse)

add_definitions(${FUSE_CFLAGS} -Wall)
include_directories(${Boost_INCLUDE_DIRS})

add_executable(tmfs
  src/main.cc
  src/readdir.cc
  src/read.cc
  src/getattr.cc
  src/get_real_path.cc
)

link_directories(${FUSE_LIBRARY_DIRS} ${Boost_LIBRARY_DIRS})
target_link_libraries(tmfs ${FUSE_LIBRARIES} ${Boost_LIBRARIES})
install(TARGETS tmfs RUNTIME DESTINATION bin
  PERMISSIONS OWNER_READ OWNER_WRITE OWNER_EXECUTE
              GROUP_READ GROUP_EXECUTE
              WORLD_READ WORLD_EXECUTE)
