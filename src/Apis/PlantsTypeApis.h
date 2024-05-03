#ifndef PLANTSTYPEAPIS_h
#define PLANTSTYPEAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/PlantsTypeController.h"
#include "Permissions.h"

class PlantsTypeApis : public ApiInterface
{
private:
    AppContext* context;
    PlantsTypeController* plantstypeController;
    std::string class_path = "/plantstype";

public:
    PlantsTypeApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String type, int condition_id, String description);
    String handleupdate(int id, String type, int condition_id, String description);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

PlantsTypeApis::PlantsTypeApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    plantstypeController = new PlantsTypeController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTSTYPE_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("type") || !req->getParams()->isQueryParameterSet("condition_id") || !req->getParams()->isQueryParameterSet("description"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String type = getQueryParameterString(req, "type");
    int condition_id = getQueryParameterint(req, "condition_id");
    String description = getQueryParameterString(req, "description");

        response(res, handlecreate(type, condition_id, description));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTSTYPE_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("type") || !req->getParams()->isQueryParameterSet("condition_id") || !req->getParams()->isQueryParameterSet("description"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String type = getQueryParameterString(req, "type");
    int condition_id = getQueryParameterint(req, "condition_id");
    String description = getQueryParameterString(req, "description");
        
        response(res, handleupdate(id, type, condition_id, description));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTSTYPE_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTSTYPE_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTSTYPE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTSTYPE_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String PlantsTypeApis::getClassPath()
{
    return String(class_path.c_str());
}

String PlantsTypeApis::handlecreate(String type, int condition_id, String description) {
    PlantsTypeEntity* plantstypeEntity = new PlantsTypeEntity(type, condition_id, description);
    int id = plantstypeController->Add(*plantstypeEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String PlantsTypeApis::handleupdate(int id, String type, int condition_id, String description) {
    PlantsTypeEntity* plantstypeEntity = new PlantsTypeEntity(id, type, condition_id, description);
    
    if (plantstypeController->Update(*plantstypeEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String PlantsTypeApis::handledelete(int id) {
    
    if (plantstypeController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String PlantsTypeApis::handlegetAll() {
    return plantstypeController->GetAllJson();
}
String PlantsTypeApis::handlegetById(int id) {
    return plantstypeController->GetById(id).toJson();
}
String PlantsTypeApis::handleget(String query) {
    return plantstypeController->GetJson(query);
}

String PlantsTypeApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["type"], parameters["condition_id"].toInt(), parameters["description"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["type"], parameters["condition_id"].toInt(), parameters["description"]);
    }
    if (functionName == "delete") {
        return handledelete(parameters["id"].toInt());
    }
    if (functionName == "getAll") {
        return handlegetAll();
    }
    if (functionName == "getById") {
        return handlegetById(parameters["id"].toInt());
    }
    if (functionName == "get") {
        return handleget(parameters["query"]);
    }
    return String(NO_FUNCTION_MESSAGE + functionName);
}

#endif //PLANTSTYPEApis_h

    