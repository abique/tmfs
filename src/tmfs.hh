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

struct tmfs_computer {
  tmfs_computer(const std::string & name, const std::string & root);
  std::string name_;
  std::string root_;
  std::vector<std::string> dates_;
};

struct tmfs {
  std::string  hfs_root;
  uid_t        uid;
  gid_t        gid;
  std::map<std::string, tmfs_computer*> comps;
};

extern struct tmfs g_tmfs;

int tmfs_getattr(const char *path, struct stat *stbuf);
int tmfs_opendir(const char *, struct fuse_file_info *);
int tmfs_readdir(const char *, void *, fuse_fill_dir_t, off_t,
                 struct fuse_file_info *);

#endif /* !TMFS_HH */
