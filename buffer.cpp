#include"buffer.h"
#include<Arduino.h>

float Buffer::read(){
  while(isEmpty()){
    delay(10);
  }
  float value = *reader;
  step(&reader);
  return value;  
}

void Buffer::write(float value){
  while(isFull()){
    delay(10);
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
