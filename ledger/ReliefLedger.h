#pragma once
#include <string>
#include <vector>
#include <ctime>

namespace AgroResQ
{
namespace Ledger
{

struct ReliefEntry
{
    int id;
    std::string victimName;
    std::string resourceType;
    int quantity;
    std::string timestamp;
    std::string previousHash;
    std::string currentHash;
    bool isValid;
};

class ReliefLedger
{
private:
    std::vector<ReliefEntry> entries;
    std::string lastHash;
    std::string filePath;

    std::string calculateHash(const std::string& data);
    std::string generateTimestamp();
    std::string serializeEntry(const ReliefEntry& entry);
    ReliefEntry deserializeEntry(const std::string& line);
    bool verifyChainIntegrity();

public:
    ReliefLedger();
    explicit ReliefLedger(const std::string& path);

    bool addEntry(const std::string& victimName, const std::string& resourceType, int quantity);
    bool verifyAllEntries();
    std::vector<ReliefEntry> getAllEntries();
    std::vector<ReliefEntry> getEntriesByVictim(const std::string& victimName);
    bool isLedgerTampered();
    void displayLedger();
    bool saveToFile();
    bool loadFromFile();
    void clearLedger();
};

}
}