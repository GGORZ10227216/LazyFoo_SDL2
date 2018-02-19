#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

// cpp native header
#include <string>

// c-style header
#include <SDL_Utility.h>

class TextureManager
{
public:
  // ctor & dtor
  TextureManager( const std::string& p, SDL_PixelFormat* sf, SDL_Renderer* r ) ;
  TextureManager( SDL_Surface* const src, SDL_Renderer* r ) ;
  virtual ~TextureManager();
  // pubilc method
  void Free() ;
  void Render() ;
  void Render( const int x, const int y, SDL_Rect* src, int scale ) ;
  void SetColor( uint8_t r, uint8_t g, uint8_t b ) ;
  // info getter
  int GetWidth() {
    return mWidth ;
  }
  int GetHeight() {
    return mHeight ;
  }
  // END OF DECORATION
protected:

private:
  SDL_Texture* mTexture = NULL ;
  SDL_Renderer* render = NULL ;
  uint32_t mTextureFormat = 0 ;
  int accessMode = SDL_TEXTUREACCESS_STATIC ;
  int mWidth = 0 ;
  int mHeight = 0 ;
};

#endif // TEXTUREMANAGER_H
