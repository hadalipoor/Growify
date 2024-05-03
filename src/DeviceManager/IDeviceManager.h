
#ifndef IDEVICEMANAGER_H
#define IDEVICEMANAGER_H

#include <EBPInterfaces.h>

class IDeviceManager
{
public:
    virtual ~IDeviceManager(){}

    virtual void initialize() = 0;
    virtual void update() = 0;
    virtual Button* resetButton() = 0;
    virtual LCD16X2* mainLCD() = 0;
    
    virtual Relay* getRelayById(int id) = 0;
    virtual SoilMoistureSensor* getSoilMoistureSensorById(int id) = 0;
    virtual DHTSensor* getDHTSensorById(int id) = 0;

    virtual Relay* getRelayByString(String name) = 0;
    virtual SoilMoistureSensor* getSoilMoistureSensorByString(String name) = 0;
    virtual DHTSensor* getDHTSensorByString(String name) = 0;

};

#endif