
#ifndef GROWIFYENTITY_H
#define GROWIFYENTITY_H

#include <OStad.h>

class GrowifyConfigEntity : public Entity {
public:
    static const String COLUMN_KEY;
    static const String COLUMN_VALUE;

    String key;
    String value;

    GrowifyConfigEntity() : Entity() {}

    GrowifyConfigEntity(int id, const String &_key, const String &_value) : Entity() {
        this->id = id;
        key = _key;
        value = _value;
        addColumn(COLUMN_KEY, key, "string");
        addColumn(COLUMN_VALUE, value, "string");
    }

    GrowifyConfigEntity(const String &_key, const String &_value) : GrowifyConfigEntity(0, _key, _value) {}

    static GrowifyConfigEntity fromEntity(Entity entity)
    {
        GrowifyConfigEntity systemConfigEntity = GrowifyConfigEntity();
        systemConfigEntity.fromString(entity.toString());
        return systemConfigEntity;
    }

    void setKey(const String &_key) {
        key = _key;
        SetValue(COLUMN_KEY, _key);
    }

    String getKey() {
        return GetValue(COLUMN_KEY);
    }

    void setValue(const String &_value) {
        value = _value;
        SetValue(COLUMN_VALUE, _value);
    }

    String getValue() {
        return GetValue(COLUMN_VALUE);
    }
};

const String GrowifyConfigEntity::COLUMN_KEY = "key";
const String GrowifyConfigEntity::COLUMN_VALUE = "value";

#endif // GROWIFYENTITY_H

