#include "tmfs.hh"

#include <sstream>

struct tmfs g_tmfs;

int main(int argc, char ** argv)
{
  if (argc < 3)
  {
    fprintf(stderr, "%s: <path> fuse-options...\n", argv[0]);
    return 2;
  }

  struct fuse_operations ops;

  /* global structure setup */
  g_tmfs.uid_ = getuid();
  g_tmfs.gid_ = getgid();
  g_tmfs.hfs_root_ = argv[1];
  --argc;
  for (int i = 1; i < argc; ++i)
    argv[i] = argv[i + 1];

  /* vtable setup */
  memset(&ops, 0, sizeof (ops));
  ops.read = tmfs_read;
  ops.getattr = tmfs_getattr;
  ops.readdir = tmfs_readdir;

  /* lets go */
  fuse_main(argc, argv, &ops, NULL);
  return 0;
}
