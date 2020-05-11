#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <PubSubClient.h>

class IOT
{
public:
    IOT(WiFiClientSecure &wifi_client, PubSubClient &pubsub_client);
    //void register_callback(string topic, function);
    void print_on_publish(bool goal);
    bool publish(String topic, const uint8_t *message, unsigned int len);
    void setup(void);
    PubSubClient *_pubsub_client;

private:
    void print_callback(char *topic, byte *message, unsigned int length);
    bool _PRINT = false;
    WiFiClientSecure *_wifi_client;
};
