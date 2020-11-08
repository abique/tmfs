#include "tmfs.hh"

static std::string _get_real_path(const std::string & str)
{
  // use the relative path so that the real_path doesn't get replaced
  const auto clean_path = fs::path(str).relative_path();

  fs::path real_path(tmfs::instance().hfs_root());
  real_path /= "Backups.backupdb"; // ${hfs_root}/Backups.backupdb/

  // ok let's copy the 3 first part of the virtual path
  // (${comp_name}, ${date}, ${disk_name})
  auto it = clean_path.begin();
  for (int i = 0; i < 3 && it != clean_path.end(); ++i, ++it)
    real_path /= *it;

  // let's resolv all the parts of the path
  struct stat stbuf;
  for (; it != clean_path.end(); ++it)
  {
    real_path /= *it;
    // Does the file exists ?
    if (lstat(real_path.string().c_str(), &stbuf))
      return real_path.string();

    // Is the file a dir_id ?
    if (S_ISREG(stbuf.st_mode) && stbuf.st_size == 0 && stbuf.st_nlink > 0)
    {
      // build the real path
      fs::path dir_path = tmfs::instance().hfs_root();
      dir_path /= ".HFS+ Private Directory Data\r/dir_" + std::to_string(stbuf.st_nlink);

      // check if it's really a ${dir_id}
      if (stat(dir_path.c_str(), &stbuf))
        continue; // it's not
      real_path = dir_path; // it is
    }
  }
  return real_path.string();
}

std::string get_real_path(const std::string & str)
{
  auto result = _get_real_path(str);
#ifndef NDEBUG
  std::cout << "get_real_path(\"" << str << "\") -> "  << result << std::endl;
#endif
  return result;
}
