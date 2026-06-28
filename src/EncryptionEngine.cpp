#include "EncryptionEngine.h"
#include <stdexcept>
#include <numeric>

// ── Constructor ───────────────────────────────────────────────────────────────
EncryptionEngine::EncryptionEngine(const std::string& key, Algorithm algo)
    : m_key(key), m_algo(algo), m_shift(0)
{
    if (key.empty())
        throw std::invalid_argument("Encryption key must not be empty.");

    // Pre-compute shift: sum of all key bytes mod 256
    uint64_t sum = 0;
    for (unsigned char c : key) sum += c;
    m_shift = static_cast<uint8_t>(sum % 256);
}

// ── encrypt ───────────────────────────────────────────────────────────────────
std::vector<unsigned char> EncryptionEngine::encrypt(
        const std::vector<unsigned char>& plainData) const {
    switch (m_algo) {
        case Algorithm::XOR_CIPHER:  return applyXOR(plainData);
        case Algorithm::CAESAR_SHIFT: return applyShift(plainData, true);
    }
    throw std::logic_error("Unknown algorithm.");
}

// ── decrypt ───────────────────────────────────────────────────────────────────
std::vector<unsigned char> EncryptionEngine::decrypt(
        const std::vector<unsigned char>& cipherData) const {
    switch (m_algo) {
        case Algorithm::XOR_CIPHER:  return applyXOR(cipherData);    // XOR is self-inverse
        case Algorithm::CAESAR_SHIFT: return applyShift(cipherData, false);
    }
    throw std::logic_error("Unknown algorithm.");
}

// ── algorithmName ─────────────────────────────────────────────────────────────
std::string EncryptionEngine::algorithmName() const {
    return (m_algo == Algorithm::XOR_CIPHER) ? "XOR Cipher" : "Caesar Byte-Shift";
}

// ── applyXOR (private) ────────────────────────────────────────────────────────
std::vector<unsigned char> EncryptionEngine::applyXOR(
        const std::vector<unsigned char>& data) const {
    std::vector<unsigned char> result(data.size());
    size_t keyLen = m_key.size();
    for (size_t i = 0; i < data.size(); ++i)
        result[i] = data[i] ^ static_cast<unsigned char>(m_key[i % keyLen]);
    return result;
}

// ── applyShift (private) ──────────────────────────────────────────────────────
std::vector<unsigned char> EncryptionEngine::applyShift(
        const std::vector<unsigned char>& data, bool forward) const {
    std::vector<unsigned char> result(data.size());
    for (size_t i = 0; i < data.size(); ++i) {
        int val = static_cast<int>(data[i]);
        val = forward ? (val + m_shift) % 256
                      : (val - m_shift + 256) % 256;
        result[i] = static_cast<unsigned char>(val);
    }
    return result;
}
