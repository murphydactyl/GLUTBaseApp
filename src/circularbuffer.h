//
//  circularbuffer.h
//  TrivialGLUT
//
//  Created by research on 5/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef utils_circularbuffer_h
#define utils_circularbuffer_h

class CircularBuffer {

private:
  double* _data;
  double _sum;
  bool _wrapped;
  uint64_t _head;
  uint64_t _size;

  
  void wrap() {
    if (_head >= _size) {
      _head = 0;
      _wrapped = true;    
    }
  }
  
  void init(uint64_t size) {
    _size = size;
    _data = new double[size];
    _head = 0;
    _wrapped = false;    
    _sum = 0;
    for (int i = 0; i < size; i++) {
      _data[i] = 0;
    }
  }
    

public:
  
  CircularBuffer() {
    init(0);
  }
  
  CircularBuffer(uint64_t size) {
    init(size);
  }
    
  ~CircularBuffer() {
    delete [] _data;
  }
  
  double mean() {
    uint64_t actual_length = length();
    if (actual_length > 0) {
      return _sum / actual_length;
    } else {
      return 0;
    }
  }
  
  double sum() {
    return _sum;
  }
  
  double reset(double fillvalue) {
    uint64_t actual_length = length(); 
    for (int i = 0; i < actual_length; i++) {
      _data[i] = fillvalue;
    }
    _wrapped = false;
  }
  
  double reset() {
    reset(0.0);
  }
  
  void save(double value) {
    wrap();
    _sum -= _data[_head];
    _data[_head] = value;
    _sum += value;
    _head += 1;
    wrap();
  }
  
  uint64_t length() {
    if (_wrapped) {
      return _size;
    } else {
      return _head;
    }
  }
  
};

#endif
