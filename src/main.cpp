#ifndef UNIT_TEST

#include <Arduino.h>

#endif

#include <DNSServer.h>
#include <WiFiManager.h>

#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

#include <ArduinoJson.h>

// TODO: Make button to reset wifi

/*********************************************************************/

ESP8266WebServer server(80);

/*********************************************************************/

// RELAY PINS
int relay[] = {0, 4, 5, 16};
bool status_relay[] = {false, false, false, false};

/*********************************************************************/

/**
 * Size of relay array
 * 
 * @return number of element in array
 */
int get_relay_size() {
    return sizeof(relay) / sizeof(relay[0]);
}

/**
 * Initialization of relay pins
 * 
 * @param relay_size relay number
 */
void initRelay(int relay_size) {
    for (int i = 0; i < relay_size; i++) {
        pinMode(relay[i], OUTPUT);
        digitalWrite(relay[i], HIGH);
    }
}

/*********************************************************************/

/**
 * Check if the relay pin received is correct
 * 
 * @param num relay pin
 * @return "true" if is correct | "false" if is incorrect
 */
bool is_valid_relay_pin(int num) {
    if (num >= 0 && num <= get_relay_size() - 1 && num != NULL) {
        return true;
    }

    return false;
}

/*********************************************************************/

/**
 * Turn on a specific relay pin
 * 
 * @param pin pin of relay pin
 */
void turnOn(int pin) {
    digitalWrite(pin, LOW);
}

/**
 * Turn off a specific relay pin
 * 
 * @param pin Pin of relay pin
 */
void turnOff(int pin) {
    digitalWrite(pin, HIGH);
}

/*********************************************************************/

/**
 * Send response
 * 
 * @param html_code HTML status code
 * @param message 
 */
void sendResponse(int html_code, String message) {
    String body;
    DynamicJsonDocument raw_body(1024);

    raw_body["msg"] = message;

    serializeJson(raw_body, body);

    server.send(html_code, "text/json", body);
}

/*********************************************************************/

/**
 * Turn on/off a specific relay by parameters
 */
void checkArgs() {
    int html_code;
    String message = "";

    DynamicJsonDocument body(1024);

    if (server.hasArg("plain") == false) {
        html_code = 400;
        message = "Body not found";
    } else {
        deserializeJson(body, server.arg("plain"));

        String action = body["action"];
        int pin = body["pin"];
        pin -= 1;

        if (action == "on" || action == "off") {
            if (is_valid_relay_pin(body["pin"])) {
                html_code = 200;
                message = "Successful action";

                if (action == "on") {
                    turnOn(relay[pin]);
                    status_relay[pin] = true;
                } else {
                    turnOff(relay[pin]);
                    status_relay[pin] = false;
                }
            } else {
                html_code = 400;
                message = "Relay number not found";
            }
        } else {
            html_code = 400;
            message = "Action not found";
        }
    }

    sendResponse(html_code, message);
}

/*********************************************************************/

/**
 * Send the status of relays
 */
void getStatus() {
    int html_code = 200;
    String status;
    DynamicJsonDocument doc(1024);

    for (int i = 0; i < get_relay_size(); i++) {
        int num = i + 1;
        String name = "relay_" + String(num);

        doc[name] = status_relay[i];
    }

    serializeJson(doc, status);

    sendResponse(html_code, status);
}

/*********************************************************************/

void setup() {
    Serial.begin(9600);

    initRelay(get_relay_size());

    // WiFiManager
    WiFiManager wifiManager;

    // Reset settings - for testing
    // wifiManager.resetSettings();

    wifiManager.setTimeout(180);
    wifiManager.setHostname("ESP_PowerStrip");

    if (!wifiManager.autoConnect("ESP_PowerStrip - Access Poinit")) {
        Serial.println("Failed to connect and hit timeout");
        delay(3000);

        ESP.reset();
        delay(5000);
    }

    Serial.println("Connected");

    server.on("/", checkArgs);
    server.on("/status", getStatus);

    server.begin();
}

/*********************************************************************/

void loop() {
    server.handleClient();
}