#pragma once
#include <unordered_map>
#include <string>
#include <vector>
#include <stdexcept>

namespace AgroResQ
{
namespace Database
{

template<typename KeyType, typename ValueType>
class IndexedDB
{
private:
    std::unordered_map<KeyType, ValueType> dataMap;
    std::string indexName;

public:
    explicit IndexedDB(const std::string& name = "default") : indexName(name) {}

    // Add or update a record
    void add(const KeyType& key, const ValueType& value)
    {
        dataMap[key] = value;
    }

    // Get a record by key
    bool get(const KeyType& key, ValueType& value) const
    {
        auto it = dataMap.find(key);
        if (it != dataMap.end())
        {
            value = it->second;
            return true;
        }
        return false;
    }

    // Remove a record by key
    bool remove(const KeyType& key)
    {
        return dataMap.erase(key) > 0;
    }

    // Check if a key exists
    bool exists(const KeyType& key) const
    {
        return dataMap.find(key) != dataMap.end();
    }

    // Get all values
    std::vector<ValueType> getAll() const
    {
        std::vector<ValueType> result;
        result.reserve(dataMap.size());
        for (const auto& pair : dataMap)
        {
            result.push_back(pair.second);
        }
        return result;
    }

    // Get all key-value pairs
    std::unordered_map<KeyType, ValueType> getAllPairs() const
    {
        return dataMap;
    }

    // Clear all records
    void clear()
    {
        dataMap.clear();
    }

    // Get size
    size_t size() const
    {
        return dataMap.size();
    }

    // Check if empty
    bool empty() const
    {
        return dataMap.empty();
    }
};

}
}