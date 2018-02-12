#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_W = 1280 ;
const int SCREEN_H = 720 ;

SDL_Window* gMainWindow = NULL ;
SDL_Surface* gSurface = NULL ;
SDL_Renderer* gRenderer = NULL ;

SDL_Surface* LoadSurface( const char* path ) {
  SDL_Surface* result = IMG_Load( path ) ;
  if ( result == NULL ) {
    cerr << "Unable to load image \"" << path << "\" SDL_Error: "
         << SDL_GetError() << endl ;
    return NULL ;
  } // if
  else {
    SDL_Surface* optimized = SDL_ConvertSurface( result, gSurface->format, NULL ) ;
    SDL_FreeSurface( result ) ;
    return optimized ;
  } // else

  return NULL ;
} // LoadMedia()

SDL_Texture* LoadTexture( SDL_Surface* const src ) {
  SDL_Texture* result = SDL_CreateTextureFromSurface( gRenderer, src ) ;
  if ( result == NULL ) {
    cerr << "Could not load texture from surface: "
         << SDL_GetError() << endl ;
  } // if

  return result ;
} // LoadTexture()

SDL_Renderer* InitRenderer() {
  SDL_Renderer* result = SDL_CreateRenderer( gMainWindow, -1, SDL_RENDERER_ACCELERATED ) ;
  if ( result == NULL ) {
    cerr << "gRenderer could not be created! SDL Error: "
         << SDL_GetError() << endl ;
  } // if
  else {
    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ) ;
  } // else

  return result ;
} // InitRenderer()

int main( int argc, char* argv[] ) {

  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    cerr << "SDL could not initialize! SDL_Error: "
         << SDL_GetError() << endl ;
  } // if
  else {
    int imgFlags = IMG_INIT_PNG ;
    if ( IMG_Init( imgFlags ) != imgFlags ) {
      cerr << "SDL_image could not initialize! SDL_image Error: "
           << IMG_GetError() << endl ;
    }  // if
    else {
      gMainWindow = SDL_CreateWindow( "test", SDL_WINDOWPOS_UNDEFINED
                                 , SDL_WINDOWPOS_UNDEFINED
                                 , SCREEN_W
                                 , SCREEN_H
                                 , SDL_WINDOW_SHOWN
                               ) ;

      if ( gMainWindow == NULL ) {
        cerr << "gMainWindow could not be created! SDL_Error: "
             << SDL_GetError() << endl ;
      } // if
      else {
        gSurface = SDL_GetWindowSurface( gMainWindow ) ;
        gRenderer = InitRenderer() ;
        // SDL_FillRect( gSurface, NULL, SDL_MapRGB( gSurface->format, 0xFF, 0xFF, 0xFF ) ) ;
        SDL_Surface* defaultSurface = NULL ;
        SDL_Texture* texture = NULL ;

        defaultSurface = LoadSurface( "resource/bmp/down.bmp" ) ;
        if ( defaultSurface == NULL )
          return -1 ;

        texture = LoadTexture( defaultSurface ) ;
        SDL_FreeSurface( defaultSurface ) ;

        bool quit = false ;
        SDL_Event e ;
        SDL_Surface* cSurface = defaultSurface ;
        while( !quit ) {
          while ( SDL_PollEvent( &e ) != 0 ) {
            // Handling all input event here.
            if ( e.type == SDL_QUIT ) {
              quit = true ;
            } // if
          } // while

          SDL_RenderClear( gRenderer ) ;
          SDL_RenderCopy( gRenderer, texture, NULL, NULL ) ;
          SDL_RenderPresent( gRenderer ) ;

          SDL_Delay( 20 ) ; // reduce CPU usage.
        } // while

        SDL_DestroyTexture( texture ) ;
      } // else

      SDL_DestroyRenderer( gRenderer ) ;
      gRenderer = NULL ;
      SDL_DestroyWindow( gMainWindow ) ;
      gMainWindow = NULL ;

      IMG_Quit() ;
      SDL_Quit() ;
    } // else
  } // else

  return 0;
}
