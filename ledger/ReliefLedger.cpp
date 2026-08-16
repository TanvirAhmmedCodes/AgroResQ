#include "ReliefLedger.h"
#include "../core/FileManager.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <cstring>
#include <cstdint>

namespace AgroResQ
{
namespace Ledger
{

static const uint32_t HASH_SEED = 0x9E3779B1;

// ===== Simple SHA-256 style hash (32-bit FNV-1a variant) =====
std::string ReliefLedger::calculateHash(const std::string& data)
{
    uint32_t hash = 0x811C9DC5; // FNV offset basis
    for (char c : data)
    {
        hash ^= static_cast<uint32_t>(static_cast<unsigned char>(c));
        hash *= 0x01000193; // FNV prime
        hash ^= (hash >> 16);
        hash ^= HASH_SEED;
    }
    std::stringstream ss;
    ss << std::hex << std::setw(8) << std::setfill('0') << hash;
    return ss.str();
}

std::string ReliefLedger::generateTimestamp()
{
    time_t now = time(nullptr);
    char buf[80];
    strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", localtime(&now));
    return std::string(buf);
}

std::string ReliefLedger::serializeEntry(const ReliefEntry& entry)
{
    std::stringstream ss;
    ss << entry.id << ","
       << entry.victimName << ","
       << entry.resourceType << ","
       << entry.quantity << ","
       << entry.timestamp << ","
       << entry.previousHash << ","
       << entry.currentHash << ","
       << (entry.isValid ? "1" : "0");
    return ss.str();
}

ReliefEntry ReliefLedger::deserializeEntry(const std::string& line)
{
    std::stringstream ss(line);
    ReliefEntry entry;
    std::string idStr;
    std::string quantityStr;
    std::string validStr;

    std::getline(ss, idStr, ',');
    entry.id = std::stoi(idStr);

    std::getline(ss, entry.victimName, ',');
    std::getline(ss, entry.resourceType, ',');
    std::getline(ss, quantityStr, ',');
    entry.quantity = std::stoi(quantityStr);
    std::getline(ss, entry.timestamp, ',');
    std::getline(ss, entry.previousHash, ',');
    std::getline(ss, entry.currentHash, ',');
    std::getline(ss, validStr);
    entry.isValid = (validStr == "1");

    return entry;
}
// ================================================================

ReliefLedger::ReliefLedger()
{
    filePath = "database/relief_ledger.txt";
    loadFromFile();
}

ReliefLedger::ReliefLedger(const std::string& path) : filePath(path)
{
    loadFromFile();
}

bool ReliefLedger::addEntry(const std::string& victimName, const std::string& resourceType, int quantity)
{
    if (victimName.empty() || resourceType.empty() || quantity <= 0) return false;

    ReliefEntry entry;
    entry.id = entries.size() + 1;
    entry.victimName = victimName;
    entry.resourceType = resourceType;
    entry.quantity = quantity;
    entry.timestamp = generateTimestamp();
    entry.previousHash = lastHash.empty() ? "GENESIS" : lastHash;

    std::string data = std::to_string(entry.id) + "|" +
                       entry.victimName + "|" +
                       entry.resourceType + "|" +
                       std::to_string(entry.quantity) + "|" +
                       entry.timestamp + "|" +
                       entry.previousHash;
    entry.currentHash = calculateHash(data);
    entry.isValid = true;

    entries.push_back(entry);
    lastHash = entry.currentHash;

    return saveToFile();
}

bool ReliefLedger::verifyAllEntries()
{
    return verifyChainIntegrity();
}

bool ReliefLedger::verifyChainIntegrity()
{
    if (entries.empty()) return true;

    std::string expectedPrev = "GENESIS";
    for (size_t i = 0; i < entries.size(); ++i)
    {
        auto& entry = entries[i];
        if (entry.previousHash != expectedPrev) return false;
        std::string data = std::to_string(entry.id) + "|" +
                           entry.victimName + "|" +
                           entry.resourceType + "|" +
                           std::to_string(entry.quantity) + "|" +
                           entry.timestamp + "|" +
                           entry.previousHash;
        std::string computedHash = calculateHash(data);
        if (computedHash != entry.currentHash) return false;
        expectedPrev = entry.currentHash;
    }
    return true;
}

std::vector<ReliefEntry> ReliefLedger::getAllEntries()
{
    return entries;
}

std::vector<ReliefEntry> ReliefLedger::getEntriesByVictim(const std::string& victimName)
{
    std::vector<ReliefEntry> result;
    for (const auto& entry : entries)
    {
        if (entry.victimName == victimName)
            result.push_back(entry);
    }
    return result;
}

bool ReliefLedger::isLedgerTampered()
{
    return !verifyChainIntegrity();
}

void ReliefLedger::displayLedger()
{
    std::cout << "\n========== RELIEF LEDGER (HASH CHAIN) ==========\n";
    std::cout << "Status: " << (isLedgerTampered() ? "⚠️ TAMPERED" : "✅ VERIFIED") << "\n";
    std::cout << "Total Entries: " << entries.size() << "\n";
    std::cout << "=================================================\n";

    for (const auto& entry : entries)
    {
        std::cout << "\nID        : " << entry.id << "\n";
        std::cout << "Victim    : " << entry.victimName << "\n";
        std::cout << "Resource  : " << entry.resourceType << " x " << entry.quantity << "\n";
        std::cout << "Time      : " << entry.timestamp << "\n";
        std::cout << "Prev Hash : " << entry.previousHash << "\n";
        std::cout << "Curr Hash : " << entry.currentHash << "\n";
        std::cout << "Valid     : " << (entry.isValid ? "Yes" : "No") << "\n";
        std::cout << "-------------------------------------------------\n";
    }
}

bool ReliefLedger::saveToFile()
{
    Core::FileManager fm;
    std::string data;
    for (const auto& entry : entries)
    {
        data += serializeEntry(entry) + "\n";
    }
    return fm.writeFile(filePath, data);
}

bool ReliefLedger::loadFromFile()
{
    Core::FileManager fm;
    if (!fm.fileExists(filePath))
    {
        fm.createFile(filePath);
        return true;
    }

    entries.clear();
    auto lines = fm.readLines(filePath);
    for (const auto& line : lines)
    {
        if (!line.empty())
        {
            entries.push_back(deserializeEntry(line));
        }
    }

    if (!entries.empty())
    {
        lastHash = entries.back().currentHash;
    }

    return true;
}

void ReliefLedger::clearLedger()
{
    entries.clear();
    lastHash = "";
    saveToFile();
}

}
}