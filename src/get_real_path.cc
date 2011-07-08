#include "tmfs.hh"

std::string get_real_path(const std::string & str)
{
  // removes ../.././././//./ garbage
  bfs::path clean_path = bfs::absolute(str, "/");
  bfs::path real_path(tmfs::instance().hfs_root());
  real_path /= "Backups.backupdb"; // ${hfs_root}/Backups.backupdb/

  // ok let's copy the 4 first part of the virtual path
  // (/, ${comp_name}, ${date}, ${disk_name})
  bfs::path::const_iterator it = clean_path.begin();
  for (int i = 0; i < 4; ++i, ++it)
  {
    if (it == clean_path.end())
      return real_path.string();
    real_path /= *it;
  }

  // let's resolv all the parts of the path
  struct stat stbuf;
  for (; it != clean_path.end(); ++it)
  {
    real_path /= *it;
    // Does the file exists ?
    if (stat(real_path.c_str(), &stbuf))
      return real_path.string();

    // Is the file a dir_id ?
    if (S_ISREG(stbuf.st_mode) && stbuf.st_size == 0 && stbuf.st_nlink > 0)
    {
      // build the real path
      std::ostringstream os;
      os << tmfs::instance().hfs_root() << "/.HFS+ Private Directory Data\r/dir_" << stbuf.st_nlink;

      // check if it's really a ${dir_id}
      if (stat(os.str().c_str(), &stbuf))
        continue; // it's not
      real_path = os.str(); // it is
    }
  }
  return real_path.string();
}
