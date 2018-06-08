/* This sample uses PutItem on a DynamoDB table to save the state of a virtual
 * temperature sensor.
 *
 * For this demo to work you must have keys.h/.ccp files that contain your AWS
 * access keys and define "awsSecKey" and "awsKeyID", a DynamoDB table with the
 * name defined by the constant TABLE_NAME with hash and range keys as defined
 * by constants HASH_KEY_NAME/RANGE_KEY_NAME. */

#include <ESP8266WiFi.h>
#include "AwsDb.h"


AWSDB DB;
// Init and connect Esp8266 WiFi to local wlan
const char* pSSID = "Free Wi-Fi 2.4G"; // REPLACE with your network SSID (name)
const char* pPassword = "bitchplease"; // REPLACE with your network password (use for WPA, or use as key for WEP)


void setup() {
    /* Begin serial communication. */
    Serial.begin(115200);
    Serial.println();
    Serial.print("Attempting to connect to SSID: ");
    Serial.println(pSSID);

    WiFi.hostname("ESP8266");

    // If pPassword is set the most secure supported mode will be automatically selected
    WiFi.begin(pSSID, pPassword);

    // Wait for WiFi connection
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print(".");
        delay(500);
    }

    Serial.println();

    /* Initialize ddbClient. */
    DB.init();
}

void loop() {
    /* Temperature reading. */
    int reading;
    reading = random(20, 30);
    Serial.print("Temperature = ");
    Serial.println(reading);
    DB.putData("temp", reading, "letthingsspeak-mobilehub-849318221-ESP8266AWSDemo", "userId", "ESP01", "timest", dateTimeProvider.getDateTime());
    Serial.println(DB.getData("roomName", "letthingsspeak-mobilehub-849318221-LetThingsSpeak", "userId", "shubhama", "deviceId", "124"));
    Serial.println(DB.getData2("ownerId", "letthingsspeak-mobilehub-849318221-device_map", "deviceId", "11101"));
    delay(5000);
}
