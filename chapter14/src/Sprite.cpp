#include "Sprite.h"

#include <iostream>

Sprite::Sprite( int frameSize, int d, TextureManager && t ) :
  length( frameSize ), duration( d ), srcSheet( std::move( t ) )
{
}

void Sprite::AddFrame( int x, int y , int w, int h ) {
  SDL_Rect tempRect = { x, y, w, h } ;
  AddFrame( tempRect ) ;
  return ;
} // AddFrame()

void Sprite::AddFrame( SDL_Rect r ) {
  frameList.push_back( r ) ;
} // Sprite()

void Sprite::SetRepeatFrame( int frameNum ) {
  repeatFrame = frameNum ;
} // SetRepeatFrame()

void Sprite::SetDuration( int d ) {
  duration = d ;
} // SetDuration()

void Sprite::Render( int x, int y ) {
  if ( length == 0 )
    return ;

  uint32_t currentTime = SDL_GetTicks() ;
  if ( lastFrameTime == 0 ) {
    lastFrameTime = currentTime ;
  } // if
  else {
    if ( currentTime - lastFrameTime > duration ) {

      ++ currentFrame ;
      if ( currentFrame == length )
        currentFrame = ( currentFrame % length ) + repeatFrame ;
      lastFrameTime = currentTime ;
    } // if
  } // else

  srcSheet.RenderUsingCenterPoint( x, y, &( frameList.at( currentFrame ) ), 4 ) ;
} // Render()

void Sprite::Render( int x, int y, int frame ) {
  srcSheet.RenderUsingCenterPoint( x, y, &( frameList.at( frame ) ), 4 ) ;
} // Render()

Sprite::~Sprite() {
  //dtor
}
