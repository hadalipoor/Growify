#ifndef HUMIDITYCONDITIONENTITY_H
#define HUMIDITYCONDITIONENTITY_H

#include <OStad.h>

class HumidityConditionEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MODULE_ID;
    static const String COLUMN_MIN_HUMIDITY;
    static const String COLUMN_MAX_HUMIDITY;
    static const String COLUMN_DRYING_RELAY_ID;
    static const String COLUMN_HUMIDIFYING_RELAY_ID;
    static const String COLUMN_DESCRIPTION;
    

    String name;
    int module_id;
    int min_humidity;
    int max_humidity;
    String drying_relay_id;
    String humidifying_relay_id;
    String description;
    

    HumidityConditionEntity()  : Entity(){}

    HumidityConditionEntity(int id, String _name, int _module_id, int _min_humidity, int _max_humidity, String _drying_relay_id, String _humidifying_relay_id, String _description) : Entity() {
        this->id = id;
        name = _name;
        module_id = _module_id;
        min_humidity = _min_humidity;
        max_humidity = _max_humidity;
        drying_relay_id = _drying_relay_id;
        humidifying_relay_id = _humidifying_relay_id;
        description = _description;
        

        addColumn(COLUMN_NAME, String(name), "String");
        addColumn(COLUMN_MODULE_ID, String(module_id), "int");
        addColumn(COLUMN_MIN_HUMIDITY, String(min_humidity), "int");
        addColumn(COLUMN_MAX_HUMIDITY, String(max_humidity), "int");
        addColumn(COLUMN_DRYING_RELAY_ID, String(drying_relay_id), "String");
        addColumn(COLUMN_HUMIDIFYING_RELAY_ID, String(humidifying_relay_id), "String");
        addColumn(COLUMN_DESCRIPTION, String(description), "String");
        
    }

    HumidityConditionEntity(String _name, int _module_id, int _min_humidity, int _max_humidity, String _drying_relay_id, String _humidifying_relay_id, String _description) : 
        HumidityConditionEntity(0, _name, _module_id, _min_humidity, _max_humidity, _drying_relay_id, _humidifying_relay_id, _description)  {}

    static HumidityConditionEntity fromEntity(Entity entity)
    {
        HumidityConditionEntity humidityconditionentity = HumidityConditionEntity();
        humidityconditionentity.fromString(entity.toString());
        return humidityconditionentity;
    }

    // Setters and Getters for each field
};

const String HumidityConditionEntity::COLUMN_NAME = "name";
const String HumidityConditionEntity::COLUMN_MODULE_ID = "module_id";
const String HumidityConditionEntity::COLUMN_MIN_HUMIDITY = "min_humidity";
const String HumidityConditionEntity::COLUMN_MAX_HUMIDITY = "max_humidity";
const String HumidityConditionEntity::COLUMN_DRYING_RELAY_ID = "drying_relay_id";
const String HumidityConditionEntity::COLUMN_HUMIDIFYING_RELAY_ID = "humidifying_relay_id";
const String HumidityConditionEntity::COLUMN_DESCRIPTION = "description";


#endif // HUMIDITYCONDITIONENTITY_H