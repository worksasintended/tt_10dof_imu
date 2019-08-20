#pragma once
#include<cstdlib>
#include <Arduino.h>

class Buffer{
  public:
    Buffer(size_t _size){
     buffer = (float*)std::malloc(size*sizeof(float));
     writer = buffer; 
     reader = buffer;
     size = _size;
    }
    ~Buffer(){
      std::free(buffer);
    }

    void write(float value);
    bool isEmpty();
    bool isFull();
    void clear();
    float read();
    void step(float** pointer);
    float* stepReturn(float* pointer);

  private:
    float* writer;
    float* reader;
    float* buffer; 
    size_t size;
};
