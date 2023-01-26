#include "FileIO.h"
#include <fstream>

namespace engine
{
    std::string GetStringFromFile(const std::string &path)
    {
        std::ifstream stream(path);
        std::string line, content;

        while (std::getline(stream, line))
        {
            content += (line + "\n");
        }
        return content;
    }
}