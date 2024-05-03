#ifndef CONDITIONENTITY_H
#define CONDITIONENTITY_H

#include <OStad.h>

class ConditionEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_TEMPERATURE_CONDITION_ID;
    static const String COLUMN_HUMIDITY_CONDITION_ID;
    static const String COLUMN_SOILMOISTUREC_CONDITION_ID;
    static const String COLUMN_LIGHT_CONDITION_ID;
    static const String COLUMN_DESCRIPTION;
    

    String name;
    int temperature_condition_id;
    int humidity_condition_id;
    int soilMoistureC_condition_id;
    int light_condition_id;
    String description;
    

    ConditionEntity()  : Entity(){}

    ConditionEntity(int id, String _name, int _temperature_condition_id, int _humidity_condition_id, int _soilMoistureC_condition_id, int _light_condition_id, String _description) : Entity() {
        this->id = id;
        name = _name;
        temperature_condition_id = _temperature_condition_id;
        humidity_condition_id = _humidity_condition_id;
        soilMoistureC_condition_id = _soilMoistureC_condition_id;
        light_condition_id = _light_condition_id;
        description = _description;
        

        addColumn(COLUMN_NAME, String(name), "String");
        addColumn(COLUMN_TEMPERATURE_CONDITION_ID, String(temperature_condition_id), "int");
        addColumn(COLUMN_HUMIDITY_CONDITION_ID, String(humidity_condition_id), "int");
        addColumn(COLUMN_SOILMOISTUREC_CONDITION_ID, String(soilMoistureC_condition_id), "int");
        addColumn(COLUMN_LIGHT_CONDITION_ID, String(light_condition_id), "int");
        addColumn(COLUMN_DESCRIPTION, String(description), "String");
        
    }

    ConditionEntity(String _name, int _temperature_condition_id, int _humidity_condition_id, int _soilMoistureC_condition_id, int _light_condition_id, String _description) : 
        ConditionEntity(0, _name, _temperature_condition_id, _humidity_condition_id, _soilMoistureC_condition_id, _light_condition_id, _description)  {}

    static ConditionEntity fromEntity(Entity entity)
    {
        ConditionEntity conditionentity = ConditionEntity();
        conditionentity.fromString(entity.toString());
        return conditionentity;
    }

    // Setters and Getters for each field
};

const String ConditionEntity::COLUMN_NAME = "name";
const String ConditionEntity::COLUMN_TEMPERATURE_CONDITION_ID = "temperature_condition_id";
const String ConditionEntity::COLUMN_HUMIDITY_CONDITION_ID = "humidity_condition_id";
const String ConditionEntity::COLUMN_SOILMOISTUREC_CONDITION_ID = "soilMoistureC_condition_id";
const String ConditionEntity::COLUMN_LIGHT_CONDITION_ID = "light_condition_id";
const String ConditionEntity::COLUMN_DESCRIPTION = "description";


#endif // CONDITIONENTITY_H