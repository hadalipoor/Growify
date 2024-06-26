#ifndef APPCONTEXT_H
#define APPCONTEXT_H

#include <Context.h>
#include "DeviceManager/IDeviceManager.h"
#include "Growify/IGrowify.h"
#include "Growify/ISystemConditionController.h"

class AppContext
{
private:
    IDeviceManager* _deviceManager;
    IConfig* growifyConfig;
    IGrowify* growify;
    ISystemConditionController* systemConditionController;

public:
    AppContext(Context* context): systemContext(context){}
    ~AppContext(){}

    IDeviceManager* getDeviceManager() { return _deviceManager; }
    void setDeviceManager(IDeviceManager* deviceManager) { _deviceManager = deviceManager; }

    IConfig* getGrowifyConfig() { return growifyConfig; }
    void setGrowifyConfig(IConfig* config) { growifyConfig = config; }
    
    IGrowify* getGrowify() { return growify; }
    void setgrowify(IGrowify* _growify) { growify = _growify; }

    ISystemConditionController* getSystemConditionController() { return systemConditionController; }
    void setSystemConditionController(ISystemConditionController* _systemConditionController) { systemConditionController = _systemConditionController; }
    
    Context* systemContext;
};

#endif //APPCONTEXT_H