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

TextureManager::TextureManager( TextureManager && rhs )
{
    this->mTexture = rhs.mTexture ;
    rhs.mTexture = NULL ;
    this->render = rhs.render ;
    rhs.mTexture = NULL ;
    this->mTextureFormat = rhs.mTextureFormat ;
    this->accessMode = rhs.accessMode ;
    this->mWidth = rhs.mWidth ;
    this->mHeight = rhs.mHeight ;
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

void TextureManager::RenderUsingCenterPoint( const int x, const int y, SDL_Rect* src, int scale ) {
  SDL_Rect dst = { 0, 0, mWidth, mHeight } ;
  if ( src != NULL ) {
    dst.w = src->w * scale ;
    dst.h = src->h * scale ;
  } // if

  dst.x = x - ( dst.w / 2 ) ;
  dst.y = y - ( dst.h / 2 ) ;

  SDL_SetRenderDrawColor( render, 0xff, 0xff, 0x00, 0xFF ) ;
  SDL_RenderDrawRect( render, &dst ) ;
  SDL_RenderCopy( render, mTexture, src, &dst ) ;


  SDL_RenderDrawLine( render, dst.x, dst.y + ( dst.h / 2 ),
                      dst.x + dst.w, dst.y + ( dst.h / 2 ) ) ;
  SDL_RenderDrawLine( render, dst.x + ( dst.w / 2 ), dst.y ,
                              dst.x + ( dst.w / 2 ), dst.y + dst.h ) ;

  return ;
} // Render()

void TextureManager::SetColor( uint8_t r, uint8_t g, uint8_t b ) {
  SDL_SetTextureColorMod( mTexture, r, g, b );
  return ;
} // SetColor()

void TextureManager::SetBlendMode( const SDL_BlendMode& blending )
{
    SDL_SetTextureBlendMode( mTexture, blending );
}

void TextureManager::SetAlpha( uint8_t alpha )
{
    SDL_SetTextureAlphaMod( mTexture, alpha );
}

void TextureManager::Free() {
  if( mTexture != NULL ) {
    SDL_DestroyTexture( mTexture );
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
  } // if

  return ;
} // Free()
