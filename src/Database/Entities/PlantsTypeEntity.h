#ifndef PLANTSTYPEENTITY_H
#define PLANTSTYPEENTITY_H

#include <OStad.h>

class PlantsTypeEntity : public Entity {
public:
    static const String COLUMN_TYPE;
    static const String COLUMN_CONDITION_ID;
    static const String COLUMN_DESCRIPTION;
    

    String type;
    int condition_id;
    String description;
    

    PlantsTypeEntity()  : Entity(){}

    PlantsTypeEntity(int id, String _type, int _condition_id, String _description) : Entity() {
        this->id = id;
        type = _type;
        condition_id = _condition_id;
        description = _description;
        

        addColumn(COLUMN_TYPE, String(type), "String");
        addColumn(COLUMN_CONDITION_ID, String(condition_id), "int");
        addColumn(COLUMN_DESCRIPTION, String(description), "String");
        
    }

    PlantsTypeEntity(String _type, int _condition_id, String _description) : 
        PlantsTypeEntity(0, _type, _condition_id, _description)  {}

    static PlantsTypeEntity fromEntity(Entity entity)
    {
        PlantsTypeEntity plantstypeentity = PlantsTypeEntity();
        plantstypeentity.fromString(entity.toString());
        return plantstypeentity;
    }

    // Setters and Getters for each field
};

const String PlantsTypeEntity::COLUMN_TYPE = "type";
const String PlantsTypeEntity::COLUMN_CONDITION_ID = "condition_id";
const String PlantsTypeEntity::COLUMN_DESCRIPTION = "description";


#endif // PLANTSTYPEENTITY_H