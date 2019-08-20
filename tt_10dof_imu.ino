#include "BluetoothSerial.h"
#include "buffer.h"
BluetoothSerial SerialBT;
Buffer buffer(10);
TaskHandle_t Task1;


void waitForBtConnection() {
  while (1) {
    if (SerialBT.hasClient()) {
      Serial.println("  ...bluetooth client connected");
      SerialBT.print("Hello Client!");
      break;
    }
    delay(100);
  }
}

void printBufferToSerial(void *nothing){
  Serial.println("  ...buffer reader running on core: "+ (String)xPortGetCoreID());

  int stepsBundled = 100;
  String data;

  while(1){
    data = "";
    for(int i=0; i<stepsBundled; i++){
      data += " " + (String)buffer.read();
    }
    Serial.println(data);
  }
}


void setup() {
  Serial.begin(115200);
  bool btState = SerialBT.begin("TT-Sensor Bracket");
  Serial.println("\n Initializing Table Tennis Sensor");
  if (btState) {
    Serial.println("  ...bluetooth running");
    vTaskDelay(30);
  }
  //waitForBtConnection();
  xTaskCreatePinnedToCore(printBufferToSerial, "Reader", 1000, NULL , 1, &Task1, 0);
  vTaskDelay(100);

}

void loop() {
  static float val = 0;
  buffer.write(val);
  val += 0.01;
  vTaskDelay(10);
}
