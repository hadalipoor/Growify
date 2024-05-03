
#ifndef PlantsControlApis_h
#define PlantsControlApis_h


#include "../AppContext.h"
#include "Permissions.h"
class PlantsControlApis : public ApiInterface
{
private:
    AppContext* context;
    std::string class_path = "/plantscontrol";

public:
    PlantsControlApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handledisableCondition(String condition_id);
};

PlantsControlApis::PlantsControlApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    if (!add_apis) return;

    
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/disableCondition"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTSCONTROL_DISABLECONDITION) == AuthorizationResults::SUCCESFULL){return;}
        
        if(!req->getParams()->isQueryParameterSet("condition_id")){
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
        }
        
        String condition_id = getQueryParameterString(req, "condition_id");
        
        response(res, handledisableCondition(condition_id));
    }));
}

String PlantsControlApis::getClassPath()
{
    return String(class_path.c_str());
}



String PlantsControlApis::handledisableCondition(String condition_id) {
    return "";
}

String PlantsControlApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "handledisableCondition") {
        handledisableCondition(parameters["condition_id"]);
        return "OK";
    }
    return "";
}

#endif //PlantsControlApis_h
