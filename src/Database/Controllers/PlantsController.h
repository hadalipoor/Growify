#ifndef PLANTSCONTROLLER_H
#define PLANTSCONTROLLER_H

#include <OStad.h>
#include "../Entities/PlantsEntity.h"
#include "../../AppContext.h"

class PlantsController : public MainController<PlantsEntity> {
public:
    AppContext* appContext;
    PlantsController(AppContext* appContext, StorageType _storageType) : MainController<PlantsEntity>(appContext->systemContext ,"plants", _storageType), appContext(appContext) {}
};

#endif // PLANTSCONTROLLER_H