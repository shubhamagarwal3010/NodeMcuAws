## AWS SDK for ESP8266 <span clear="right">

<img src="https://cloud.githubusercontent.com/assets/6751621/14332057/30905a36-fc48-11e5-87af-ede357864439.png" alt="Glorious ESP8266" title="Glorious ESP8266" align="right" />

The purpose of this project is to add support for aws dynamoDB with **Espressif ESP8266** microcontroller .

### Getting Started with ESP8266

Getting the sample working has the following steps: setting up the DynamoDB table, importing the SDK and copying over the sample, configuring the `keys.cpp` file, and setting up the hardware. These steps are outlined for the ESP8266's sample, you can find more instructions for the other boards on the [original repository](https://github.com/awslabs/aws-sdk-arduino).


<sub>*Quick reminder of the wiring diagram for this module (ESP-01 version), note that GPIO0 needs to be shorted to ground and restarted to flash a new Firmware. The module needs to be powered by an external 3.3v supply as most of the serial adapters won't provide enough current.*</sub>


#### Step 1: Setting up the DynamoDB Table

You will need to set up a DynamoDB table with the same name, hash key, and range key. These values are defined as constants in the sample, i.e. `HASH_KEY_NAME` and `TABLE_NAME`.

You can follow the steps below to get the tables set up with the right values:

* Log into the [AWS Console](http://console.aws.amazon.com/) and navigate to **DynamoDB**.
* Click on the "Create Table" button.
* Enter `ESP8266AWSDemo` as the *Table Name*, `id` as the primary *Partition Key*, and `timest` as the primary *Sort Key*. Be sure to mark *id* as *String* and *timest* as *Number*.
* Just one *Read Capacity Unit* and one *Write Capacity Unit* will be more than enough for this demo. Press create with these values.
* After the table has finished creating you are good to go, your ESP will take care about populating it.


#### Step 2: Creating `keys.h` and `keys.cpp`

You will need to create and add `keys.h` and `keys.cpp` into the `AWSArduinoSDK` directory you made. Alternatively, if you want to use different access keys for every sketch you make, just put them inside your current sketch folder. These files define the `awsKeyID` and `awsSecKey` values used by the sketch, the files may be structured as following:

```
// keys.h
#ifndef KEYS_H_
#define KEYS_H_

extern const char* awsKeyID;  // Declare these variables to
extern const char* awsSecKey; // be accessible by the sketch

#endif
```

```
// keys.cpp
#include "keys.h"

const char* awsKeyID = "YOUR AWS KEY ID HERE";
const char* awsSecKey = "YOUR AWS SECRET KEY HERE";
```

*Do not share your AWS keys with anyone, it is reccomended to create a dedicated user with restricted permissions, do not use your root account. If you accidentally push your keys online disable them immediatly from the [AWS IAM console](https://console.aws.amazon.com/iam/home)*


#### Step 4: Setting up Hardware

The ESP8266 sample uses only a "virtual sensor" (i.e. numbers generated randomly), so it is only necessary to give power to the module without adding extra components.

### Supported Services

| Service Name                             | Status                | API Version |
| :--------------------------------------- | :-------------------- | :---------- |
| Amazon DynamoDB                          | Complete              | 2012-08-10  |
| Amazon Kinesis \*                        | Complete              | 2013-12-02  |
| Amazon Simple Notification Service       | Only Publish          | 2010-03-31  |

<sub>\* *The code for creating, serializing, and deserializing Kinesis input and output objects is included, but the devices that the experimental SDK has been tested on do not have readily available HTTPS support. This code has been included so it can be used by those who want to do further experimenting with Kinesis and HTTPS.*</sub>

----------

###### Disclaimer

This fork is not affiliated in any way with Amazon Web Services (AWS), Arduino or Espressif which are registered trademarks of their respective holders.
