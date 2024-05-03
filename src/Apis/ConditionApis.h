#ifndef CONDITIONAPIS_h
#define CONDITIONAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/ConditionController.h"
#include "Permissions.h"

class ConditionApis : public ApiInterface
{
private:
    AppContext* context;
    ConditionController* conditionController;
    std::string class_path = "/condition";

public:
    ConditionApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String name, int temperature_condition_id, int humidity_condition_id, int soilMoistureC_condition_id, int light_condition_id, String description);
    String handleupdate(int id, String name, int temperature_condition_id, int humidity_condition_id, int soilMoistureC_condition_id, int light_condition_id, String description);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

ConditionApis::ConditionApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    conditionController = new ConditionController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::CONDITION_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("temperature_condition_id") || !req->getParams()->isQueryParameterSet("humidity_condition_id") || !req->getParams()->isQueryParameterSet("soilMoistureC_condition_id") || !req->getParams()->isQueryParameterSet("light_condition_id") || !req->getParams()->isQueryParameterSet("description"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String name = getQueryParameterString(req, "name");
    int temperature_condition_id = getQueryParameterint(req, "temperature_condition_id");
    int humidity_condition_id = getQueryParameterint(req, "humidity_condition_id");
    int soilMoistureC_condition_id = getQueryParameterint(req, "soilMoistureC_condition_id");
    int light_condition_id = getQueryParameterint(req, "light_condition_id");
    String description = getQueryParameterString(req, "description");

        response(res, handlecreate(name, temperature_condition_id, humidity_condition_id, soilMoistureC_condition_id, light_condition_id, description));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::CONDITION_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("temperature_condition_id") || !req->getParams()->isQueryParameterSet("humidity_condition_id") || !req->getParams()->isQueryParameterSet("soilMoistureC_condition_id") || !req->getParams()->isQueryParameterSet("light_condition_id") || !req->getParams()->isQueryParameterSet("description"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String name = getQueryParameterString(req, "name");
    int temperature_condition_id = getQueryParameterint(req, "temperature_condition_id");
    int humidity_condition_id = getQueryParameterint(req, "humidity_condition_id");
    int soilMoistureC_condition_id = getQueryParameterint(req, "soilMoistureC_condition_id");
    int light_condition_id = getQueryParameterint(req, "light_condition_id");
    String description = getQueryParameterString(req, "description");
        
        response(res, handleupdate(id, name, temperature_condition_id, humidity_condition_id, soilMoistureC_condition_id, light_condition_id, description));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::CONDITION_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::CONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::CONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::CONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String ConditionApis::getClassPath()
{
    return String(class_path.c_str());
}

String ConditionApis::handlecreate(String name, int temperature_condition_id, int humidity_condition_id, int soilMoistureC_condition_id, int light_condition_id, String description) {
    ConditionEntity* conditionEntity = new ConditionEntity(name, temperature_condition_id, humidity_condition_id, soilMoistureC_condition_id, light_condition_id, description);
    int id = conditionController->Add(*conditionEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String ConditionApis::handleupdate(int id, String name, int temperature_condition_id, int humidity_condition_id, int soilMoistureC_condition_id, int light_condition_id, String description) {
    ConditionEntity* conditionEntity = new ConditionEntity(id, name, temperature_condition_id, humidity_condition_id, soilMoistureC_condition_id, light_condition_id, description);
    
    if (conditionController->Update(*conditionEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String ConditionApis::handledelete(int id) {
    
    if (conditionController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String ConditionApis::handlegetAll() {
    return conditionController->GetAllJson();
}
String ConditionApis::handlegetById(int id) {
    return conditionController->GetById(id).toJson();
}
String ConditionApis::handleget(String query) {
    return conditionController->GetJson(query);
}

String ConditionApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["name"], parameters["temperature_condition_id"].toInt(), parameters["humidity_condition_id"].toInt(), parameters["soilMoistureC_condition_id"].toInt(), parameters["light_condition_id"].toInt(), parameters["description"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["name"], parameters["temperature_condition_id"].toInt(), parameters["humidity_condition_id"].toInt(), parameters["soilMoistureC_condition_id"].toInt(), parameters["light_condition_id"].toInt(), parameters["description"]);
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

#endif //CONDITIONApis_h

    