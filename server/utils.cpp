#include "utils.hpp"

std::wstring Utils::StringToWString(const std::string& s)
{
        std::wstring temp(s.length(),L' ');
        std::copy(s.begin(), s.end(), temp.begin());
        return temp;
}
