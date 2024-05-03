#ifndef PLANTSAPIS_h
#define PLANTSAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/PlantsController.h"
#include "Permissions.h"

class PlantsApis : public ApiInterface
{
private:
    AppContext* context;
    PlantsController* plantsController;
    std::string class_path = "/plants";

public:
    PlantsApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(int plants_type_id, String name, int active, int condition_id);
    String handleupdate(int id, int plants_type_id, String name, int active, int condition_id);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

PlantsApis::PlantsApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    plantsController = new PlantsController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTS_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("plants_type_id") || !req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("active") || !req->getParams()->isQueryParameterSet("condition_id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int plants_type_id = getQueryParameterint(req, "plants_type_id");
    String name = getQueryParameterString(req, "name");
    int active = getQueryParameterint(req, "active");
    int condition_id = getQueryParameterint(req, "condition_id");

        response(res, handlecreate(plants_type_id, name, active, condition_id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTS_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("plants_type_id") || !req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("active") || !req->getParams()->isQueryParameterSet("condition_id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        int plants_type_id = getQueryParameterint(req, "plants_type_id");
    String name = getQueryParameterString(req, "name");
    int active = getQueryParameterint(req, "active");
    int condition_id = getQueryParameterint(req, "condition_id");
        
        response(res, handleupdate(id, plants_type_id, name, active, condition_id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTS_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTS_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTS_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::PLANTS_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String PlantsApis::getClassPath()
{
    return String(class_path.c_str());
}

String PlantsApis::handlecreate(int plants_type_id, String name, int active, int condition_id) {
    PlantsEntity* plantsEntity = new PlantsEntity(plants_type_id, name, active, condition_id);
    int id = plantsController->Add(*plantsEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String PlantsApis::handleupdate(int id, int plants_type_id, String name, int active, int condition_id) {
    PlantsEntity* plantsEntity = new PlantsEntity(id, plants_type_id, name, active, condition_id);
    
    if (plantsController->Update(*plantsEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String PlantsApis::handledelete(int id) {
    
    if (plantsController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String PlantsApis::handlegetAll() {
    return plantsController->GetAllJson();
}
String PlantsApis::handlegetById(int id) {
    return plantsController->GetById(id).toJson();
}
String PlantsApis::handleget(String query) {
    return plantsController->GetJson(query);
}

String PlantsApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["plants_type_id"].toInt(), parameters["name"], parameters["active"].toInt(), parameters["condition_id"].toInt());
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["plants_type_id"].toInt(), parameters["name"], parameters["active"].toInt(), parameters["condition_id"].toInt());
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

#endif //PLANTSApis_h

    