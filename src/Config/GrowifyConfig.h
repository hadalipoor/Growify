
#ifndef GROWIFYCONFIGS_H
#define GROWIFYCONFIGS_H

#include <string>
#include "DefaultGrowifyConfigs.h"
#include "../AppContext.h"
#include "../Database/Controllers/GrowifyConfigController.h"
#include "GrowifyConfigKeys.h"

class GrowifyConfig : public IConfig {

private:
    GrowifyConfigController* growifyConfigController;

public:
    AppContext* appContext;
    GrowifyConfig(AppContext* cntxt):appContext (cntxt) {
    }
    
    void initialize() {
        growifyConfigController = new GrowifyConfigController(appContext, storageType);
    }

    String get(const String& key) {
        std::vector<GrowifyConfigEntity> growifyConfigEntities  = growifyConfigController->Get(GrowifyConfigEntity::COLUMN_KEY + "=" + key);
        
        if (growifyConfigEntities.size() > 0)
        {
            GrowifyConfigEntity configEntity = growifyConfigEntities.at(0);
            configEntity.fromString(configEntity.toString());
            if (configEntity.id == -1) {
                return "";
            } else {
                return configEntity.getValue();
            }
        }
        else
        {
            GrowifyConfigEntity* growifyConfigEntity = new GrowifyConfigEntity(key,DefaultGrowifyConfigs::get(key));
            growifyConfigController->Add(*growifyConfigEntity);
            return DefaultGrowifyConfigs::get(key);
        }
    }

    void set(const String& key, const String& value) {
        GrowifyConfigEntity configEntity = growifyConfigController->Get(GrowifyConfigEntity::COLUMN_KEY + "=" + key).at(0);
        if (configEntity.id == -1) { // Key does not exist
            configEntity.setKey(key);
            configEntity.setValue(value);
            growifyConfigController->Add(configEntity);
        } else { // Key exists
            configEntity.setValue(value);
            growifyConfigController->Update(configEntity);
        }
    }

};

#endif // GROWIFY_H
