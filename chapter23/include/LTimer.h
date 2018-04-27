#ifndef LTIMER_H
#define LTIMER_H

#include <SDL_Utility.h>

class LTimer {
 public:
  LTimer();

  void start() ;
  void stop() ;
  void pause() ;
  void unpause() ;

  uint32_t getTicks() ;

  bool isStarted() ;
  bool isPaused() ;
  virtual ~LTimer();

 protected:

 private:
  uint32_t mStartTicks ;
  uint32_t mPausedTicks ;

  bool mPaused ;
  bool mStarted ;
};

#endif // LTIMER_H
