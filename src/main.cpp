#include <iostream>
#include <string>
#include <cstring>
#include "VaultX.h"
#include "OutputHandler.h"

// ── printUsage ────────────────────────────────────────────────────────────────
static void printUsage(const char* prog) {
    std::cout <<
        "\nUsage:\n"
        "  " << prog << " <mode> <key> <input_file> [output_file] [--algo <xor|caesar>]\n\n"
        "Modes:\n"
        "  encrypt    Encrypt the input file\n"
        "  decrypt    Decrypt the input file\n\n"
        "Options:\n"
        "  --algo xor      Use XOR cipher (default)\n"
        "  --algo caesar   Use Caesar byte-shift cipher\n\n"
        "Examples:\n"
        "  " << prog << " encrypt mySecret report.pdf\n"
        "  " << prog << " decrypt mySecret report.pdf.vx report_original.pdf\n"
        "  " << prog << " encrypt myKey data.txt --algo caesar\n\n";
}

// ── main ──────────────────────────────────────────────────────────────────────
int main(int argc, char* argv[]) {
    std::cout << "\033[1m\033[36m"
              << " __   __          _ _    __  __\n"
              << " \\ \\ / /_ _ _   _| | |_  \\ \\/ /\n"
              << "  \\ V / _` | | | | | __|  \\  /\n"
              << "   | | (_| | |_| | | |_   /  \\\n"
              << "   |_|\\__,_|\\__,_|_|\\__| /_/\\_\\\n"
              << "\033[0m"
              << "  Secure File Encryptor/Decryptor  v1.0\n\n";

    if (argc < 4) {
        printUsage(argv[0]);
        return 1;
    }

    std::string mode      = argv[1];
    std::string key       = argv[2];
    std::string inputFile = argv[3];
    std::string outputFile;
    Algorithm   algo      = Algorithm::XOR_CIPHER;

    // Parse optional args
    for (int i = 4; i < argc; ++i) {
        if (std::strcmp(argv[i], "--algo") == 0 && i + 1 < argc) {
            std::string algoStr = argv[++i];
            if (algoStr == "caesar") algo = Algorithm::CAESAR_SHIFT;
            else if (algoStr != "xor") {
                OutputHandler::log(LogLevel::ERROR_LEVEL,
                    "Unknown algorithm '" + algoStr + "'. Use 'xor' or 'caesar'.");
                return 1;
            }
        } else {
            outputFile = argv[i];   // treat unknown positional as output path
        }
    }

    try {
        VaultX vault(key, algo, /*verbose=*/true);

        if (mode == "encrypt") {
            vault.encryptFile(inputFile, outputFile);
        } else if (mode == "decrypt") {
            vault.decryptFile(inputFile, outputFile);
        } else {
            OutputHandler::log(LogLevel::ERROR_LEVEL,
                "Unknown mode '" + mode + "'. Use 'encrypt' or 'decrypt'.");
            printUsage(argv[0]);
            return 1;
        }
    } catch (...) {
        return 1;   // Error already logged inside VaultX
    }

    return 0;
}
