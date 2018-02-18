#include "texturemanager.h"

#include <string>
#include <iostream>

TextureManager::TextureManager( const std::string& p, SDL_PixelFormat* sf, SDL_Renderer* r ) :
  mTexture( SDL_Utility::LoadTextureFromFile( p, sf, r ) ), render( r )
{
  int queryResult = SDL_QueryTexture( mTexture,
                                      &mTextureFormat,
                                      &accessMode,
                                      &mWidth,
                                      &mHeight
                                    ) ;
  if ( queryResult < 0 ) {
    std::cerr << "Failed to manage texture from path: " << p << "!" << std::endl
              << "SDL_Error: " << SDL_GetError() << std::endl ;
  } // if
}

TextureManager::TextureManager( SDL_Surface* const src, SDL_Renderer* r ) :
  mTexture( SDL_Utility::LoadTexture( src, r ) ), render( r )
{
  int queryResult = SDL_QueryTexture( mTexture,
                                      &mTextureFormat,
                                      &accessMode,
                                      &mWidth,
                                      &mHeight
                                    ) ;
  if ( queryResult < 0 ) {
    std::cerr << "Failed to manage texture from surface: " << src << "!" << std::endl
              << "SDL_Error: " << SDL_GetError() << std::endl ;
  } // if
}

TextureManager::~TextureManager()
{
  Free() ;
}

void TextureManager::Render() {
  SDL_RenderCopy( render, mTexture, NULL, NULL ) ;
} // Render()

void TextureManager::Render( const int x, const int y, SDL_Rect* src, int scale ) {
  SDL_Rect dst = { x, y, mWidth, mHeight } ;
  if ( src != NULL ) {
    dst.w = src->w * scale ;
    dst.h = src->h * scale ;
  } // if

  SDL_SetRenderDrawColor( render, 0xff, 0xff, 0x00, 0xFF ) ;
  SDL_RenderDrawRect( render, &dst ) ;

  SDL_RenderCopy( render, mTexture, src, &dst ) ;
  return ;
} // Render()

void TextureManager::Free() {
  if( mTexture != NULL ) {
    SDL_DestroyTexture( mTexture );
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  } // if

  return ;
} // Free()