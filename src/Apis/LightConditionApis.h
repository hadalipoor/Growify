#ifndef LIGHTCONDITIONAPIS_h
#define LIGHTCONDITIONAPIS_h

#include "../AppContext.h"
#include "../Database/Controllers/LightConditionController.h"
#include "Permissions.h"

class LightConditionApis : public ApiInterface
{
private:
    AppContext* context;
    LightConditionController* lightconditionController;
    std::string class_path = "/lightcondition";

public:
    LightConditionApis(AppContext* cntxt, bool add_apis);
    String getClassPath() override;

    String callFunction(String functionName, std::map<String, String> parameters) override;
    
    String handlecreate(String name, int module_id, EBPDateTime start_time, EBPDateTime end_time, String led_relay_id, String description);
    String handleupdate(int id, String name, int module_id, EBPDateTime start_time, EBPDateTime end_time, String led_relay_id, String description);
    String handledelete(int id);
    String handlegetAll();
    String handlegetById(int id);
    String handleget(String query);
};

LightConditionApis::LightConditionApis(AppContext* cntxt, bool add_apis): context(cntxt) {
    lightconditionController = new LightConditionController(context, storageType);

    if (!add_apis) return;    

    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/create"), LambdaResourceNode::REQUEST_METHOD_POST, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_CREATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("module_id") || !req->getParams()->isQueryParameterSet("start_time") || !req->getParams()->isQueryParameterSet("end_time") || !req->getParams()->isQueryParameterSet("led_relay_id") || !req->getParams()->isQueryParameterSet("description"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        String name = getQueryParameterString(req, "name");
    int module_id = getQueryParameterint(req, "module_id");
    EBPDateTime start_time = getQueryParameterEBPDateTime(req, "start_time");
    EBPDateTime end_time = getQueryParameterEBPDateTime(req, "end_time");
    String led_relay_id = getQueryParameterString(req, "led_relay_id");
    String description = getQueryParameterString(req, "description");

        response(res, handlecreate(name, module_id, start_time, end_time, led_relay_id, description));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/update"), LambdaResourceNode::REQUEST_METHOD_PUT, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_UPDATE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id") || !req->getParams()->isQueryParameterSet("name") || !req->getParams()->isQueryParameterSet("module_id") || !req->getParams()->isQueryParameterSet("start_time") || !req->getParams()->isQueryParameterSet("end_time") || !req->getParams()->isQueryParameterSet("led_relay_id") || !req->getParams()->isQueryParameterSet("description"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        String name = getQueryParameterString(req, "name");
    int module_id = getQueryParameterint(req, "module_id");
    EBPDateTime start_time = getQueryParameterEBPDateTime(req, "start_time");
    EBPDateTime end_time = getQueryParameterEBPDateTime(req, "end_time");
    String led_relay_id = getQueryParameterString(req, "led_relay_id");
    String description = getQueryParameterString(req, "description");
        
        response(res, handleupdate(id, name, module_id, start_time, end_time, led_relay_id, description));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/delete"), LambdaResourceNode::REQUEST_METHOD_DELETE, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_DELETE) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }
        
        int id = getQueryParameterint(req, "id");
        
        response(res, handledelete(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getAll"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        response(res, handlegetAll());
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/getById"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("id"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        int id = getQueryParameterint(req, "id");
        
        response(res, handlegetById(id));
    }));
    context->systemContext->getNetwork()->addApi(new ResourceNode(std::string(class_path + "/get"), LambdaResourceNode::REQUEST_METHOD_GET, [&](HTTPRequest * req, HTTPResponse * res) {
        if (!context->systemContext->getSecurity()->checkAuthentication(req, res, Permissions::LIGHTCONDITION_GET) == AuthorizationResults::SUCCESFULL){return;}
        if (!req->getParams()->isQueryParameterSet("query"))
        {
            response(res, 400, MISSING_INPUT_PARAMS_MESSAGE);
            return;
        }

        String query = getQueryParameterString(req, "query");
        
        response(res, handleget(query));
    }));
}

String LightConditionApis::getClassPath()
{
    return String(class_path.c_str());
}

String LightConditionApis::handlecreate(String name, int module_id, EBPDateTime start_time, EBPDateTime end_time, String led_relay_id, String description) {
    LightConditionEntity* lightconditionEntity = new LightConditionEntity(name, module_id, start_time, end_time, led_relay_id, description);
    int id = lightconditionController->Add(*lightconditionEntity);
    if (id != -1)
    {
        return CREATE_SUCCESFULL_MESSAGE;
    }
    
    return CREATE_FAILED_MESSAGE;
}
String LightConditionApis::handleupdate(int id, String name, int module_id, EBPDateTime start_time, EBPDateTime end_time, String led_relay_id, String description) {
    LightConditionEntity* lightconditionEntity = new LightConditionEntity(id, name, module_id, start_time, end_time, led_relay_id, description);
    
    if (lightconditionController->Update(*lightconditionEntity))
    {
        return UPDATE_SUCCESFULL_MESSAGE;
    }
    
    return UPDATE_FAILED_MESSAGE;
}
String LightConditionApis::handledelete(int id) {
    
    if (lightconditionController->Delete(id))
    {
        return DELETE_SUCCESFULL_MESSAGE;
    }
    
    return DELETE_FAILED_MESSAGE;
}
String LightConditionApis::handlegetAll() {
    return lightconditionController->GetAllJson();
}
String LightConditionApis::handlegetById(int id) {
    return lightconditionController->GetById(id).toJson();
}
String LightConditionApis::handleget(String query) {
    return lightconditionController->GetJson(query);
}

String LightConditionApis::callFunction(String functionName, std::map<String, String> parameters) {
    
    if (functionName == "create") {
        return handlecreate(parameters["name"], parameters["module_id"].toInt(), parameters["start_time"], parameters["end_time"], parameters["led_relay_id"], parameters["description"]);
    }
    if (functionName == "update") {
        return handleupdate(parameters["id"].toInt(), parameters["name"], parameters["module_id"].toInt(), parameters["start_time"], parameters["end_time"], parameters["led_relay_id"], parameters["description"]);
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

#endif //LIGHTCONDITIONApis_h

    