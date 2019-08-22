//#include "BluetoothSerial.h"
#include "buffer.h"
//BluetoothSerial SerialBT;
Buffer buffer = Buffer(7000);
//TaskHandle_t Task1;
unsigned long timeOld;
unsigned long timeNew;


//void waitForBtConnection() {
//  while (1) {
//    if (SerialBT.hasClient()) {
//      Serial.println("  ...bluetooth client connected");
//      SerialBT.print("Hello Client!");
//      break;
//    }
//    delay(100);
//  }
//}

void printBufferToSerial(void *nothing) {
  Serial.println("  ...buffer reader running on core: " + (String)xPortGetCoreID());

  int stepsBundled = 1000;
  String view;
  while (1) {
    view = "";
    for (int i = 0; i < stepsBundled; i++) {
      view += " " + (String)buffer.read();
    }
    Serial.println(ESP.getFreeHeap() / 8 / 1024);
    Serial.println(view);
  }
}


void setup() {
  Serial.begin(115200);
  // bool btState = SerialBT.begin("TT-Sensor Bracket");
  Serial.println("\n Initializing Table Tennis Sensor");
  // if (btState) {
  //   Serial.println("  ...bluetooth running");
  //   vTaskDelay(30);
  // }
  //waitForBtConnection(); 
  xTaskCreatePinnedToCore(printBufferToSerial, "Reader", 1000, NULL , 1, NULL, 0);// 1, &Task1, 0);
  vTaskDelay(100);
  timeOld = millis();

}

void loop() {
  for(int i = 0; i < 100; i++){
    static float val = 0;
    buffer.write(val);
    val += 0.01;
  }
  timeNew = millis();
  //Serial.println(timeNew-timeOld);
  timeOld = timeNew;
}
