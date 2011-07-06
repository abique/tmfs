#ifndef TMFS_H
# define TMFS_H

# define FUSE_USE_VERSION 26

# include <sys/time.h>
# include <stdlib.h>
# include <fuse.h>
# include <stdio.h>
# include <string.h>
# include <errno.h>
# include <fcntl.h>

struct tmfs {
  const char * rootdir;
};

int tmfs_opendir(const char *, struct fuse_file_info *);
int tmfs_readdir(const char *, void *, fuse_fill_dir_t, off_t,
                 struct fuse_file_info *);

#endif /* !TMFS_H */
