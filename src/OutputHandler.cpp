#include "OutputHandler.h"
#include <iostream>
#include <iomanip>
#include <sstream>

// ANSI color codes
static const char* RESET   = "\033[0m";
static const char* CYAN    = "\033[36m";
static const char* GREEN   = "\033[32m";
static const char* YELLOW  = "\033[33m";
static const char* RED     = "\033[31m";
static const char* BOLD    = "\033[1m";

// ── log ───────────────────────────────────────────────────────────────────────
void OutputHandler::log(LogLevel level, const std::string& message) {
    const char* color  = RESET;
    const char* prefix = "";

    switch (level) {
        case LogLevel::INFO:        color = CYAN;   prefix = "[INFO]   "; break;
        case LogLevel::SUCCESS:     color = GREEN;  prefix = "[OK]     "; break;
        case LogLevel::WARNING:     color = YELLOW; prefix = "[WARN]   "; break;
        case LogLevel::ERROR_LEVEL: color = RED;    prefix = "[ERROR]  "; break;
    }

    std::cout << BOLD << color << prefix << RESET << message << "\n";
}

// ── printSummary ──────────────────────────────────────────────────────────────
void OutputHandler::printSummary(const std::string& inputPath,
                                  const std::string& outputPath,
                                  size_t             bytesProcessed,
                                  const std::string& algorithm,
                                  bool               encrypted) {
    std::string op = encrypted ? "ENCRYPTED" : "DECRYPTED";

    std::cout << "\n" << BOLD << GREEN << "--- VaultX Summary ---" << RESET << "\n";
    std::cout << std::left << std::setw(18) << "  Operation:"    << op             << "\n";
    std::cout << std::left << std::setw(18) << "  Algorithm:"    << algorithm      << "\n";
    std::cout << std::left << std::setw(18) << "  Input:"        << inputPath      << "\n";
    std::cout << std::left << std::setw(18) << "  Output:"       << outputPath     << "\n";
    std::cout << std::left << std::setw(18) << "  Bytes:"        << bytesProcessed << "\n";
    std::cout << BOLD << GREEN << "----------------------" << RESET << "\n\n";
}

// ── printProgress ─────────────────────────────────────────────────────────────
void OutputHandler::printProgress(size_t current, size_t total,
                                   const std::string& label) {
    if (total == 0) return;
    int pct  = static_cast<int>((current * 100) / total);
    int bars = pct / 5;
    std::cout << "\r" << CYAN << (label.empty() ? "Processing" : label) << " ["
              << std::string(bars, '=')
              << std::string(20 - bars, ' ')
              << "] " << pct << "%" << RESET << std::flush;
    if (current >= total) std::cout << "\n";
}

// ── buildOutputPath ───────────────────────────────────────────────────────────
std::string OutputHandler::buildOutputPath(const std::string& inputPath, bool encrypting) {
    if (encrypting) {
        return inputPath + ".vx";
    } else {
        if (inputPath.size() > 3 &&
            inputPath.substr(inputPath.size() - 3) == ".vx")
            return inputPath.substr(0, inputPath.size() - 3);
        return inputPath + ".dec";
    }
}
