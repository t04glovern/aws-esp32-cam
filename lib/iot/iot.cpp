#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>
#include "conf.h"
#include <iot.h>
#include <ArduinoJson.h>

IOT::IOT(WiFiClientSecure &wifi_client, PubSubClient &pubsub_client)
{
    this->_wifi_client = &wifi_client;
    this->_pubsub_client = &pubsub_client;
}

void IOT::setup(void)
{
    _pubsub_client->setServer(IOT_ENDPOINT, 8883);
    _wifi_client->setCACert(CA_CERT);
    _wifi_client->setCertificate(IOT_CERT);
    _wifi_client->setPrivateKey(IOT_PRIVATE_KEY);
    _pubsub_client->connect(DEVICE_NAME);
    while (!_pubsub_client->connected())
    {
        _pubsub_client->connect(DEVICE_NAME);
        sleep(5);
    }
}

void IOT::print_on_publish(bool goal)
{
    _PRINT = goal;
}

bool IOT::publish(String topic, const uint8_t *message, unsigned int len)
{
    while (!_pubsub_client->connected())
    {
        _pubsub_client->connect(DEVICE_NAME);
        sleep(5);
    }
    return _pubsub_client->publish(topic.c_str(), message, len);
}

void IOT::print_callback(char *topic, byte *message, unsigned int length)
{
    Serial.println(String("Message arrived on topic") + String(topic));
    if (_PRINT)
    {
        for (int ii = 0; ii < length; ii++)
        {
            Serial.print((char)message[ii]);
        }
        Serial.println();
    }
}