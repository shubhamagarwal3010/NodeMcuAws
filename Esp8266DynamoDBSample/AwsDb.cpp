#include "AwsDb.h"


// Common AWS constants
const char* AWS_REGION = "ap-south-1";  // REPLACE with your region
const char* AWS_ENDPOINT = "amazonaws.com";

Esp8266HttpClient httpClient;
Esp8266DateTimeProvider dateTimeProvider;
AmazonDynamoDBClient ddbClient;

void AWSDB::init() {
  /* Initialize ddbClient. */
  ddbClient.setAWSRegion(AWS_REGION);
  ddbClient.setAWSEndpoint(AWS_ENDPOINT);
  ddbClient.setAWSSecretKey(awsSecKey);
  ddbClient.setAWSKeyID(awsKeyID);
  ddbClient.setHttpClient(&httpClient);
  ddbClient.setDateTimeProvider(&dateTimeProvider);
}


char* AWSDB::getData(char* data, char* TABLE_NAME, char* HASH_KEY_NAME, int HASH_KEY_VALUE) {
  char* val = "0";
  /* Set the string and number values for the range and hash Keys,
     respectively. */
  /* Create an Item. */
  char numberBuffer[4];
  AttributeValue attributeValue;
  sprintf(numberBuffer, "%d", HASH_KEY_VALUE);
  attributeValue.setN(numberBuffer);

  /* Create key-value pairs out of the hash and range keys, and create
     a map out off them, which is the key. */
  MinimalKeyValuePair < MinimalString, AttributeValue
  > att1(HASH_KEY_NAME, attributeValue);
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
        strcpy(val, (av.getS().getCStr()));
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
int AWSDB::getIntData(char* data, char* TABLE_NAME, char* HASH_KEY_NAME, int HASH_KEY_VALUE) {
  int val = 0;
  /* Set the string and number values for the range and hash Keys,
     respectively. */
  /* Create an Item. */
  char numberBuffer[4];
  AttributeValue attributeValue;
  sprintf(numberBuffer, "%d", HASH_KEY_VALUE);
  attributeValue.setN(numberBuffer);

  /* Create key-value pairs out of the hash and range keys, and create
     a map out off them, which is the key. */
  MinimalKeyValuePair < MinimalString, AttributeValue
  > att1(HASH_KEY_NAME, attributeValue);
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
        val = atoi(av.getN().getCStr());
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

char* AWSDB::getData(char* data, char* TABLE_NAME, char* HASH_KEY_NAME, char* HASH_KEY_VALUE) {
  char* val = "0";
  /* Set the string and number values for the range and hash Keys,
     respectively. */
  /* Create an Item. */
  AttributeValue attributeValue;
  attributeValue.setN(HASH_KEY_VALUE);

  /* Create key-value pairs out of the hash and range keys, and create
     a map out off them, which is the key. */
  MinimalKeyValuePair < MinimalString, AttributeValue > att1(HASH_KEY_NAME, attributeValue);
  MinimalKeyValuePair<MinimalString, AttributeValue > itemArray[] = { att1 };
  GetItemInput getItemInput;
  getItemInput.setKey(MinimalMap < AttributeValue > (itemArray, 1));

  /* Looking to get the R G and B values */
  MinimalString attributesToGet[] = { data };
  getItemInput.setAttributesToGet( MinimalList < MinimalString > (attributesToGet, 1));
  /* Set other values. */
  getItemInput.setTableName(TABLE_NAME);

  ActionError actionError;
  /* Perform getItem and check for errors. */
  GetItemOutput getItemOutput = ddbClient.getItem(getItemInput, actionError);
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
        strcpy(val, (av.getS().getCStr()));
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

char* AWSDB::getData(char* data, char* TABLE_NAME, char* HASH_KEY_NAME, char* HASH_KEY_VALUE, char* RANGE_KEY_NAME, int RANGE_KEY_VALUE) {
  char* val = "0";
  /* Set the string and number values for the range and hash Keys,
     respectively. */
  /* Create an Item. */
  AttributeValue userId;
  userId.setS(HASH_KEY_VALUE);
  
  char numberBuffer[4];
  AttributeValue attributeValue;
  sprintf(numberBuffer, "%d", RANGE_KEY_VALUE);
  
  AttributeValue rangeKeyValue;
  rangeKeyValue.setN(numberBuffer);

  /* Create key-value pairs out of the hash and range keys, and create
     a map out off them, which is the key. */
  MinimalKeyValuePair < MinimalString, AttributeValue > att1(HASH_KEY_NAME, userId);
  MinimalKeyValuePair < MinimalString, AttributeValue > att2(RANGE_KEY_NAME, rangeKeyValue);
  MinimalKeyValuePair<MinimalString, AttributeValue> itemArray[] = { att1, att2 };
  GetItemInput getItemInput;
  getItemInput.setKey(MinimalMap < AttributeValue > (itemArray, 2));

  /* Looking to get the R G and B values */
  MinimalString attributesToGet[] = { data };
  getItemInput.setAttributesToGet( MinimalList < MinimalString > (attributesToGet, 1));
  /* Set other values. */
  getItemInput.setTableName(TABLE_NAME);

  ActionError actionError;
  /* Perform getItem and check for errors. */
  GetItemOutput getItemOutput = ddbClient.getItem(getItemInput, actionError);
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
        strcpy(val, (av.getS().getCStr()));
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

void AWSDB::putData(char* dataField, int data, char* TABLE_NAME, char* HASH_KEY_NAME, char* HASH_KEY_VALUE, char* RANGE_KEY_NAME, const char* RANGE_KEY_VALUE) {

  /* Create an Item. */
  AttributeValue userId;
  userId.setS(HASH_KEY_VALUE);

  AttributeValue rangeKeyValue;
  rangeKeyValue.setN(RANGE_KEY_VALUE);


  /* Create an AttributeValue for 'temp', convert the number to a
     string (AttributeValue object represents numbers as strings), and
     use setN to apply that value to the AttributeValue. */
  char numberBuffer[4];
  AttributeValue attributeValue;
  sprintf(numberBuffer, "%d", data);
  attributeValue.setN(numberBuffer);

  /* Create the Key-value pairs and make an array of them. */
  MinimalKeyValuePair < MinimalString, AttributeValue > att1(HASH_KEY_NAME, userId);
  MinimalKeyValuePair < MinimalString, AttributeValue > att2(RANGE_KEY_NAME, rangeKeyValue);
  MinimalKeyValuePair < MinimalString, AttributeValue > att3(dataField, attributeValue);
  MinimalKeyValuePair<MinimalString, AttributeValue> itemArray[] = { att1, att2, att3 };

  PutItemInput putItemInput;
  /* Set values for putItemInput. */
  putItemInput.setItem(MinimalMap < AttributeValue > (itemArray, 3));
  putItemInput.setTableName(TABLE_NAME);

  ActionError actionError;
  /* Perform putItem and check for errors. */
  PutItemOutput putItemOutput = ddbClient.putItem(putItemInput, actionError);
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

