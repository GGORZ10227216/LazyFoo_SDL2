#ifndef SDL_UTILITY_H
#define SDL_UTILITY_H

#include <string>

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>

class SDL_Utility {
 public:
  static SDL_Surface* LoadSurface( const char* path, SDL_PixelFormat* surFormat ) ;
  static SDL_Texture* LoadTexture( SDL_Surface* const src, SDL_Renderer* renderer ) ;
  static SDL_Texture* LoadTextureFromFile( const std::string& p, SDL_PixelFormat* sf, SDL_Renderer* r ) ;
  static SDL_Renderer* InitRenderer( SDL_Window* targetWin ) ;
  static TTF_Font* LoadTureTypeFont( const char* path, uint8_t px ) ;
 protected:

 private:
  SDL_Utility();
};

#endif // SDL_UTILITY_H
