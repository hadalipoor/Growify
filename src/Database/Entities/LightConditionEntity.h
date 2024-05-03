#ifndef LIGHTCONDITIONENTITY_H
#define LIGHTCONDITIONENTITY_H

#include <OStad.h>

class LightConditionEntity : public Entity {
public:
    static const String COLUMN_NAME;
    static const String COLUMN_MODULE_ID;
    static const String COLUMN_START_TIME;
    static const String COLUMN_END_TIME;
    static const String COLUMN_LED_RELAY_ID;
    static const String COLUMN_DESCRIPTION;
    

    String name;
    int module_id;
    EBPDateTime start_time;
    EBPDateTime end_time;
    String led_relay_id;
    String description;
    

    LightConditionEntity()  : Entity(){}

    LightConditionEntity(int id, String _name, int _module_id, EBPDateTime _start_time, EBPDateTime _end_time, String _led_relay_id, String _description) : Entity() {
        this->id = id;
        name = _name;
        module_id = _module_id;
        start_time = _start_time;
        end_time = _end_time;
        led_relay_id = _led_relay_id;
        description = _description;
        

        addColumn(COLUMN_NAME, String(name), "String");
        addColumn(COLUMN_MODULE_ID, String(module_id), "int");
        addColumn(COLUMN_START_TIME, start_time.toDateTimeString(), "EBPDateTime");
        addColumn(COLUMN_END_TIME, end_time.toDateTimeString(), "EBPDateTime");
        addColumn(COLUMN_LED_RELAY_ID, String(led_relay_id), "String");
        addColumn(COLUMN_DESCRIPTION, String(description), "String");
        
    }

    LightConditionEntity(String _name, int _module_id, EBPDateTime _start_time, EBPDateTime _end_time, String _led_relay_id, String _description) : 
        LightConditionEntity(0, _name, _module_id, _start_time, _end_time, _led_relay_id, _description)  {}

    static LightConditionEntity fromEntity(Entity entity)
    {
        LightConditionEntity lightconditionentity = LightConditionEntity();
        lightconditionentity.fromString(entity.toString());
        return lightconditionentity;
    }

    // Setters and Getters for each field
};

const String LightConditionEntity::COLUMN_NAME = "name";
const String LightConditionEntity::COLUMN_MODULE_ID = "module_id";
const String LightConditionEntity::COLUMN_START_TIME = "start_time";
const String LightConditionEntity::COLUMN_END_TIME = "end_time";
const String LightConditionEntity::COLUMN_LED_RELAY_ID = "led_relay_id";
const String LightConditionEntity::COLUMN_DESCRIPTION = "description";


#endif // LIGHTCONDITIONENTITY_H