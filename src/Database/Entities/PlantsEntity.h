#ifndef PLANTSENTITY_H
#define PLANTSENTITY_H

#include <OStad.h>

class PlantsEntity : public Entity {
public:
    static const String COLUMN_PLANTS_TYPE_ID;
    static const String COLUMN_NAME;
    static const String COLUMN_ACTIVE;
    static const String COLUMN_CONDITION_ID;
    

    int plants_type_id;
    String name;
    int active;
    int condition_id;
    

    PlantsEntity()  : Entity(){}

    PlantsEntity(int id, int _plants_type_id, String _name, int _active, int _condition_id) : Entity() {
        this->id = id;
        plants_type_id = _plants_type_id;
        name = _name;
        active = _active;
        condition_id = _condition_id;
        

        addColumn(COLUMN_PLANTS_TYPE_ID, String(plants_type_id), "int");
        addColumn(COLUMN_NAME, String(name), "String");
        addColumn(COLUMN_ACTIVE, String(active), "int");
        addColumn(COLUMN_CONDITION_ID, String(condition_id), "int");
        
    }

    PlantsEntity(int _plants_type_id, String _name, int _active, int _condition_id) : 
        PlantsEntity(0, _plants_type_id, _name, _active, _condition_id)  {}

    static PlantsEntity fromEntity(Entity entity)
    {
        PlantsEntity plantsentity = PlantsEntity();
        plantsentity.fromString(entity.toString());
        return plantsentity;
    }

    // Setters and Getters for each field
};

const String PlantsEntity::COLUMN_PLANTS_TYPE_ID = "plants_type_id";
const String PlantsEntity::COLUMN_NAME = "name";
const String PlantsEntity::COLUMN_ACTIVE = "active";
const String PlantsEntity::COLUMN_CONDITION_ID = "condition_id";


#endif // PLANTSENTITY_H