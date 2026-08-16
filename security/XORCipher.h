#pragma once
#include <string>
#include <vector>
#include <cstdint>

namespace AgroResQ
{
namespace Security
{

class XORCipher
{
private:
    std::string key;

    // Generate a pseudo-random key stream from the master key
    std::vector<uint8_t> generateKeyStream(size_t length) const;

public:
    // Constructor with a master key (default: "AgroResQ2025")
    explicit XORCipher(const std::string& masterKey = "AgroResQ2025");

    // Encrypt a string
    std::string encrypt(const std::string& plaintext) const;

    // Decrypt a string
    std::string decrypt(const std::string& ciphertext) const;

    // Encrypt binary data
    std::vector<uint8_t> encrypt(const std::vector<uint8_t>& data) const;

    // Decrypt binary data
    std::vector<uint8_t> decrypt(const std::vector<uint8_t>& data) const;

    // Change the encryption key
    void setKey(const std::string& newKey);

    // Get the current key (for debugging only)
    std::string getKey() const;

    // Simple file encryption helper
    bool encryptFile(const std::string& inputPath, const std::string& outputPath) const;

    // Simple file decryption helper
    bool decryptFile(const std::string& inputPath, const std::string& outputPath) const;
};

}
}