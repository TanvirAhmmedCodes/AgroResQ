#include "Validator.h"
#include <cctype>

namespace AgroResQ
{
    namespace Core
    {
        Validator::Validator() = default;

        bool Validator::isEmpty(const std::string& text) const
        {
            return text.empty();
        }

        bool Validator::isNumber(const std::string& text) const
        {
            if (text.empty()) return false;
            for (char ch : text)
            {
                if (!std::isdigit(static_cast<unsigned char>(ch)))
                    return false;
            }
            return true;
        }

        bool Validator::isPositive(int value) const
        {
            return value > 0;
        }

        bool Validator::isValidSeverity(int severity) const
        {
            return severity >= 1 && severity <= 10;
        }

        bool Validator::isValidName(const std::string& name) const
        {
            return !isEmpty(name);
        }

        bool Validator::isValidLocation(const std::string& location) const
        {
            return !isEmpty(location);
        }

        bool Validator::isValidDate(const std::string& date) const
        {
            if (date.length() != 10) return false;
            return date[2] == '-' && date[5] == '-';
        }
    }
}