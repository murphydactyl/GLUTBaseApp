//
//  fpsclock.h
//  TrivialGLUT
//
//  Created by research on 5/8/12.
//  Copyright (c) 2012 __MyCompanyName__. All rights reserved.
//

#ifndef utils_fpsclock_h
#define utils_fpsclock_h
#include "clock.h"
#include "circularbuffer.h"


class FPSClock {
private:
  Clock wallClock;
  CircularBuffer* buffer;
  uint64_t frames;
  
public: 
  FPSClock() {
    buffer = new CircularBuffer(100);
    wallClock.tic();
    frames = 0;
  };
  
  double update() {
    double delta = wallClock.toc();
    wallClock.tic();
    buffer->save(delta);
    return buffer->length() / buffer->sum();
  }
  
};
  
#endif
