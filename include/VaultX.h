#pragma once
#include <string>
#include "EncryptionEngine.h"

// High-level interface: ties FileManager, EncryptionEngine, and OutputHandler together
class VaultX {
public:
    VaultX(const std::string& key,
           Algorithm          algo       = Algorithm::XOR_CIPHER,
           bool               verbose    = true);

    // Encrypt inputPath -> outputPath (auto-named if empty)
    void encryptFile(const std::string& inputPath,
                     const std::string& outputPath = "");

    // Decrypt inputPath -> outputPath (auto-named if empty)
    void decryptFile(const std::string& inputPath,
                     const std::string& outputPath = "");

private:
    std::string      m_key;
    Algorithm        m_algo;
    bool             m_verbose;

    void processFile(const std::string& inputPath,
                     const std::string& outputPath,
                     bool               encrypting);
};
