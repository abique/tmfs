#pragma once

#define FUSE_USE_VERSION 26

#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <dirent.h>

#include <fuse.h>

#include <map>
#include <string>
#include <vector>
#include <sstream>
#include <iostream>

#include <filesystem>

namespace fs = std::filesystem;

/** this is the global structure of tmfs */
struct tmfs {
  inline const fs::path & hfs_root() const noexcept { return hfs_root_; }
  static inline tmfs & instance() { static tmfs i; return i; }

  fs::path  hfs_root_; // the hfs root
};

/** transforms a virtual paths in the tmfs's root to the real path in hfs's root */
std::string get_real_path(const std::string & path);

/** fuse functions
 * @{ */
int tmfs_getattr(const char * path, struct stat *stbuf);
int tmfs_readdir(const char * path, void * buf, fuse_fill_dir_t filler_callback,
                 off_t offset, struct fuse_file_info * fi);
int tmfs_read(const char * path, char * buf, size_t nbytes, off_t offset,
              struct fuse_file_info * fi);
int tmfs_readlink(const char * path, char * buf, size_t size);
/** @} */
