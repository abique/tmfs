#include "tmfs.hh"

std::string get_real_path(const std::string & str)
{
  bfs::path clean_path = bfs::absolute(str, "/");
  bfs::path real_path(g_tmfs.hfs_root());
  real_path /= "Backups.backupdb";

  auto it = clean_path.begin();
  for (int i = 0; i < 4; ++i, ++it)
  {
    if (it == clean_path.end())
      return real_path.string();
    real_path /= *it;
  }

  struct stat stbuf;
  for (; it != clean_path.end(); ++it)
  {
    real_path /= *it;
    if (stat(real_path.c_str(), &stbuf))
      return real_path.string();
    if (S_ISREG(stbuf.st_mode) && stbuf.st_size == 0 && stbuf.st_nlink > 0)
    {
      std::ostringstream os;
      os << g_tmfs.hfs_root() << "/.HFS+ Private Directory Data\r/dir_" << stbuf.st_nlink;
      real_path = os.str();
      std::cout << "--------- " << real_path << std::endl;
    }
  }
  return real_path.string();
}
