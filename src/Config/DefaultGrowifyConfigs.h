
#ifndef DEFAULTGROWIFY_H
#define DEFAULTGROWIFY_H

#include <Arduino.h>
#include <ArduinoJson.h>

class DefaultGrowifyConfigs {

public:
    static const String jsonString;
    static String get(String key);
};

String DefaultGrowifyConfigs::get(String key) {
    StaticJsonDocument<512> doc;
    DeserializationError error = deserializeJson(doc, jsonString);

    if (error) {
        Serial.println(F("Failed to parse jsonString"));
        return "";
    }

    if (doc.containsKey(key)) {
        return String(doc[key].as<const char *>());
    } else {
        Serial.print(F("Key not found in Growify Config: "));
        Serial.println(key);
        return "";
    }
}

const String DefaultGrowifyConfigs::jsonString = R"(
{
    "system_enable" : "true",
    "check_conditions_delay" : "5000"
}
)";

#endif
