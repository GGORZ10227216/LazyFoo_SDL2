#include "LTimer.h"

LTimer::LTimer() {
  //Initialize the variables
  mStartTicks = 0;
  mPausedTicks = 0;
  mPaused = false;
  mStarted = false;
}

void LTimer::start() {
  // Start the timer
  mStarted = true ;
  mPaused = false ;
  mStartTicks = SDL_GetTicks() ;
  mPausedTicks = 0 ;
} // LTimer::start()

void LTimer::stop() {
  mStarted = false ;
  mPaused = false ;
  mStartTicks = 0 ;
  mPausedTicks = 0 ;
} // LTimer()::stop()

void LTimer::pause() {
  if ( mStarted && !mPaused ) {
    // Pause the timer
    mPaused = true ;

    mPausedTicks = SDL_GetTicks() - mStartTicks ;
    mStartTicks = 0 ;
  } // if
} // LTimer::pause()

void LTimer::unpause() {
  if ( mStarted && mPaused ) {
    // Unpause the timer
    mPaused = false ;

    mStartTicks = SDL_GetTicks() - mPausedTicks ;
    mPausedTicks = 0 ;
  } // if
} // LTimer::unpause()

uint32_t LTimer::getTicks() {
  //The actual timer time
  uint32_t time = 0;
  //If the timer is running
  if( mStarted ) {
    //If the timer is paused
    if( mPaused ) {
      //Return the number of ticks when the timer was paused
      time = mPausedTicks;
    } //if
    else {
      //Return the current time minus the start time
      time = SDL_GetTicks() - mStartTicks;
    } // else
  } // if

  return time;
} // LTimer::getTicks()

bool LTimer::isStarted() { //Timer is running and paused or unpaused
  return mStarted ;
} // LTimer::isStarted()

bool LTimer::isPaused() { //Timer is running and paused
  return mPaused && mStarted ;
} // LTimer::isPaused()

LTimer::~LTimer() {
  //dtor
}
