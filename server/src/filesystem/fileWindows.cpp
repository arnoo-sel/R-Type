#include "filesystem/fileWindows.hpp"

FileWindows::FileWindows() : opened(false)
{}


FileWindows::FileWindows(const string& path) : opened(false)
{
    open(path);
}

void		FileWindows::open(const std::string &path)
{
	std::wstring  wsPath = StringToWString(path);

    if (opened == true)
        close();
    hFile = CreateFile(path.c_str(), GENERIC_READ | GENERIC_WRITE,
		       FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
    if (hFile == INVALID_HANDLE_VALUE)
        throw new FileException("Could not open file", path);
    opened = true;
}




void	FileWindows::close()
{
	if (opened == true && CloseHandle(hFile) == false)
        throw new FileException("Can't close opened file");
    opened = false;
}

string		FileWindows::read(int len)
{
	char 	*tmpBuff = new char[len];
	DWORD	nbRead;
	string  out;

	if (opened == false || ReadFile(hFile, tmpBuff, len, &nbRead, NULL) == 0)
	{
        delete[] tmpBuff;
        throw new FileException("Could not read file");
	}
    out = string(tmpBuff, nbRead);
    delete[] tmpBuff;
	return out;
}



int			FileWindows::write(const std::string &buff)
{
	DWORD	nbWritten;

	if (opened == false || WriteFile(hFile, (LPCVOID) buff.c_str(),
                                        buff.length(), &nbWritten, NULL) == 0)
        throw new FileException("Could not write file");
	return nbWritten;
}

std::wstring StringToWString(const std::string& s)
{
	std::wstring temp(s.length(),L' ');
	std::copy(s.begin(), s.end(), temp.begin());
	return temp;
}
