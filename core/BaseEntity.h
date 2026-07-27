#pragma once
#include <string>

namespace AgroResQ
{
    namespace Core
    {
        class BaseEntity
        {
        protected:
            int id;

        public:
            BaseEntity();
            virtual ~BaseEntity();

            void setId(int id);
            int getId() const;
            
            
            virtual std::string toString() const = 0;  // Pure virtual
        };
    }
}