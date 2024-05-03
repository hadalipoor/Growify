
#ifndef DEVICEMANAGER_H
#define DEVICEMANAGER_H

#include "IDeviceManager.h"
#include "../AppContext.h"
#include <OStad.h>

struct RelayData
{
    int id;
    Relay* relay;
};

struct DHTSensorData
{
    int id;
    DHTSensor* dhtSensor;
};

struct SoilMoistureSensorData
{
    int id;
    SoilMoistureSensor* soilMoistureSensor;
};


class DeviceManager : public IDeviceManager
{
private:
    AppContext* appContext;

    ModulesController *modulesController;

    String _resetButtonStr = "resetButton";
    Button* _resetButton;

    String _mainLCDStr = "mainLCD";
    LCD16X2* _mainLCD;

    std::vector<RelayData> _Relays;

    std::vector<SoilMoistureSensorData> _soileMoistureSensors;

    std::vector<DHTSensorData> _TemperatureHumiditySensors;

public:
    DeviceManager(AppContext* context);

    void initialize() override;
    void update() override;
    Button* resetButton() override;
    LCD16X2* mainLCD() override;

    Relay* getRelayById(int id) override;
    SoilMoistureSensor* getSoilMoistureSensorById(int id) override;
    DHTSensor* getDHTSensorById(int id) override;

    Relay* getRelayByString(String name) override;
    SoilMoistureSensor* getSoilMoistureSensorByString(String name) override;
    DHTSensor* getDHTSensorByString(String name) override;
};

DeviceManager::DeviceManager(AppContext* context) : appContext(context) {

}

void DeviceManager::initialize()
{
    _resetButton = new Button(0, "resetButton", false, false, ButtonType::PIN);
    _mainLCD = new LCD16X2("mainLCD", 0x27, 16, 2);

    modulesController = new ModulesController(appContext->systemContext, storageType);
    
    std::vector<RelayFullEntity> relays = modulesController->getAllRelays();
    for(auto& fullrelay: relays)
    {
        _Relays.push_back({fullrelay.id, new Relay(fullrelay.PinNumber, fullrelay.Name, fullrelay.NormallyOpen)});
    }

    std::vector<SoilMoistureFullEntity> soilMoistureSensors = modulesController->getAllSoilMoistures();
    for(auto& fullSoilmoistureSensor: soilMoistureSensors)
    {
        _soileMoistureSensors.push_back({fullSoilmoistureSensor.id, new SoilMoistureSensor(fullSoilmoistureSensor.Name, fullSoilmoistureSensor.ConnectionType, fullSoilmoistureSensor.NodeId, fullSoilmoistureSensor.PinNumber, fullSoilmoistureSensor.DryTreshold, fullSoilmoistureSensor.WetTreshold)});
    }

    std::vector<DHTFullEntity> dhtSensors = modulesController->getAllDHTs();
    for(auto& fullDHTSensor: dhtSensors)
    {
        _TemperatureHumiditySensors.push_back({fullDHTSensor.id, new DHTSensor(fullDHTSensor.Name, fullDHTSensor.PinNumber, fullDHTSensor.ModuleType == "DHT22"? DHTType::DHT22: DHTType::DHT11)});
    }
}

void DeviceManager::update()
{
    _resetButton->update();
    for(auto& _relay: _Relays)
    {
        _relay.relay->update();
    }

    for(auto& _temperatureHumiditySensor: _TemperatureHumiditySensors)
    {
        _temperatureHumiditySensor.dhtSensor->update();
    }
}

Button* DeviceManager::resetButton()
{
    return _resetButton;
}

LCD16X2* DeviceManager::mainLCD()
{
    return _mainLCD;
}

Relay* DeviceManager::getRelayById(int id)
{
    for(auto& _relay: _Relays)
    {
        if (_relay.id == id)
        {
            return _relay.relay;
        }        
    }
    return NULL;
}

SoilMoistureSensor* DeviceManager::getSoilMoistureSensorById(int id)
{
    for(auto& _soileMoistureSensor: _soileMoistureSensors)
    {
        if (_soileMoistureSensor.id == id)
        {
            return _soileMoistureSensor.soilMoistureSensor;
        }        
    }
    return NULL;
}

DHTSensor* DeviceManager::getDHTSensorById(int id)
{
    for(auto& _TemperatureHumiditySensor: _TemperatureHumiditySensors)
    {
        if (_TemperatureHumiditySensor.id == id)
        {
            return _TemperatureHumiditySensor.dhtSensor;
        }        
    }
    return NULL;
}

Relay* DeviceManager::getRelayByString(String name)
{
for(auto& _relay: _Relays)
    {
        if (_relay.relay->name == name)
        {
            return _relay.relay;
        }        
    }
    return NULL;
}

SoilMoistureSensor* DeviceManager::getSoilMoistureSensorByString(String name)
{
    for(auto& _soileMoistureSensor: _soileMoistureSensors)
    {
        if (_soileMoistureSensor.soilMoistureSensor->getName() == name)
        {
            return _soileMoistureSensor.soilMoistureSensor;
        }        
    }
    return NULL;
}

DHTSensor* DeviceManager::getDHTSensorByString(String name)
{
for(auto& _TemperatureHumiditySensor: _TemperatureHumiditySensors)
    {
        if (_TemperatureHumiditySensor.dhtSensor->getName() == name)
        {
            return _TemperatureHumiditySensor.dhtSensor;
        }        
    }
    return NULL;
}

#endif