#pragma once
#include <vector>
#include <string>
#include <cstdint>

// Supported encryption algorithms
enum class Algorithm {
    XOR_CIPHER,    // XOR each byte with key bytes (cyclic)
    CAESAR_SHIFT   // Shift each byte by a numeric key value
};

class EncryptionEngine {
public:
    explicit EncryptionEngine(const std::string& key, Algorithm algo = Algorithm::XOR_CIPHER);

    // Encrypt data in-place; returns a new encrypted buffer
    std::vector<unsigned char> encrypt(const std::vector<unsigned char>& plainData) const;

    // Decrypt data in-place; returns a new decrypted buffer
    std::vector<unsigned char> decrypt(const std::vector<unsigned char>& cipherData) const;

    // Get name of the active algorithm
    std::string algorithmName() const;

private:
    std::string       m_key;
    Algorithm         m_algo;
    uint8_t           m_shift;  // pre-computed numeric shift for CAESAR_SHIFT

    // Internal helpers
    std::vector<unsigned char> applyXOR(const std::vector<unsigned char>& data) const;
    std::vector<unsigned char> applyShift(const std::vector<unsigned char>& data, bool forward) const;
};
