#include "tmfs.hh"

int tmfs_read(const char * path, char * buf, size_t nbytes, off_t offset,
              struct fuse_file_info * fi)
{
  // get the real path
  std::string real_path = get_real_path(path);

  // open the file
  int fd = open(real_path.c_str(), O_RDONLY);
  if (fd < 0)
    return -errno;

  // read the data and close
  ssize_t bytes = pread(fd, buf, nbytes, offset);
  close(fd);
  if (bytes < 0)
    return -errno;
  return bytes;
}
