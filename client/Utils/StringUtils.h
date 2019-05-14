#pragma once
#include "../NovusTypes.h"
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

namespace StringUtils
{
    inline std::vector<std::string> SplitString(std::string string, char delim = ' ')
    {
        std::vector<std::string> results;
        std::stringstream ss(string);
        std::string token;

        while (std::getline(ss, token, delim))
        {
            results.push_back(token);
        }

        return results;
    }

    template <typename... Args>
    inline i32 FormatString(char* buffer, size_t bufferSize, char const* format, Args... args)
    {
        i32 length = -1;
#ifdef _WIN32
        length = sprintf_s(buffer, bufferSize, format, args...);
#else
        (void)bufferSize; // Get rid of warning
        length = sprintf(buffer, format, args...);
#endif
        assert(length > -1);
        return length;
    }
}