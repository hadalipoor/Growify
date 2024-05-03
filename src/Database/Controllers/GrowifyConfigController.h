
#ifndef GROWIFYCONFIGCONTROLLER_H
#define GROWIFYCONFIGCONTROLLER_H

#include "../../AppContext.h"
#include "../Entities/GrowifyConfigEntity.h"

class GrowifyConfigController : public MainController<GrowifyConfigEntity>{
protected:
public:
    AppContext* appContext;
    GrowifyConfigController(AppContext* appContext, StorageType _storageType) : MainController<GrowifyConfigEntity>(appContext->systemContext ,"growify_config", _storageType), appContext(appContext) {}

};

#endif //GROWIFYCONFIGCONTROLLER_H
    