#ifndef ISYSTEMCONDITIONCONTROLLER_H
#define ISYSTEMCONDITIONCONTROLLER_H

class ISystemConditionController
{
public:
    virtual void update() = 0;
    virtual void initialize() = 0;
};

#endif