#include "tmfs.hh"

int tmfs_getattr(const char *path, struct stat *stbuf)
{
  std::string real_path = get_real_path(path);

  std::cout << " ## getattr " << bfs::path(path) << " -> " << real_path << std::endl;

  memset(stbuf, 0, sizeof(struct stat));
  if (stat(real_path.c_str(), stbuf))
    return -errno;
  return 0;
}
