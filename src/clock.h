//
//  clock.h
//
//  Created by Jonathan Tompson on 3/30/12.
//  Copyright (c) 2012 NYU. All rights reserved.
//

#ifndef utils_clock_h
#define utils_clock_h

#ifdef __APPLE_CC__
#include <mach/mach.h>
#include <mach/mach_time.h>


class Clock {
public:
  Clock() {
    time = mach_absolute_time();
    (void) mach_timebase_info(&sTimebaseInfo);
  }
  
  void Update() {
    time_old = time;
    //time = mach_absolute_time();
    time = nowInNanoseconds();
  }
  
  void tic() {
    time_old = nowInNanoseconds();
  }
  
  double toc() {
    time = nowInNanoseconds();
    return getDeltaTime();
  }
  
  void tic(uint64_t start) {
    time_old = start;
  }
  
  double toc(uint64_t end) {
    time = end;
    return getDeltaTime();
  }
  
  //  double getDeltaTime() {
  //    elapsedNano = (time-time_old) * sTimebaseInfo.numer / sTimebaseInfo.denom;
  //    return ((double)elapsedNano / 1000000000.0);
  //  }
  
  double getDeltaTime() {
    return timeDifferenceInSeconds(time, time_old);
  }
  
  double secondsElapsed() {
    return getDeltaTime();
  }
  
  double nowMinusThenInSeconds(uint64_t then) {
    return timeDifferenceInSeconds(nowInNanoseconds(), then);
  }
  
  double timeDifferenceInSeconds(uint64_t now, uint64_t then) {
    return (now - then) / 1000000000.0;
  }
  
  uint64_t nowInNanoseconds() {
    return (mach_absolute_time() * sTimebaseInfo.numer) / sTimebaseInfo.denom;
  }
  
private:
  uint64_t time;
  uint64_t time_old;
  uint64_t elapsedNano;
  mach_timebase_info_data_t sTimebaseInfo;
};
#endif

#if defined( __WIN32__ ) || defined( _WIN32 ) || defined( WIN32 )
#include <windows.h>
#include <stdexcept>

class Clock {
public:
  Clock() {
    if(!QueryPerformanceFrequency((LARGE_INTEGER*)&m_cntFreq))
    {
      throw std::runtime_error("clk::GetTime() - Failed to get performance counter!");
    }
    m_secsPerCnt = 1.0 / (double)m_cntFreq;
    QueryPerformanceCounter((LARGE_INTEGER*)&m_cntCurrent);
  }
  
  void Update() {
    m_cntOld = m_cntCurrent;
    QueryPerformanceCounter((LARGE_INTEGER*)&m_cntCurrent);
  }
  
  double getDeltaTime() {
    double elapsedSec = (double)(m_cntCurrent-m_cntOld) * (double)m_secsPerCnt;
    return elapsedSec;
  }
  
private:
  double elapsedSec;
  __int64 m_cntFreq, // Frequency of the precision counter
  m_cntCurrent, // Current counter value
  m_cntOld;
  double  m_secsPerCnt; // counter period
  __int64 m_clockPauseTime; // record when the clock was paused
};
#endif

#endif
