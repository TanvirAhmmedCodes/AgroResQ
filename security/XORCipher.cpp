#include "XORCipher.h"
#include <fstream>
#include <stdexcept>
#include <cstring>
#include <iostream>

namespace AgroResQ
{
namespace Security
{

// ===== Simple Pseudo-Random Key Generator =====
std::vector<uint8_t> XORCipher::generateKeyStream(size_t length) const
{
    std::vector<uint8_t> stream(length);
    size_t keyLen = key.length();
    
    for (size_t i = 0; i < length; ++i)
    {
        // Generate deterministic pseudo-random bytes based on key
        uint8_t byte = static_cast<uint8_t>(key[i % keyLen]);
        
        // Mix with position to avoid simple patterns
        byte ^= static_cast<uint8_t>((i * 0x9E3779B9) >> 16);
        byte ^= static_cast<uint8_t>((i * 0x85EBCA6B) >> 8);
        
        stream[i] = byte;
    }
    
    return stream;
}

// ===== Constructor =====
XORCipher::XORCipher(const std::string& masterKey) : key(masterKey) {}

// ===== Set Key =====
void XORCipher::setKey(const std::string& newKey)
{
    if (newKey.empty())
        throw std::runtime_error("Encryption key cannot be empty");
    key = newKey;
}

// ===== Get Key =====
std::string XORCipher::getKey() const
{
    return key;
}

// ===== Encrypt String =====
std::string XORCipher::encrypt(const std::string& plaintext) const
{
    if (plaintext.empty())
        return "";

    auto keyStream = generateKeyStream(plaintext.length());
    std::string ciphertext(plaintext.length(), '\0');

    for (size_t i = 0; i < plaintext.length(); ++i)
    {
        ciphertext[i] = plaintext[i] ^ keyStream[i];
    }

    return ciphertext;
}

// ===== Decrypt String =====
std::string XORCipher::decrypt(const std::string& ciphertext) const
{
    // XOR is symmetric: same function works for both
    return encrypt(ciphertext);
}

// ===== Encrypt Binary Data =====
std::vector<uint8_t> XORCipher::encrypt(const std::vector<uint8_t>& data) const
{
    if (data.empty())
        return {};

    auto keyStream = generateKeyStream(data.size());
    std::vector<uint8_t> encrypted(data.size());

    for (size_t i = 0; i < data.size(); ++i)
    {
        encrypted[i] = data[i] ^ keyStream[i];
    }

    return encrypted;
}

// ===== Decrypt Binary Data =====
std::vector<uint8_t> XORCipher::decrypt(const std::vector<uint8_t>& data) const
{
    // XOR is symmetric
    return encrypt(data);
}

// ===== Encrypt File =====
bool XORCipher::encryptFile(const std::string& inputPath, const std::string& outputPath) const
{
    std::ifstream input(inputPath, std::ios::binary);
    if (!input.is_open())
    {
        std::cerr << "[Encryption] Failed to open input file: " << inputPath << "\n";
        return false;
    }

    std::ofstream output(outputPath, std::ios::binary);
    if (!output.is_open())
    {
        std::cerr << "[Encryption] Failed to open output file: " << outputPath << "\n";
        return false;
    }

    // Read entire file
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(input)),
                               std::istreambuf_iterator<char>());

    // Encrypt
    auto encrypted = encrypt(data);

    // Write encrypted data
    output.write(reinterpret_cast<const char*>(encrypted.data()), encrypted.size());

    return true;
}

// ===== Decrypt File =====
bool XORCipher::decryptFile(const std::string& inputPath, const std::string& outputPath) const
{
    std::ifstream input(inputPath, std::ios::binary);
    if (!input.is_open())
    {
        std::cerr << "[Encryption] Failed to open input file: " << inputPath << "\n";
        return false;
    }

    std::ofstream output(outputPath, std::ios::binary);
    if (!output.is_open())
    {
        std::cerr << "[Encryption] Failed to open output file: " << outputPath << "\n";
        return false;
    }

    // Read entire file
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(input)),
                               std::istreambuf_iterator<char>());

    // Decrypt (same as encrypt for XOR)
    auto decrypted = decrypt(data);

    // Write decrypted data
    output.write(reinterpret_cast<const char*>(decrypted.data()), decrypted.size());

    return true;
}

}
}