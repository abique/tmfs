#include "tmfs.hh"

#include <sstream>

/** options for fuse_opt.h */
struct tmfs g_tmfs;

static struct fuse_operations g_tmfs_operations;

tmfs_computer::tmfs_computer(const std::string & name, const std::string & root)
 : name_(name),
   root_(root)
{
  DIR * dir = opendir(root.c_str());
  if (!dir)
    return;

  struct dirent * entry;
  while (entry = readdir(dir))
  {
    if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "."))
      continue;

    dates_.push_back(entry->d_name);
  }

  closedir(dir);
}

static void load_data()
{
  std::ostringstream os;
  os << g_tmfs.hfs_root << "/Backups.backupdb/";

  std::string db_dir = os.str();
  DIR * dir = opendir(db_dir.c_str());
  if (!dir)
    return;

  struct dirent * entry;
  while (entry = readdir(dir))
  {
    if (!strcmp(entry->d_name, ".") || !strcmp(entry->d_name, "."))
      continue;

    os.str(db_dir);
    os << entry->d_name;
    g_tmfs.comps[entry->d_name] = new tmfs_computer(entry->d_name, os.str());
  }

  closedir(dir);
}

int main(int argc, char ** argv)
{
  if (argc < 3)
  {
    fprintf(stderr, "%s: <path> fuse-options...\n", argv[0]);
    return 2;
  }
  g_tmfs.hfs_root = argv[1];
  --argc;
  for (int i = 1; i < argc; ++i)
    argv[i] = argv[i + 1];

  g_tmfs.uid = getuid();
  g_tmfs.gid = getgid();
  memset(&g_tmfs_operations, 0, sizeof (g_tmfs_operations));
  g_tmfs_operations.getattr = tmfs_getattr;
  g_tmfs_operations.readdir = tmfs_readdir;

  load_data();

  fuse_main(argc, argv, &g_tmfs_operations, NULL);
  return 0;
}
