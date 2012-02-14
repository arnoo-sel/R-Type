#include "filesystem/fileUnix.hpp"

FileUnix::FileUnix() : opened(false)
{}

FileUnix::FileUnix(const string& path) : opened(false)
{
    open(path);
}

void        FileUnix::open(const std::string &path)
{
  hFile = ::open(path.c_str(), O_RDWR | O_CREAT, 0644);

  if (opened == true)
    close();
  if (hFile == -1)
    throw new FileException("Could not open file", path);
  opened = true;
}

void    	FileUnix::close()
{
  if (opened == true && ::close(hFile) == -1)
    throw new FileException("Can't close opened file");
  opened = false;
}

string		FileUnix::read(int len)
{
  char *tmpBuff = new char[10];
  string out;
  
  int nbRead = ::read(hFile, tmpBuff, len);
  if (nbRead == -1)
    {
      delete[] tmpBuff;
      throw new FileException("Could not read file");
    }
  out = string(tmpBuff, nbRead);
  delete[] tmpBuff;
  return out;
}

int				FileUnix::write(const std::string &buff)
{
  int nbWritten = ::write(hFile, buff.c_str(), buff.length());
  if (nbWritten == -1)
    throw new FileException("Could not write file");
  return nbWritten;
}
