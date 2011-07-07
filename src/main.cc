#include "tmfs.hh"

int main(int argc, char ** argv)
{
  if (argc < 3)
  {
    fprintf(stderr, "%s: <path> fuse-options...\n", argv[0]);
    return 2;
  }

  /* global structure setup */
  tmfs::instance().hfs_root_ = argv[1];
  --argc;
  for (int i = 1; i < argc; ++i)
    argv[i] = argv[i + 1];

  /* vtable setup */
  struct fuse_operations ops;
  memset(&ops, 0, sizeof (ops));
  ops.read    = tmfs_read;
  ops.getattr = tmfs_getattr;
  ops.readdir = tmfs_readdir;

  /* lets go */
  fuse_main(argc, argv, &ops, NULL);
  return 0;
}
