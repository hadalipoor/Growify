#ifndef PERMISSIONS_H
#define PERMISSIONS_H

class Permissions
{
public:
    static const String PLANTSTYPE_CREATE;
    static const String PLANTSTYPE_UPDATE;
    static const String PLANTSTYPE_DELETE;
    static const String PLANTSTYPE_GET;
    static const String TEMPERATURECONDITION_CREATE;
    static const String TEMPERATURECONDITION_UPDATE;
    static const String TEMPERATURECONDITION_DELETE;
    static const String TEMPERATURECONDITION_GET;
    static const String HUMIDITYCONDITION_CREATE;
    static const String HUMIDITYCONDITION_UPDATE;
    static const String HUMIDITYCONDITION_DELETE;
    static const String HUMIDITYCONDITION_GET;
    static const String SOILMOISTURECONDITION_CREATE;
    static const String SOILMOISTURECONDITION_UPDATE;
    static const String SOILMOISTURECONDITION_DELETE;
    static const String SOILMOISTURECONDITION_GET;
    static const String LIGHTCONDITION_CREATE;
    static const String LIGHTCONDITION_UPDATE;
    static const String LIGHTCONDITION_DELETE;
    static const String LIGHTCONDITION_GET;
    static const String CONDITION_CREATE;
    static const String CONDITION_UPDATE;
    static const String CONDITION_DELETE;
    static const String CONDITION_GET;
    static const String PLANTS_CREATE;
    static const String PLANTS_UPDATE;
    static const String PLANTS_DELETE;
    static const String PLANTS_GET;
    static const String PLANTSCONTROL_DISABLECONDITION;


    static void addPermissions(Context* context);
};

void Permissions::addPermissions(Context* context)
{
    context->getSecurity()->addPermissionForAdmin(PLANTSTYPE_CREATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(PLANTSTYPE_UPDATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(PLANTSTYPE_DELETE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(PLANTSTYPE_GET, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPERATURECONDITION_CREATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPERATURECONDITION_UPDATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPERATURECONDITION_DELETE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(TEMPERATURECONDITION_GET, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(HUMIDITYCONDITION_CREATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(HUMIDITYCONDITION_UPDATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(HUMIDITYCONDITION_DELETE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(HUMIDITYCONDITION_GET, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTURECONDITION_CREATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTURECONDITION_UPDATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTURECONDITION_DELETE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(SOILMOISTURECONDITION_GET, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(LIGHTCONDITION_CREATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(LIGHTCONDITION_UPDATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(LIGHTCONDITION_DELETE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(LIGHTCONDITION_GET, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(CONDITION_CREATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(CONDITION_UPDATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(CONDITION_DELETE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(CONDITION_GET, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(PLANTS_CREATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(PLANTS_UPDATE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(PLANTS_DELETE, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(PLANTS_GET, "Growify Permissions");
    context->getSecurity()->addPermissionForAdmin(PLANTSCONTROL_DISABLECONDITION, "Growify Permissions");

}

const String Permissions::PLANTSTYPE_CREATE = "plantstype_create";
const String Permissions::PLANTSTYPE_UPDATE = "plantstype_update";
const String Permissions::PLANTSTYPE_DELETE = "plantstype_delete";
const String Permissions::PLANTSTYPE_GET = "plantstype_get";
const String Permissions::TEMPERATURECONDITION_CREATE = "temperaturecondition_create";
const String Permissions::TEMPERATURECONDITION_UPDATE = "temperaturecondition_update";
const String Permissions::TEMPERATURECONDITION_DELETE = "temperaturecondition_delete";
const String Permissions::TEMPERATURECONDITION_GET = "temperaturecondition_get";
const String Permissions::HUMIDITYCONDITION_CREATE = "humiditycondition_create";
const String Permissions::HUMIDITYCONDITION_UPDATE = "humiditycondition_update";
const String Permissions::HUMIDITYCONDITION_DELETE = "humiditycondition_delete";
const String Permissions::HUMIDITYCONDITION_GET = "humiditycondition_get";
const String Permissions::SOILMOISTURECONDITION_CREATE = "soilmoisturecondition_create";
const String Permissions::SOILMOISTURECONDITION_UPDATE = "soilmoisturecondition_update";
const String Permissions::SOILMOISTURECONDITION_DELETE = "soilmoisturecondition_delete";
const String Permissions::SOILMOISTURECONDITION_GET = "soilmoisturecondition_get";
const String Permissions::LIGHTCONDITION_CREATE = "lightcondition_create";
const String Permissions::LIGHTCONDITION_UPDATE = "lightcondition_update";
const String Permissions::LIGHTCONDITION_DELETE = "lightcondition_delete";
const String Permissions::LIGHTCONDITION_GET = "lightcondition_get";
const String Permissions::CONDITION_CREATE = "condition_create";
const String Permissions::CONDITION_UPDATE = "condition_update";
const String Permissions::CONDITION_DELETE = "condition_delete";
const String Permissions::CONDITION_GET = "condition_get";
const String Permissions::PLANTS_CREATE = "plants_create";
const String Permissions::PLANTS_UPDATE = "plants_update";
const String Permissions::PLANTS_DELETE = "plants_delete";
const String Permissions::PLANTS_GET = "plants_get";
const String Permissions::PLANTSCONTROL_DISABLECONDITION = "plantscontrol_disablecondition";


#endif // PERMISSIONS_H
