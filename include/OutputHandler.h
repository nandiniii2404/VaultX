#pragma once
#include <string>
#include <vector>

// Log severity levels
enum class LogLevel { INFO, SUCCESS, WARNING, ERROR_LEVEL };

class OutputHandler {
public:
    // Print a timestamped, colored log message to stderr/stdout
    static void log(LogLevel level, const std::string& message);

    // Print a summary table: original path, output path, bytes, algorithm
    static void printSummary(const std::string& inputPath,
                             const std::string& outputPath,
                             size_t             bytesProcessed,
                             const std::string& algorithm,
                             bool               encrypted);

    // Print progress bar (useful for large files)
    static void printProgress(size_t current, size_t total, const std::string& label = "");

    // Build a default output filename: adds/removes ".vx" extension
    static std::string buildOutputPath(const std::string& inputPath, bool encrypting);
};
