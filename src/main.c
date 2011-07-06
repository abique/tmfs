#include "tmfs.h"

static const struct fuse_operations g_tmfs_operations = {
  .getattr = 0,
  .readlink = 0,
  .getdir = 0,
  .mknod = 0,
  .mkdir = 0,
  .unlink = 0,
  .rmdir = 0,
  .symlink = 0,
  .rename = 0,
  .link = 0,
  .chmod = 0,
  .chown = 0,
  .truncate = 0,
  .utime = 0,
  .open = 0,
  .read = 0,
  .write = 0,
  .statfs = 0,
  .flush = 0,
  .release = 0,
  .fsync = 0,
  .setxattr = 0,
  .getxattr = 0,
  .listxattr = 0,
  .removexattr = 0,
  .opendir = 0,
  .readdir = tmfs_readdir,
  .releasedir = 0,
  .fsyncdir = 0,
  .init = 0,
  .destroy = 0,
  .access = 0,
  .create = 0,
  .ftruncate = 0,
  .fgetattr = 0,
  .lock = 0,
  .utimens = 0,
  .bmap = 0,
  .flag_nullpath_ok = 0,
  .ioctl = 0,
  .poll = 0,
};

int main(int argc, char ** argv)
{
  fuse_main(argc, argv, &g_tmfs_operations, NULL);
  return 0;
}
