#ifndef TEMPERATURECONDITIONAPIS_h
#define TEMPERATURECONDITIONAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/TemperatureConditionController.h"
#include "Permissions.h"

class TemperatureConditionApis : public ApiInterface
{
private:
    AppContext* context;
    TemperatureConditionController* temperatureconditionController;
    std::string class_path = "/temperaturecondition";

public:
    TemperatureConditionApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String name, int module_id, int min_temperature, int max_temperature, String cooler_relay_id, String hitter_relay_id, String description);
    String handleupdate(int id, String name, int module_id, int min_temperature, int max_temperature, String cooler_relay_id, String hitter_relay_id, String description);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

TemperatureConditionApis::TemperatureConditionApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    temperatureconditionController = new TemperatureConditionController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURECONDITION_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("module_id") || !req->getParams()->isQueryParameterSet("min_temperature") || !req->getParams()->isQueryParameterSet("max_temperature") || !req->getParams()->isQueryParameterSet("cooler_relay_id") || !req->getParams()->isQueryParameterSet("hitter_relay_id") || !req->getParams()->isQueryParameterSet("description"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String name = getQueryParameterString(req, "name");
    int module_id = getQueryParameterint(req, "module_id");
    int min_temperature = getQueryParameterint(req, "min_temperature");
    int max_temperature = getQueryParameterint(req, "max_temperature");
    String cooler_relay_id = getQueryParameterString(req, "cooler_relay_id");
    String hitter_relay_id = getQueryParameterString(req, "hitter_relay_id");
    String description = getQueryParameterString(req, "description");

        response(res, handlecreate(name, module_id, min_temperature, max_temperature, cooler_relay_id, hitter_relay_id, description));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURECONDITION_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("module_id") || !req->getParams()->isQueryParameterSet("min_temperature") || !req->getParams()->isQueryParameterSet("max_temperature") || !req->getParams()->isQueryParameterSet("cooler_relay_id") || !req->getParams()->isQueryParameterSet("hitter_relay_id") || !req->getParams()->isQueryParameterSet("description"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String name = getQueryParameterString(req, "name");
    int module_id = getQueryParameterint(req, "module_id");
    int min_temperature = getQueryParameterint(req, "min_temperature");
    int max_temperature = getQueryParameterint(req, "max_temperature");
    String cooler_relay_id = getQueryParameterString(req, "cooler_relay_id");
    String hitter_relay_id = getQueryParameterString(req, "hitter_relay_id");
    String description = getQueryParameterString(req, "description");
        
        response(res, handleupdate(id, name, module_id, min_temperature, max_temperature, cooler_relay_id, hitter_relay_id, description));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURECONDITION_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURECONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURECONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::TEMPERATURECONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String TemperatureConditionApis::getClassPath()
{
    return String(class_path.c_str());
}

String TemperatureConditionApis::handlecreate(String name, int module_id, int min_temperature, int max_temperature, String cooler_relay_id, String hitter_relay_id, String description) {
    TemperatureConditionEntity* temperatureconditionEntity = new TemperatureConditionEntity(name, module_id, min_temperature, max_temperature, cooler_relay_id, hitter_relay_id, description);
    int id = temperatureconditionController->Add(*temperatureconditionEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String TemperatureConditionApis::handleupdate(int id, String name, int module_id, int min_temperature, int max_temperature, String cooler_relay_id, String hitter_relay_id, String description) {
    TemperatureConditionEntity* temperatureconditionEntity = new TemperatureConditionEntity(id, name, module_id, min_temperature, max_temperature, cooler_relay_id, hitter_relay_id, description);
    
    if (temperatureconditionController->Update(*temperatureconditionEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String TemperatureConditionApis::handledelete(int id) {
    
    if (temperatureconditionController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String TemperatureConditionApis::handlegetAll() {
    return temperatureconditionController->GetAllJson();
}
String TemperatureConditionApis::handlegetById(int id) {
    return temperatureconditionController->GetById(id).toJson();
}
String TemperatureConditionApis::handleget(String query) {
    return temperatureconditionController->GetJson(query);
}

String TemperatureConditionApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["name"], parameters["module_id"].toInt(), parameters["min_temperature"].toInt(), parameters["max_temperature"].toInt(), parameters["cooler_relay_id"], parameters["hitter_relay_id"], parameters["description"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["name"], parameters["module_id"].toInt(), parameters["min_temperature"].toInt(), parameters["max_temperature"].toInt(), parameters["cooler_relay_id"], parameters["hitter_relay_id"], parameters["description"]);
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

#endif //TEMPERATURECONDITIONApis_h

    