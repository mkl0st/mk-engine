#ifndef MK_FILE_HPP
#define MK_FILE_HPP

#include <fstream>
#include <sstream>
#include <iostream>
#include <string>

namespace mk
{
  namespace File
  {
    /**
     * @brief Gets the contents of a file.
     * @param path The path to the file.
     * @return The contents of the file as a string. If the file is not found or cannot be opened, an empty string is returned.
     */
    std::string getContents(const std::string& path);
  }
}

#endif // MK_FILE_HPP
