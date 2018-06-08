/* This sample uses PutItem on a DynamoDB table to save the state of a virtual
 * temperature sensor.
 *
 * For this demo to work you must have keys.h/.ccp files that contain your AWS
 * access keys and define "awsSecKey" and "awsKeyID", a DynamoDB table with the
 * name defined by the constant TABLE_NAME with hash and range keys as defined
 * by constants HASH_KEY_NAME/RANGE_KEY_NAME. */

#include <ESP8266WiFi.h>

#include "Esp8266AWSImplementations.h"
#include "AmazonDynamoDBClient.h"
#include "AWSFoundationalTypes.h"
#include "keys.h"


// Common AWS constants
const char* AWS_REGION = "ap-south-1";  // REPLACE with your region
const char* AWS_ENDPOINT = "amazonaws.com";

// Init and connect Esp8266 WiFi to local wlan
const char* pSSID = "Free Wi-Fi 2.4G"; // REPLACE with your network SSID (name)
const char* pPassword = "bitchplease"; // REPLACE with your network password (use for WPA, or use as key for WEP)

// Constants describing DynamoDB table and values being used


/* Temperature reading. */
int reading;

Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;

AmazonDynamoDBClient ddbClient;

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
    ddbClient.setAWSRegion(AWS_REGION);
    ddbClient.setAWSEndpoint(AWS_ENDPOINT);
    ddbClient.setAWSSecretKey(awsSecKey);
    ddbClient.setAWSKeyID(awsKeyID);
    ddbClient.setHttpClient(&httpClient);
    ddbClient.setDateTimeProvider(&dateTimeProvider);
}

String getData2(char* data, char* TABLE_NAME, char* HASH_KEY_NAME, char* HASH_KEY_VALUE) {
    String val = "0";
    /* Set the string and number values for the range and hash Keys,
     * respectively. */
    /* Create an Item. */
    AttributeValue userId;
    userId.setN(HASH_KEY_VALUE);

    /* Create key-value pairs out of the hash and range keys, and create
     * a map out off them, which is the key. */
    MinimalKeyValuePair < MinimalString, AttributeValue
            > att1(HASH_KEY_NAME, userId);
    MinimalKeyValuePair<MinimalString, AttributeValue> itemArray[] = { att1 };
    GetItemInput getItemInput;
    getItemInput.setKey(MinimalMap < AttributeValue > (itemArray, 1));

    /* Looking to get the R G and B values */
    MinimalString attributesToGet[] = { data };
    getItemInput.setAttributesToGet(
            MinimalList < MinimalString > (attributesToGet, 1));
     /* Set other values. */
    getItemInput.setTableName(TABLE_NAME);

    ActionError actionError;
    /* Perform getItem and check for errors. */
    GetItemOutput getItemOutput = ddbClient.getItem(getItemInput,
            actionError);
    switch (actionError) {
    case NONE_ACTIONERROR:
        Serial.println("GetItem2 succeeded!");
        {
            /* Get the "item" from the getItem output. */
            MinimalMap < AttributeValue > attributeMap =
                    getItemOutput.getItem();
            AttributeValue av;
            /* Get the rgb values and set the led with them. */
            attributeMap.get(data, av);
            val = av.getS().getCStr();
        }
        break;
    case INVALID_REQUEST_ACTIONERROR:
        Serial.print("ERROR: ");
        Serial.println(getItemOutput.getErrorMessage().getCStr());
        break;
    case MISSING_REQUIRED_ARGS_ACTIONERROR:
        Serial.println(
                "ERROR: Required arguments were not set for GetItemInput");
        break;
    case RESPONSE_PARSING_ACTIONERROR:
        Serial.println("ERROR: Problem parsing http response of GetItem\n");
        break;
    case CONNECTION_ACTIONERROR:
        Serial.println("ERROR: Connection problem");
        break;
    }
    return val;
}
String getData(char* data, char* TABLE_NAME, char* HASH_KEY_NAME, char* HASH_KEY_VALUE, char* RANGE_KEY_NAME, char* RANGE_KEY_VALUE) {
    String val = "0";
    /* Set the string and number values for the range and hash Keys,
     * respectively. */
    /* Create an Item. */
    AttributeValue userId;
    userId.setS(HASH_KEY_VALUE);
    AttributeValue rangeKeyValue;
    rangeKeyValue.setN(RANGE_KEY_VALUE);

    /* Create key-value pairs out of the hash and range keys, and create
     * a map out off them, which is the key. */
    MinimalKeyValuePair < MinimalString, AttributeValue
            > att1(HASH_KEY_NAME, userId);
    MinimalKeyValuePair < MinimalString, AttributeValue
            > att2(RANGE_KEY_NAME, rangeKeyValue);
    MinimalKeyValuePair<MinimalString, AttributeValue> itemArray[] = { att1, att2 };
    GetItemInput getItemInput;
    getItemInput.setKey(MinimalMap < AttributeValue > (itemArray, 2));

    /* Looking to get the R G and B values */
    MinimalString attributesToGet[] = { data };
    getItemInput.setAttributesToGet(
            MinimalList < MinimalString > (attributesToGet, 1));
     /* Set other values. */
    getItemInput.setTableName(TABLE_NAME);

    ActionError actionError;
    /* Perform getItem and check for errors. */
    GetItemOutput getItemOutput = ddbClient.getItem(getItemInput,
            actionError);
    switch (actionError) {
    case NONE_ACTIONERROR:
        Serial.println("GetItem succeeded!");
        {
            /* Get the "item" from the getItem output. */
            MinimalMap < AttributeValue > attributeMap =
                    getItemOutput.getItem();
            AttributeValue av;
            /* Get the rgb values and set the led with them. */
            attributeMap.get(data, av);
            val = av.getS().getCStr();
        }
        break;
    case INVALID_REQUEST_ACTIONERROR:
        Serial.print("ERROR: ");
        Serial.println(getItemOutput.getErrorMessage().getCStr());
        break;
    case MISSING_REQUIRED_ARGS_ACTIONERROR:
        Serial.println(
                "ERROR: Required arguments were not set for GetItemInput");
        break;
    case RESPONSE_PARSING_ACTIONERROR:
        Serial.println("ERROR: Problem parsing http response of GetItem\n");
        break;
    case CONNECTION_ACTIONERROR:
        Serial.println("ERROR: Connection problem");
        break;
    }
    return val;
}

void putData(char* dataField, int data, char* TABLE_NAME, char* HASH_KEY_NAME, char* HASH_KEY_VALUE, char* RANGE_KEY_NAME, const char* RANGE_KEY_VALUE) {

    /* Create an Item. */
    AttributeValue userId;
    userId.setS(HASH_KEY_VALUE);

    AttributeValue rangeKeyValue;
    rangeKeyValue.setN(RANGE_KEY_VALUE);


    /* Create an AttributeValue for 'temp', convert the number to a
     * string (AttributeValue object represents numbers as strings), and
     * use setN to apply that value to the AttributeValue. */
    char numberBuffer[4];
    AttributeValue attributeValue;
    sprintf(numberBuffer, "%d", data);
    attributeValue.setN(numberBuffer);

    /* Create the Key-value pairs and make an array of them. */
    MinimalKeyValuePair < MinimalString, AttributeValue
            > att1(HASH_KEY_NAME, userId);
    MinimalKeyValuePair < MinimalString, AttributeValue
            > att2(RANGE_KEY_NAME, rangeKeyValue);
    MinimalKeyValuePair < MinimalString, AttributeValue
            > att3(dataField, attributeValue);
    MinimalKeyValuePair<MinimalString, AttributeValue> itemArray[] = { att1,
            att2, att3 };

    PutItemInput putItemInput;
    /* Set values for putItemInput. */
    putItemInput.setItem(MinimalMap < AttributeValue > (itemArray, 3));
    putItemInput.setTableName(TABLE_NAME);

    ActionError actionError;
    /* Perform putItem and check for errors. */
    PutItemOutput putItemOutput = ddbClient.putItem(putItemInput,
            actionError);
    switch (actionError) {
    case NONE_ACTIONERROR:
        Serial.println("PutItem succeeded!");
        break;
    case INVALID_REQUEST_ACTIONERROR:
        Serial.print("ERROR: Invalid request");
        Serial.println(putItemOutput.getErrorMessage().getCStr());
        break;
    case MISSING_REQUIRED_ARGS_ACTIONERROR:
        Serial.println(
                "ERROR: Required arguments were not set for PutItemInput");
        break;
    case RESPONSE_PARSING_ACTIONERROR:
        Serial.println("ERROR: Problem parsing http response of PutItem");
        break;
    case CONNECTION_ACTIONERROR:
        Serial.println("ERROR: Connection problem");
        break;
    }
     /* wait to not double-record */
    delay(750);

}

void loop() {
    reading = random(20, 30);
    Serial.print("Temperature = ");
    Serial.println(reading);
    putData("temp", reading, "letthingsspeak-mobilehub-849318221-ESP8266AWSDemo", "userId", "ESP01", "timest", dateTimeProvider.getDateTime());
    Serial.println(getData("roomName", "letthingsspeak-mobilehub-849318221-LetThingsSpeak", "userId", "shubhama", "deviceId", "124"));
    Serial.println(getData2("ownerId", "letthingsspeak-mobilehub-849318221-device_map", "deviceId", "11101"));
    delay(5000);
}
