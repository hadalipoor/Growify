#ifndef SYSTEMCONDITIONCONTROLLER_H
#define SYSTEMCONDITIONCONTROLLER_H

#include "ISystemConditionController.h"
#include "../AppContext.h"
#include "../Config/DefaultGrowifyConfigs.h"
#include "../Config/GrowifyConfigKeys.h"
#include "../Database/Controllers/PlantsController.h"
#include "../Database/Controllers/PlantsTypeController.h"
#include "../Database/Controllers/ConditionController.h"
#include "../Database/Controllers/TemperatureConditionController.h"
#include "../Database/Controllers/HumidityConditionController.h"
#include "../Database/Controllers/SoilMoistureConditionController.h"
#include "../Database/Controllers/LightConditionController.h"

class SystemConditionController : public ISystemConditionController
{
private:
    AppContext* context;
    int check_delay;
    PlantsController* plantsController;
    PlantsTypeController* plantsTypeController;
    ConditionController* conditionController;
    TemperatureConditionController* temperatureConditionController;
    HumidityConditionController* humidityConditionController;
    SoilMoistureConditionController* soilMoistureConditionController;
    LightConditionController* lightConditionController;

    void checkTemperature(TemperatureConditionEntity temperatureConditionEntity);
    void checkHumidity(HumidityConditionEntity humidityConditionEntity);
    void checkSoilMoisture(SoilMoistureConditionEntity soilMoistureConditionEntity);
    void checkLight(LightConditionEntity lightConditionEntity);

public:
    SystemConditionController(AppContext* context);
    
    void initialize() override;
    void update() override;
};

SystemConditionController::SystemConditionController(AppContext* context)
    : context(context) {}

void SystemConditionController::initialize() {
    check_delay = context->getGrowifyConfig()->get(GrowifyConfigKey::CHECK_CONDITIONS_DELAY).toInt();

    plantsController = new PlantsController(context, StorageType::SPIFFS_TYPE);
    plantsTypeController = new PlantsTypeController(context, StorageType::SPIFFS_TYPE);
    conditionController = new ConditionController(context, StorageType::SPIFFS_TYPE);
    temperatureConditionController = new TemperatureConditionController(context, StorageType::SPIFFS_TYPE);
    humidityConditionController = new HumidityConditionController(context, StorageType::SPIFFS_TYPE);
    soilMoistureConditionController = new SoilMoistureConditionController(context, StorageType::SPIFFS_TYPE);
    lightConditionController = new LightConditionController(context, StorageType::SPIFFS_TYPE);
}

void SystemConditionController::update() {
    std::vector<PlantsEntity> activePlants = plantsController->Get(PlantsEntity::COLUMN_ACTIVE+"=1");
    for (auto& plant: activePlants)
    {
        int condition_id;
        if (plant.GetValue(PlantsEntity::COLUMN_CONDITION_ID).length() == 0)
        {
            int plant_type_id = plant.GetValue(PlantsEntity::COLUMN_PLANTS_TYPE_ID).toInt();
            PlantsTypeEntity plantType = plantsTypeController->GetById(plant_type_id);
            condition_id = plantType.GetValue(PlantsTypeEntity::COLUMN_CONDITION_ID).toInt();
        }
        else
        {
            condition_id = plant.GetValue(PlantsEntity::COLUMN_CONDITION_ID).toInt();
        }
        ConditionEntity conditionEntity = conditionController->GetById(condition_id);

        if (conditionEntity.GetValue(ConditionEntity::COLUMN_TEMPERATURE_CONDITION_ID).length() > 0)
        {
            TemperatureConditionEntity temperatureConditionEntity = temperatureConditionController->GetById(conditionEntity.GetValue(ConditionEntity::COLUMN_TEMPERATURE_CONDITION_ID).toInt());
            HumidityConditionEntity humidityConditionEntity = humidityConditionController->GetById(conditionEntity.GetValue(ConditionEntity::COLUMN_HUMIDITY_CONDITION_ID).toInt());
            SoilMoistureConditionEntity soilMoistureConditionEntity = soilMoistureConditionController->GetById(conditionEntity.GetValue(ConditionEntity::COLUMN_SOILMOISTUREC_CONDITION_ID).toInt());
            LightConditionEntity lightConditionEntity = lightConditionController->GetById(conditionEntity.GetValue(ConditionEntity::COLUMN_LIGHT_CONDITION_ID).toInt());
            
            checkTemperature(temperatureConditionEntity);
            checkHumidity(humidityConditionEntity);
            checkSoilMoisture(soilMoistureConditionEntity);
            checkLight(lightConditionEntity);
        }
    }
}

void SystemConditionController::checkTemperature(TemperatureConditionEntity temperatureConditionEntity)
{
    int module_id = temperatureConditionEntity.GetValue(TemperatureConditionEntity::COLUMN_MODULE_ID).toInt();
    DHTSensor* dhtSensor = context->getDeviceManager()->getDHTSensorById(module_id);
    float dhtSensorTemp = dhtSensor->getTemperatureC();
    Relay* coolerRelay;
    Relay* heatRelay;
    if(temperatureConditionEntity.GetValue(TemperatureConditionEntity::COLUMN_COOLER_RELAY_ID) != "")
    {
        coolerRelay = context->getDeviceManager()->getRelayById(temperatureConditionEntity.GetValue(TemperatureConditionEntity::COLUMN_COOLER_RELAY_ID).toInt());
    }
    if (temperatureConditionEntity.GetValue(TemperatureConditionEntity::COLUMN_HEATER_RELAY_ID) != "")
    {
        heatRelay = context->getDeviceManager()->getRelayById(temperatureConditionEntity.GetValue(TemperatureConditionEntity::COLUMN_HEATER_RELAY_ID).toInt());
    }
    
    if (dhtSensorTemp > temperatureConditionEntity.GetValue(TemperatureConditionEntity::COLUMN_MAX_TEMPERATURE).toInt())
    {
        if(heatRelay != nullptr)
            heatRelay->turnOff();
        if(coolerRelay!= nullptr)
            coolerRelay->turnOn();
    }
    if (dhtSensorTemp < temperatureConditionEntity.GetValue(TemperatureConditionEntity::COLUMN_MIN_TEMPERATURE).toInt())
    {
        if(heatRelay != nullptr)
            coolerRelay->turnOff();
        if(coolerRelay!= nullptr)
            heatRelay->turnOn();
    }
    else
    {
        if(heatRelay != nullptr)
            heatRelay->turnOff();
        if(coolerRelay!= nullptr)
            coolerRelay->turnOff();
    }    
}

void SystemConditionController::checkHumidity(HumidityConditionEntity humidityConditionEntity)
{
    int module_id = humidityConditionEntity.GetValue(HumidityConditionEntity::COLUMN_MODULE_ID).toInt();
    DHTSensor* dhtSensor = context->getDeviceManager()->getDHTSensorById(module_id);
    float dhtSensorHumidity = dhtSensor->getHumidity();
    Relay* dryerRelay;
    Relay* humidifierRelay;
    if(humidityConditionEntity.GetValue(HumidityConditionEntity::COLUMN_DRYING_RELAY_ID) != "")
    {
        dryerRelay = context->getDeviceManager()->getRelayById(humidityConditionEntity.GetValue(HumidityConditionEntity::COLUMN_DRYING_RELAY_ID).toInt());
    }
    if(humidityConditionEntity.GetValue(HumidityConditionEntity::COLUMN_HUMIDIFYING_RELAY_ID))
    {
        humidifierRelay = context->getDeviceManager()->getRelayById(humidityConditionEntity.GetValue(HumidityConditionEntity::COLUMN_HUMIDIFYING_RELAY_ID).toInt());
    }

    if (dhtSensorHumidity > humidityConditionEntity.GetValue(HumidityConditionEntity::COLUMN_MAX_HUMIDITY).toInt())
    {
        if(humidifierRelay != nullptr)
            humidifierRelay->turnOff();
        if(dryerRelay != nullptr)
            dryerRelay->turnOn();
    }
    if (dhtSensorHumidity < humidityConditionEntity.GetValue(HumidityConditionEntity::COLUMN_MIN_HUMIDITY).toInt())
    {
        if(dryerRelay != nullptr)
            dryerRelay->turnOff();
        if(humidifierRelay != nullptr)
            humidifierRelay->turnOn();
    }
    else
    {
        if(dryerRelay != nullptr)
            dryerRelay->turnOff();
        if(humidifierRelay != nullptr)
            humidifierRelay->turnOff();
    }    
}

void SystemConditionController::checkSoilMoisture(SoilMoistureConditionEntity soilMoistureConditionEntity)
{
    int module_id = soilMoistureConditionEntity.GetValue(SoilMoistureConditionEntity::COLUMN_MODULE_ID).toInt();
    DHTSensor* dhtSensor = context->getDeviceManager()->getDHTSensorById(module_id);
    float dhtSensorHumidity = dhtSensor->getHumidity();
    Relay* pumpRelay;
    Relay* warningRelay;
    if(soilMoistureConditionEntity.GetValue(SoilMoistureConditionEntity::COLUMN_PUMP_RELAY_ID) != "")
    {
        pumpRelay = context->getDeviceManager()->getRelayById(soilMoistureConditionEntity.GetValue(SoilMoistureConditionEntity::COLUMN_PUMP_RELAY_ID).toInt());
    }
    if(soilMoistureConditionEntity.GetValue(SoilMoistureConditionEntity::COLUMN_SOIL_MOISTURE_WARNING_RELAY_ID))
    {
        warningRelay = context->getDeviceManager()->getRelayById(soilMoistureConditionEntity.GetValue(SoilMoistureConditionEntity::COLUMN_SOIL_MOISTURE_WARNING_RELAY_ID).toInt());
    }

    if (dhtSensorHumidity > soilMoistureConditionEntity.GetValue(SoilMoistureConditionEntity::COLUMN_MAX_SOIL_MOISTURE).toInt())
    {
        if(pumpRelay != nullptr)
            pumpRelay->turnOff();
        if(warningRelay != nullptr)
            warningRelay->turnOn();
    }
    if (dhtSensorHumidity < soilMoistureConditionEntity.GetValue(SoilMoistureConditionEntity::COLUMN_MIN_SOIL_MOISTURE).toInt())
    {
        if(warningRelay != nullptr)
            warningRelay->turnOff();
        if(pumpRelay != nullptr)
            pumpRelay->turnOn();
    }
    else
    {
        if(pumpRelay != nullptr)
            pumpRelay->turnOff();
        if(warningRelay != nullptr)
            warningRelay->turnOff();
    }    
}

void SystemConditionController::checkLight(LightConditionEntity lightConditionEntity)
{
    EBPDateTime startDate = EBPDateTime();
    EBPDateTime endDate = EBPDateTime();

    if(startDate.isDateTimeStringValid(lightConditionEntity.GetValue(LightConditionEntity::COLUMN_START_TIME)))
        startDate = EBPDateTime(lightConditionEntity.GetValue(LightConditionEntity::COLUMN_START_TIME));
    else
        return;
    if(endDate.isDateTimeStringValid(lightConditionEntity.GetValue(LightConditionEntity::COLUMN_END_TIME)))
        endDate = EBPDateTime(lightConditionEntity.GetValue(LightConditionEntity::COLUMN_END_TIME));
    else
        return;

    Relay* lightRelay;
    if(lightConditionEntity.GetValue(LightConditionEntity::COLUMN_LED_RELAY_ID) != "")
    {
        lightRelay = context->getDeviceManager()->getRelayById(lightConditionEntity.GetValue(LightConditionEntity::COLUMN_LED_RELAY_ID).toInt());
    }
    else
    {
        return;
    }

    EBPDateTime nowDateTime = context->systemContext->getClock()->now();
    if (nowDateTime.isBetweenTwoDateTime(startDate, endDate))
    {
        lightRelay->turnOn();
    }
    else
    {
        lightRelay->turnOff();
    }
    
}


#endif