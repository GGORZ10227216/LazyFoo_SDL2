#include "SDL_Utility.h"

#include <iostream>

SDL_Utility::SDL_Utility()
{
  //ctor
}

SDL_Surface* SDL_Utility::LoadSurface( const char* path, SDL_PixelFormat* surFormat ) {
  SDL_Surface* result = IMG_Load( path ) ;
  if ( result == NULL ) {
    std::cerr << "Unable to load image \"" << path << "\" SDL_Error: "
              << SDL_GetError() << std::endl ;
    return NULL ;
  } // if
  else {
    SDL_Surface* optimized = SDL_ConvertSurface( result, surFormat, NULL ) ;
    SDL_FreeSurface( result ) ;
    return optimized ;
  } // else

  return NULL ;
} // LoadSurface()

SDL_Texture* SDL_Utility::LoadTexture( SDL_Surface* const src, SDL_Renderer* renderer ) {
  SDL_Texture* result = SDL_CreateTextureFromSurface( renderer, src ) ;
  if ( result == NULL ) {
    std::cerr << "Could not load texture from surface: "
              << SDL_GetError() << std::endl ;
  } // if

  return result ;
} // LoadTexture()

SDL_Texture* SDL_Utility::LoadTextureFromFile( const std::string& p, SDL_PixelFormat* sf, SDL_Renderer* r ) {
  SDL_Surface* temp = LoadSurface( p.c_str(), sf ) ;
  SDL_Texture* result = LoadTexture( temp, r ) ;
  SDL_FreeSurface( temp ) ;
  return result ;
} // LoadTextureFromFile()

SDL_Renderer* SDL_Utility::InitRenderer( SDL_Window* targetWin ) {
  SDL_Renderer* result = SDL_CreateRenderer( targetWin, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC ) ;
  if ( result == NULL ) {
    std::cerr << "Renderer could not be created! SDL Error: "
              << SDL_GetError() << std::endl ;
  } // if
  else {
    SDL_SetRenderDrawColor( result, 0xFF, 0xFF, 0xFF, 0xFF ) ;
  } // else

  return result ;
} // InitRenderer()
