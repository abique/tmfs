#include "tmfs.hh"

int tmfs_readdir(const char * path, void * buf, fuse_fill_dir_t filler_cb, off_t offset,
                 struct fuse_file_info * fi)
{
  puts(path);

  struct stat stbuf;

  stbuf.st_mode = __S_IFDIR | 0755;
  stbuf.st_nlink = 2;
  stbuf.st_uid = g_tmfs.uid;
  stbuf.st_gid = g_tmfs.gid;
  filler_cb(buf, ".", &stbuf, 0);
  filler_cb(buf, "..", &stbuf, 0);

  return 0;
}
