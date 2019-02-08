#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <espDMX.h>

const char* ssid = "*********";
const char* password = "*********";

WiFiUDP Udp;
unsigned int localUdpPort = 6666;
byte incomingPacket[512];

void setup()
{
  dmxA.begin();
  WiFi.begin(ssid, password);
  WiFi.mode(WIFI_STA);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
  }
  Udp.begin(localUdpPort);
}


void loop()
{
  int packetSize = Udp.parsePacket();
  if (packetSize == 512 && (Udp.remoteIP().toString() == "192.168.4.200"))
  {
    int len = Udp.read(incomingPacket, 512);
    if (len > 0)
    {
      incomingPacket[len] = 0;
    }
    dmxA.setChans(incomingPacket, 512);
  }
}
