#include "BaseEntity.h"

namespace AgroResQ
{
    namespace Core
    {
        BaseEntity::BaseEntity() : id(0) {}

        BaseEntity::~BaseEntity() = default;

        void BaseEntity::setId(int id)
        {
            this->id = id;
        }

        int BaseEntity::getId() const
        {
            return id;
        }
        
       
    }
}