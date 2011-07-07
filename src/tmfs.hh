#ifndef TMFS_HH
# define TMFS_HH

# define FUSE_USE_VERSION 26

# include <sys/time.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <dirent.h>

# include <fuse.h>

# include <map>
# include <string>
# include <vector>
# include <sstream>

# include <boost/filesystem.hpp>

namespace bfs = boost::filesystem;

struct tmfs {
  inline const std::string & hfs_root() const { return hfs_root_; }

  std::string  hfs_root_;
  uid_t        uid_;
  gid_t        gid_;
};

std::string get_real_path(const std::string & path);

extern struct tmfs g_tmfs;

int tmfs_getattr(const char *path, struct stat *stbuf);
int tmfs_opendir(const char *, struct fuse_file_info *);
int tmfs_readdir(const char *, void *, fuse_fill_dir_t, off_t,
                 struct fuse_file_info *);
int tmfs_read(const char * path, char * buf, size_t nbytes, off_t offset,
              struct fuse_file_info * fi);

#endif /* !TMFS_HH */
