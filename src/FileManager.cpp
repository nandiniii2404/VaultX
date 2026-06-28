#include "FileManager.h"
#include <fstream>
#include <sstream>
#include <sys/stat.h>

// ── readFile ─────────────────────────────────────────────────────────────────
std::vector<unsigned char> FileManager::readFile(const std::string& path) {
    validatePath(path);

    std::ifstream ifs(path, std::ios::binary | std::ios::ate);
    if (!ifs.is_open())
        throw std::runtime_error("Cannot open file for reading: " + path);

    std::streamsize sz = ifs.tellg();
    if (sz < 0)
        throw std::runtime_error("Failed to determine file size: " + path);

    ifs.seekg(0, std::ios::beg);

    std::vector<unsigned char> buffer(static_cast<size_t>(sz));
    if (sz > 0 && !ifs.read(reinterpret_cast<char*>(buffer.data()), sz))
        throw std::runtime_error("Read error on file: " + path);

    return buffer;
}

// ── writeFile ─────────────────────────────────────────────────────────────────
void FileManager::writeFile(const std::string& path,
                             const std::vector<unsigned char>& data) {
    if (path.empty())
        throw std::invalid_argument("Output path must not be empty.");

    std::ofstream ofs(path, std::ios::binary | std::ios::trunc);
    if (!ofs.is_open())
        throw std::runtime_error("Cannot open file for writing: " + path);

    if (!data.empty())
        ofs.write(reinterpret_cast<const char*>(data.data()),
                  static_cast<std::streamsize>(data.size()));

    if (ofs.fail())
        throw std::runtime_error("Write error on file: " + path);
}

// ── fileExists ────────────────────────────────────────────────────────────────
bool FileManager::fileExists(const std::string& path) {
    struct stat st;
    return (stat(path.c_str(), &st) == 0) && (st.st_mode & S_IFREG);
}

// ── fileSize ──────────────────────────────────────────────────────────────────
size_t FileManager::fileSize(const std::string& path) {
    validatePath(path);
    struct stat st;
    if (stat(path.c_str(), &st) != 0)
        throw std::runtime_error("Cannot determine file size: " + path);
    return static_cast<size_t>(st.st_size);
}

// ── validatePath ──────────────────────────────────────────────────────────────
void FileManager::validatePath(const std::string& path) {
    if (path.empty())
        throw std::invalid_argument("File path must not be empty.");
    if (!fileExists(path))
        throw std::runtime_error("File not found or not a regular file: " + path);
}
