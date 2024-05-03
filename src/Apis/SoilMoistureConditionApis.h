#ifndef SOILMOISTURECONDITIONAPIS_h
#define SOILMOISTURECONDITIONAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/SoilMoistureConditionController.h"
#include "Permissions.h"

class SoilMoistureConditionApis : public ApiInterface
{
private:
    AppContext* context;
    SoilMoistureConditionController* soilmoistureconditionController;
    std::string class_path = "/soilmoisturecondition";

public:
    SoilMoistureConditionApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String name, int module_id, int min_soil_moisture, int max_soil_moisture, String pump_relay_id, String soil_moisture_warning_relay_id, String description);
    String handleupdate(int id, String name, int module_id, int min_soil_moisture, int max_soil_moisture, String pump_relay_id, String soil_moisture_warning_relay_id, String description);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

SoilMoistureConditionApis::SoilMoistureConditionApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    soilmoistureconditionController = new SoilMoistureConditionController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("module_id") || !req->getParams()->isQueryParameterSet("min_soil_moisture") || !req->getParams()->isQueryParameterSet("max_soil_moisture") || !req->getParams()->isQueryParameterSet("pump_relay_id") || !req->getParams()->isQueryParameterSet("soil_moisture_warning_relay_id") || !req->getParams()->isQueryParameterSet("description"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String name = getQueryParameterString(req, "name");
    int module_id = getQueryParameterint(req, "module_id");
    int min_soil_moisture = getQueryParameterint(req, "min_soil_moisture");
    int max_soil_moisture = getQueryParameterint(req, "max_soil_moisture");
    String pump_relay_id = getQueryParameterString(req, "pump_relay_id");
    String soil_moisture_warning_relay_id = getQueryParameterString(req, "soil_moisture_warning_relay_id");
    String description = getQueryParameterString(req, "description");

        response(res, handlecreate(name, module_id, min_soil_moisture, max_soil_moisture, pump_relay_id, soil_moisture_warning_relay_id, description));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("module_id") || !req->getParams()->isQueryParameterSet("min_soil_moisture") || !req->getParams()->isQueryParameterSet("max_soil_moisture") || !req->getParams()->isQueryParameterSet("pump_relay_id") || !req->getParams()->isQueryParameterSet("soil_moisture_warning_relay_id") || !req->getParams()->isQueryParameterSet("description"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String name = getQueryParameterString(req, "name");
    int module_id = getQueryParameterint(req, "module_id");
    int min_soil_moisture = getQueryParameterint(req, "min_soil_moisture");
    int max_soil_moisture = getQueryParameterint(req, "max_soil_moisture");
    String pump_relay_id = getQueryParameterString(req, "pump_relay_id");
    String soil_moisture_warning_relay_id = getQueryParameterString(req, "soil_moisture_warning_relay_id");
    String description = getQueryParameterString(req, "description");
        
        response(res, handleupdate(id, name, module_id, min_soil_moisture, max_soil_moisture, pump_relay_id, soil_moisture_warning_relay_id, description));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::SOILMOISTURECONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String SoilMoistureConditionApis::getClassPath()
{
    return String(class_path.c_str());
}

String SoilMoistureConditionApis::handlecreate(String name, int module_id, int min_soil_moisture, int max_soil_moisture, String pump_relay_id, String soil_moisture_warning_relay_id, String description) {
    SoilMoistureConditionEntity* soilmoistureconditionEntity = new SoilMoistureConditionEntity(name, module_id, min_soil_moisture, max_soil_moisture, pump_relay_id, soil_moisture_warning_relay_id, description);
    int id = soilmoistureconditionController->Add(*soilmoistureconditionEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String SoilMoistureConditionApis::handleupdate(int id, String name, int module_id, int min_soil_moisture, int max_soil_moisture, String pump_relay_id, String soil_moisture_warning_relay_id, String description) {
    SoilMoistureConditionEntity* soilmoistureconditionEntity = new SoilMoistureConditionEntity(id, name, module_id, min_soil_moisture, max_soil_moisture, pump_relay_id, soil_moisture_warning_relay_id, description);
    
    if (soilmoistureconditionController->Update(*soilmoistureconditionEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String SoilMoistureConditionApis::handledelete(int id) {
    
    if (soilmoistureconditionController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String SoilMoistureConditionApis::handlegetAll() {
    return soilmoistureconditionController->GetAllJson();
}
String SoilMoistureConditionApis::handlegetById(int id) {
    return soilmoistureconditionController->GetById(id).toJson();
}
String SoilMoistureConditionApis::handleget(String query) {
    return soilmoistureconditionController->GetJson(query);
}

String SoilMoistureConditionApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["name"], parameters["module_id"].toInt(), parameters["min_soil_moisture"].toInt(), parameters["max_soil_moisture"].toInt(), parameters["pump_relay_id"], parameters["soil_moisture_warning_relay_id"], parameters["description"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["name"], parameters["module_id"].toInt(), parameters["min_soil_moisture"].toInt(), parameters["max_soil_moisture"].toInt(), parameters["pump_relay_id"], parameters["soil_moisture_warning_relay_id"], parameters["description"]);
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

#endif //SOILMOISTURECONDITIONApis_h

    