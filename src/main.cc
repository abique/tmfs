#include "tmfs.hh"

int main(int argc, char ** argv)
{
  if (argc < 3)
  {
    fprintf(stderr, "Usage: %s: <HFS+ mount point> <Time Machine mount point>"
            " [FUSE options]\n", argv[0]);
    return 2;
  }

  /* global structure setup */
  tmfs::instance().hfs_root_ = fs::absolute(fs::path(argv[1]));
  --argc;
  for (int i = 1; i < argc; ++i)
    argv[i] = argv[i + 1];

  /* check that hfs_root is a directory */
  struct stat st;
  if (lstat(tmfs::instance().hfs_root_.c_str(), &st)) {
    fprintf(stderr, "%s: %m\n", tmfs::instance().hfs_root_.c_str());
    return 1;
  }

  if (!S_ISDIR(st.st_mode)) {
    fprintf(stderr, "%s: is not a directory\n", tmfs::instance().hfs_root_.c_str());
    return 1;
  }

  /* vtable setup */
  struct fuse_operations ops;
  memset(&ops, 0, sizeof (ops));
  ops.read    = tmfs_read;
  ops.getattr = tmfs_getattr;
  ops.readdir = tmfs_readdir;
  ops.readlink = tmfs_readlink;

  /* lets go */
  fuse_main(argc, argv, &ops, NULL);
  return 0;
}
