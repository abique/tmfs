#include "tmfs.hh"

int tmfs_readlink(const char * path, char * buf, size_t size)
{
  if (size < 1)
    return 0;

  // get the real path
  std::string real_path = get_real_path(path);

  // and now just readlink the real path
  ssize_t result = readlink(real_path.c_str(), buf, size - 1);
  if (result < 0)
    return -errno;
  buf[result] = 0;
  return 0;
}
