#include "tmfs.hh"

int tmfs_getattr(const char *path, struct stat *stbuf)
{
  int res = 0;
  memset(stbuf, 0, sizeof(struct stat));
  if(strcmp(path, "/") == 0) {
    stbuf->st_mode = __S_IFDIR | 0755;
    stbuf->st_nlink = 2;
    stbuf->st_uid = g_tmfs.uid;
    stbuf->st_gid = g_tmfs.gid;
  }
  else
    res = -ENOENT;

  return res;
}
