#pragma once

#include <string>

namespace AgroResQ
{
namespace Core
{

class Validator
{
public:
    Validator();

    bool isEmpty(const std::string& text) const;

    bool isNumber(const std::string& text) const;

    bool isPositive(int value) const;

    bool isValidSeverity(int severity) const;

    bool isValidName(const std::string& name) const;

    bool isValidLocation(const std::string& location) const;

    bool isValidDate(const std::string& date) const;
};

}
}