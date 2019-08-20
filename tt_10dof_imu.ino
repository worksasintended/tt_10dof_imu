#include "BluetoothSerial.h"
#include "buffer.h"
BluetoothSerial SerialBT;
Buffer buffer(100000);
TaskHandle_t Task1;


void waitForBtConnection() {
  while (1) {
    if (SerialBT.hasClient()) {
      Serial.println("  ...bluetooth client connected");
      break;
    }
    delay(100);
  }
}

void printBufferToSerial(  void * pvParameters ){
  Serial.println("buffer reader running on core: "+ (String)xPortGetCoreID());
  while(1){
    Serial.println(buffer.read());
  }
}


void setup() {
  Serial.begin(115200);
  bool btState = SerialBT.begin("TT-Sensor Bracket");
  Serial.println("\n Initializing Table Tennis Sensor");
  if (btState) {
    Serial.println("  ...bluetooth running");
  }
  xTaskCreatePinnedToCore(printBufferToSerial, "Reader", 1000, NULL , 0, NULL, 0);
  //waitForBtConnection();


}

void loop() {
  buffer.write(1.1);
  delay(1000); 
}
