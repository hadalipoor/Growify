#ifndef PLANTSTYPECONTROLLER_H
#define PLANTSTYPECONTROLLER_H

#include <OStad.h>
#include "../Entities/PlantsTypeEntity.h"
#include "../../AppContext.h"

class PlantsTypeController : public MainController<PlantsTypeEntity> {
public:
    AppContext* appContext;
    PlantsTypeController(AppContext* appContext, StorageType _storageType) : MainController<PlantsTypeEntity>(appContext->systemContext ,"plantstype", _storageType), appContext(appContext) {}
};

#endif // PLANTSTYPECONTROLLER_H