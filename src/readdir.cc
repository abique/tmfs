#include "tmfs.hh"

int tmfs_readdir(const char * path, void * buf, fuse_fill_dir_t filler_cb, off_t offset,
                 struct fuse_file_info * fi)
{
  std::string real_path = get_real_path(path);

  if (!bfs::is_directory(real_path))
    return -ENOTDIR;

  struct stat stbuf;

  stbuf.st_mode = __S_IFDIR | 0755;
  stbuf.st_nlink = 2;
  stbuf.st_uid = g_tmfs.uid_;
  stbuf.st_gid = g_tmfs.gid_;

  filler_cb(buf, ".", &stbuf, 0);
  filler_cb(buf, "..", &stbuf, 0);


  DIR * dir = opendir(real_path.c_str());
  if (!dir)
    return 0;

  struct dirent * entry;
  while ((entry = readdir(dir)))
  {
    auto path = bfs::path(real_path) / entry->d_name;
    stat(path.c_str(), &stbuf);
    stbuf.st_mode |= 0755;
    stbuf.st_uid = g_tmfs.uid_;
    stbuf.st_gid = g_tmfs.gid_;
    filler_cb(buf, entry->d_name, &stbuf, 0);
  }
  closedir(dir);

  return 0;
}
