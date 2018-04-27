#ifndef SPRITE_H
#define SPRITE_H

#include <vector>

#include <SDL_Utility.h>
#include <texturemanager.h>

class Sprite {
 public:
  Sprite( int frameSize, int d, TextureManager && t );
  virtual ~Sprite();
  void AddFrame( int x, int y, int w, int h ) ;
  void AddFrame( SDL_Rect r ) ;
  void Render( int x, int y, double rotate, SDL_RendererFlip flip ) ;
  void Render( int x, int y, int frame, double rotate, SDL_RendererFlip flip ) ;
  void SetDuration( int d ) ;
  void SetRepeatFrame( int frameNum ) ;
 protected:

 private:
  int length = 0 ;
  int duration = 0 ;
  int currentFrame = 0 ;
  int lastFrameTime = 0 ;
  int repeatFrame = 0 ;
  std::vector<SDL_Rect> frameList ;
  TextureManager srcSheet ;
};

#endif // SPRITE_H
