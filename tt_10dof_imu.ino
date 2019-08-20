#include "BluetoothSerial.h"
#include "buffer.h"
BluetoothSerial SerialBT;



void waitForBtConnection() {
  while (1) {
    if (SerialBT.hasClient()) {
      Serial.println("  ...bluetooth client connected");
      break;
    }
    delay(100);
  }
}

Buffer buffer(100);

void setup() {
  Serial.begin(115200);
  bool btState = SerialBT.begin("TT-Sensor Bracket");
  Serial.println("\n Initializing Table Tennis Sensor");
  if (btState) {
    Serial.println("  ...bluetooth running");
  }

  
  float test= 1.1;
  buffer.write(test);
  Serial.println("test1");
  buffer.write(1.3);
  Serial.println("test1");
  Serial.println(buffer.read());
  Serial.println(buffer.read());
  Serial.println(buffer.read());
  Serial.println("test");
  waitForBtConnection();


}

void loop() {
  SerialBT.print(".");
}
