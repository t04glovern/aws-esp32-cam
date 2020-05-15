# Libraries

## conf

Contains a header file that you should include your WiFi credentials and AWS Certificate/Endpoint information

## PubSubClient

Literally just a copy of [knollearys pubsubclient](https://github.com/knolleary/pubsubclient) at ```update 2.7```, with some changes to the ```PubSubClient.h``` to allow a larger payload (default is 128 bytes) and to increase the timeout to something more reasonable for my purposes.

## iot

Class to be a bit of a wrapper to PubSubClient to keep main clean from unnessessary stuff realated to the inner workings and setup of the MQTT client.
