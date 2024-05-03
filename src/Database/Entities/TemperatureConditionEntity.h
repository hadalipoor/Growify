#ifndef TEMPERATURECONDITIONENTITY_H
#define TEMPERATURECONDITIONENTITY_H

#include <OStad.h>

class TemperatureConditionEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MODULE_ID;
    static const String COLUMN_MIN_TEMPERATURE;
    static const String COLUMN_MAX_TEMPERATURE;
    static const String COLUMN_COOLER_RELAY_ID;
    static const String COLUMN_HEATER_RELAY_ID;
    static const String COLUMN_DESCRIPTION;
    

    String name;
    int module_id;
    int min_temperature;
    int max_temperature;
    String cooler_relay_id;
    String hitter_relay_id;
    String description;
    

    TemperatureConditionEntity()  : Entity(){}

    TemperatureConditionEntity(int id, String _name, int _module_id, int _min_temperature, int _max_temperature, String _cooler_relay_id, String _hitter_relay_id, String _description) : Entity() {
        this->id = id;
        name = _name;
        module_id = _module_id;
        min_temperature = _min_temperature;
        max_temperature = _max_temperature;
        cooler_relay_id = _cooler_relay_id;
        hitter_relay_id = _hitter_relay_id;
        description = _description;
        

        addColumn(COLUMN_NAME, String(name), "String");
        addColumn(COLUMN_MODULE_ID, String(module_id), "int");
        addColumn(COLUMN_MIN_TEMPERATURE, String(min_temperature), "int");
        addColumn(COLUMN_MAX_TEMPERATURE, String(max_temperature), "int");
        addColumn(COLUMN_COOLER_RELAY_ID, String(cooler_relay_id), "String");
        addColumn(COLUMN_HEATER_RELAY_ID, String(hitter_relay_id), "String");
        addColumn(COLUMN_DESCRIPTION, String(description), "String");
        
    }

    TemperatureConditionEntity(String _name, int _module_id, int _min_temperature, int _max_temperature, String _cooler_relay_id, String _hitter_relay_id, String _description) : 
        TemperatureConditionEntity(0, _name, _module_id, _min_temperature, _max_temperature, _cooler_relay_id, _hitter_relay_id, _description)  {}

    static TemperatureConditionEntity fromEntity(Entity entity)
    {
        TemperatureConditionEntity temperatureconditionentity = TemperatureConditionEntity();
        temperatureconditionentity.fromString(entity.toString());
        return temperatureconditionentity;
    }

    // Setters and Getters for each field
};

const String TemperatureConditionEntity::COLUMN_NAME = "name";
const String TemperatureConditionEntity::COLUMN_MODULE_ID = "module_id";
const String TemperatureConditionEntity::COLUMN_MIN_TEMPERATURE = "min_temperature";
const String TemperatureConditionEntity::COLUMN_MAX_TEMPERATURE = "max_temperature";
const String TemperatureConditionEntity::COLUMN_COOLER_RELAY_ID = "cooler_relay_id";
const String TemperatureConditionEntity::COLUMN_HEATER_RELAY_ID = "hitter_relay_id";
const String TemperatureConditionEntity::COLUMN_DESCRIPTION = "description";


#endif // TEMPERATURECONDITIONENTITY_H