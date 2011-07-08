#include "tmfs.hh"

int tmfs_readdir(const char * path, void * buf, fuse_fill_dir_t filler_cb, off_t offset,
                 struct fuse_file_info * fi)
{
  // get the real path
  std::string real_path = get_real_path(path);

  // checks if it's really a directory
  if (!bfs::is_directory(real_path))
    return -ENOTDIR;

  struct stat stbuf;

  // report ./ and ../
  stbuf.st_mode = __S_IFDIR | 0755;
  stbuf.st_nlink = 2;
  filler_cb(buf, ".", &stbuf, 0);
  filler_cb(buf, "..", &stbuf, 0);

  // now iterate over the real directory
  DIR * dir = opendir(real_path.c_str());
  if (!dir)
    return 0;

  struct dirent * entry;
  while ((entry = readdir(dir)))
  {
    // stat the file pointed by entry
    bfs::path path = bfs::path(real_path) / entry->d_name;
    if (stat(path.c_str(), &stbuf))
      continue;
    stbuf.st_mode |= 0755;
    // report the entry
    filler_cb(buf, entry->d_name, &stbuf, 0);
  }
  closedir(dir);

  return 0;
}
