# VaultX — File Encryptor & Decryptor

A modular, object-oriented C++ system for secure file encryption and decryption.

## Tech Stack
- **Language:** C++17
- **Design:** OOP with separated concerns (file I/O, encryption logic, output handling)
- **Build:** CMake ≥ 3.14

---

## Architecture

```
VaultX/
├── include/
│   ├── FileManager.h       # File I/O interface
│   ├── EncryptionEngine.h  # Encryption/decryption interface
│   ├── OutputHandler.h     # Logging & progress reporting
│   └── VaultX.h            # Top-level orchestrator
├── src/
│   ├── FileManager.cpp
│   ├── EncryptionEngine.cpp
│   ├── OutputHandler.cpp
│   ├── VaultX.cpp
│   └── main.cpp            # CLI entry point
└── CMakeLists.txt
```

### Class Responsibilities

| Class | Role |
|---|---|
| `FileManager` | Static utility for reading/writing binary files with error validation |
| `EncryptionEngine` | Stateless cipher engine supporting XOR and Caesar byte-shift algorithms |
| `OutputHandler` | Structured logging, progress bars, and result summaries |
| `VaultX` | Orchestrator — composes the above classes to process a full file |

---

## Build

```bash
mkdir build && cd build
cmake ..
make
```

The `vaultx` binary will be in `build/`.

---

## Usage

```
./vaultx <mode> <key> <input_file> [output_file] [--algo <xor|caesar>]
```

### Encrypt a file
```bash
./vaultx encrypt mySecretKey report.pdf
# → writes report.pdf.vx
```

### Decrypt a file
```bash
./vaultx decrypt mySecretKey report.pdf.vx report_restored.pdf
```

### Use Caesar byte-shift cipher
```bash
./vaultx encrypt myKey data.txt --algo caesar
```

---

## Design Highlights

- **Modular architecture** — encryption logic, file management, and output handling are fully separated into independent classes, making each component independently testable and extensible.
- **OOP principles** — encapsulation of cipher state in `EncryptionEngine`; static utility pattern in `FileManager` and `OutputHandler`; composition in `VaultX`.
- **Robust error handling** — `std::invalid_argument` for bad inputs, `std::runtime_error` for I/O failures; all errors are caught and reported via `OutputHandler` before rethrowing.
- **Algorithm extensibility** — adding a new cipher requires only a new enum value and private method in `EncryptionEngine`, with no changes to `VaultX` or `main`.

---

## Supported Algorithms

| Flag | Algorithm | How it works |
|---|---|---|
| `--algo xor` (default) | XOR Cipher | Each byte XOR'd with the cyclic key bytes |
| `--algo caesar` | Caesar Byte-Shift | Each byte shifted by a value derived from the key |
