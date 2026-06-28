#include "VaultX.h"
#include "FileManager.h"
#include "EncryptionEngine.h"
#include "OutputHandler.h"
#include <stdexcept>

// ── Constructor ───────────────────────────────────────────────────────────────
VaultX::VaultX(const std::string& key, Algorithm algo, bool verbose)
    : m_key(key), m_algo(algo), m_verbose(verbose) {}

// ── encryptFile ───────────────────────────────────────────────────────────────
void VaultX::encryptFile(const std::string& inputPath,
                          const std::string& outputPath) {
    processFile(inputPath, outputPath, true);
}

// ── decryptFile ───────────────────────────────────────────────────────────────
void VaultX::decryptFile(const std::string& inputPath,
                          const std::string& outputPath) {
    processFile(inputPath, outputPath, false);
}

// ── processFile (private) ─────────────────────────────────────────────────────
void VaultX::processFile(const std::string& inputPath,
                          const std::string& outputPath,
                          bool               encrypting) {
    try {
        // 1. Validate input
        if (m_verbose)
            OutputHandler::log(LogLevel::INFO,
                (encrypting ? "Encrypting: " : "Decrypting: ") + inputPath);

        // 2. Read file
        std::vector<unsigned char> data = FileManager::readFile(inputPath);
        size_t totalBytes = data.size();

        if (m_verbose)
            OutputHandler::printProgress(0, totalBytes, "Reading ");

        // 3. Encrypt or decrypt
        EncryptionEngine engine(m_key, m_algo);
        std::vector<unsigned char> result =
            encrypting ? engine.encrypt(data) : engine.decrypt(data);

        if (m_verbose)
            OutputHandler::printProgress(totalBytes, totalBytes, "Processing");

        // 4. Determine output path
        std::string outPath = outputPath.empty()
            ? OutputHandler::buildOutputPath(inputPath, encrypting)
            : outputPath;

        // 5. Write result
        FileManager::writeFile(outPath, result);

        // 6. Report success
        if (m_verbose) {
            OutputHandler::log(LogLevel::SUCCESS, "Done.");
            OutputHandler::printSummary(inputPath, outPath, totalBytes,
                                        engine.algorithmName(), encrypting);
        }

    } catch (const std::invalid_argument& e) {
        OutputHandler::log(LogLevel::ERROR_LEVEL, std::string("Input error: ") + e.what());
        throw;
    } catch (const std::runtime_error& e) {
        OutputHandler::log(LogLevel::ERROR_LEVEL, std::string("Runtime error: ") + e.what());
        throw;
    }
}
