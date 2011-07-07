#include "tmfs.hh"

int tmfs_getattr(const char *path, struct stat *stbuf)
{
  // get the real path
  std::string real_path = get_real_path(path);

  // and now just stat the real path
  memset(stbuf, 0, sizeof(struct stat));
  if (stat(real_path.c_str(), stbuf))
    return -errno;
  return 0;
}
