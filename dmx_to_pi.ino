#include <Wire.h>
#include <DMXSerial.h>

int request;
byte msg[32];

void setup() {
  Wire.begin(8);
  Wire.setClock(600000);
  Wire.onRequest(requestEvent);
  DMXSerial.init(DMXReceiver);
  delay(1000);
  request = 0;
}

void loop() {
}

void requestEvent() {
  for(int i = 1; i < 32; i++){
    msg[i-1] = DMXSerial.read(i + request*31);
  }
  msg[31] = request;
  Wire.write(msg, sizeof(msg));
  request += 1;
  if(request > 16){
    request = 0;
  }
}
