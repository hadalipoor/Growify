#ifndef SOILMOISTURECONDITIONENTITY_H
#define SOILMOISTURECONDITIONENTITY_H

#include <OStad.h>

class SoilMoistureConditionEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MODULE_ID;
    static const String COLUMN_MIN_SOIL_MOISTURE;
    static const String COLUMN_MAX_SOIL_MOISTURE;
    static const String COLUMN_PUMP_RELAY_ID;
    static const String COLUMN_SOIL_MOISTURE_WARNING_RELAY_ID;
    static const String COLUMN_DESCRIPTION;
    

    String name;
    int module_id;
    int min_soil_moisture;
    int max_soil_moisture;
    String pump_relay_id;
    String soil_moisture_warning_relay_id;
    String description;
    

    SoilMoistureConditionEntity()  : Entity(){}

    SoilMoistureConditionEntity(int id, String _name, int _module_id, int _min_soil_moisture, int _max_soil_moisture, String _pump_relay_id, String _soil_moisture_warning_relay_id, String _description) : Entity() {
        this->id = id;
        name = _name;
        module_id = _module_id;
        min_soil_moisture = _min_soil_moisture;
        max_soil_moisture = _max_soil_moisture;
        pump_relay_id = _pump_relay_id;
        soil_moisture_warning_relay_id = _soil_moisture_warning_relay_id;
        description = _description;
        

        addColumn(COLUMN_NAME, String(name), "String");
        addColumn(COLUMN_MODULE_ID, String(module_id), "int");
        addColumn(COLUMN_MIN_SOIL_MOISTURE, String(min_soil_moisture), "int");
        addColumn(COLUMN_MAX_SOIL_MOISTURE, String(max_soil_moisture), "int");
        addColumn(COLUMN_PUMP_RELAY_ID, String(pump_relay_id), "String");
        addColumn(COLUMN_SOIL_MOISTURE_WARNING_RELAY_ID, String(soil_moisture_warning_relay_id), "String");
        addColumn(COLUMN_DESCRIPTION, String(description), "String");
        
    }

    SoilMoistureConditionEntity(String _name, int _module_id, int _min_soil_moisture, int _max_soil_moisture, String _pump_relay_id, String _soil_moisture_warning_relay_id, String _description) : 
        SoilMoistureConditionEntity(0, _name, _module_id, _min_soil_moisture, _max_soil_moisture, _pump_relay_id, _soil_moisture_warning_relay_id, _description)  {}

    static SoilMoistureConditionEntity fromEntity(Entity entity)
    {
        SoilMoistureConditionEntity soilmoistureconditionentity = SoilMoistureConditionEntity();
        soilmoistureconditionentity.fromString(entity.toString());
        return soilmoistureconditionentity;
    }

    // Setters and Getters for each field
};

const String SoilMoistureConditionEntity::COLUMN_NAME = "name";
const String SoilMoistureConditionEntity::COLUMN_MODULE_ID = "module_id";
const String SoilMoistureConditionEntity::COLUMN_MIN_SOIL_MOISTURE = "min_soil_moisture";
const String SoilMoistureConditionEntity::COLUMN_MAX_SOIL_MOISTURE = "max_soil_moisture";
const String SoilMoistureConditionEntity::COLUMN_PUMP_RELAY_ID = "pump_relay_id";
const String SoilMoistureConditionEntity::COLUMN_SOIL_MOISTURE_WARNING_RELAY_ID = "soil_moisture_warning_relay_id";
const String SoilMoistureConditionEntity::COLUMN_DESCRIPTION = "description";


#endif // SOILMOISTURECONDITIONENTITY_H