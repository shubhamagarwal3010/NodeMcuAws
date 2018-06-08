//AWSDB.h
#ifndef ADSB_H
#define ADSB_H

#include "Esp8266AWSImplementations.h"
#include "AmazonDynamoDBClient.h"
#include "AWSFoundationalTypes.h"
#include "keys.h"

// Constants describing DynamoDB table and values being used
extern Esp8266HttpClient httpClient;
extern Esp8266DateTimeProvider dateTimeProvider;
extern AmazonDynamoDBClient ddbClient;

class AWSDB {

  public:
    void init();
    char* getData2(char* data, char* TABLE_NAME, char* HASH_KEY_NAME, char* HASH_KEY_VALUE);
    char* getData(char* data, char* TABLE_NAME, char* HASH_KEY_NAME, char* HASH_KEY_VALUE, char* RANGE_KEY_NAME, char* RANGE_KEY_VALUE);
    void putData(char* dataField, int data, char* TABLE_NAME, char* HASH_KEY_NAME, char* HASH_KEY_VALUE, char* RANGE_KEY_NAME, const char* RANGE_KEY_VALUE);
};

#endif
