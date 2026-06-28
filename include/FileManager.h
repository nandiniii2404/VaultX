#pragma once
#include <string>
#include <vector>
#include <stdexcept>

class FileManager {
public:
    // Read raw bytes from a file
    static std::vector<unsigned char> readFile(const std::string& path);

    // Write raw bytes to a file
    static void writeFile(const std::string& path, const std::vector<unsigned char>& data);

    // Check if a file exists and is accessible
    static bool fileExists(const std::string& path);

    // Get file size in bytes
    static size_t fileSize(const std::string& path);

    // Validate that a path is not empty and accessible
    static void validatePath(const std::string& path);
};
