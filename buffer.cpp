#include"buffer.h"
#include<Arduino.h>
//TODO: 
// - delay timing adjusted to sensor read speed 

float Buffer::read(){
  while(isEmpty()){
    vTaskDelay(1);
  }
  float value = *reader;
  step(&reader);
  return value;  
}

void Buffer::write(float value){
  if(isFull()){
    Serial.println("  ...buffer full");
    while(isFull()){
    //we need to do something or watchdog is killing us (such a bitch)
      vTaskDelay(1);
    }
  }

  *writer = value;
  step(&writer);
}

void Buffer::clear(){
  writer = buffer;
  reader = buffer;
}

bool Buffer::isEmpty(){
  return (writer == reader); 
}

bool Buffer::isFull(){
  return ( stepReturn(writer) == reader);
}

void Buffer::step(float** pointer){
  *pointer = ((*pointer+1-buffer) % size ) + buffer;
}

float* Buffer::stepReturn(float* pointer){
  return ((pointer+1-buffer) % size ) + buffer;
}
