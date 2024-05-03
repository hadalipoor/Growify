
#ifndef APIS_H
#define APIS_H

#include "Permissions.h"
#include "PlantsControlApis.h"
#include "PlantsTypeApis.h"
#include "TemperatureConditionApis.h"
#include "HumidityConditionApis.h"
#include "SoilMoistureConditionApis.h"
#include "LightConditionApis.h"
#include "ConditionApis.h"
#include "PlantsApis.h"


void createApis(AppContext* appContext)
{
    std::vector<ApiInterface*> apis = std::vector<ApiInterface*>();

    
    PlantsControlApis* plantscontrolApis = new PlantsControlApis(appContext, true);
    apis.push_back(plantscontrolApis);
    
    PlantsTypeApis* plantstypeApis = new PlantsTypeApis(appContext, true);
    apis.push_back(plantstypeApis);
    
    TemperatureConditionApis* temperatureconditionApis = new TemperatureConditionApis(appContext, true);
    apis.push_back(temperatureconditionApis);
    
    HumidityConditionApis* humidityconditionApis = new HumidityConditionApis(appContext, true);
    apis.push_back(humidityconditionApis);
    
    SoilMoistureConditionApis* soilmoistureconditionApis = new SoilMoistureConditionApis(appContext, true);
    apis.push_back(soilmoistureconditionApis);
    
    LightConditionApis* lightconditionApis = new LightConditionApis(appContext, true);
    apis.push_back(lightconditionApis);
    
    ConditionApis* conditionApis = new ConditionApis(appContext, true);
    apis.push_back(conditionApis);
    
    PlantsApis* plantsApis = new PlantsApis(appContext, true);
    apis.push_back(plantsApis);
    

    appContext->systemContext->getNetwork()->addApis(apis);
}

#endif //APIS_H
    