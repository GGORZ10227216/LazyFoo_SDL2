#include <iostream>
#include <string>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_W = 1280 ;
const int SCREEN_H = 720 ;

SDL_Window* window = NULL ;
SDL_Surface* screenSurface = NULL ;

bool LoadSurface( const char* path, SDL_Surface*& dst ) {
  bool result = false ;
  dst = IMG_Load( path ) ;
  if ( dst == NULL ) {
    cerr << "Unable to load image \"" << path << "\" SDL_Error: "
         << SDL_GetError() << endl ;
  } // if
  else {
    result = true ;
    SDL_Surface* optimized = SDL_ConvertSurface( dst, screenSurface->format, NULL ) ;
    SDL_FreeSurface( dst ) ;
    dst = optimized ;
  } // else

  return result ;
} // LoadMedia()

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
      window = SDL_CreateWindow( "test", SDL_WINDOWPOS_UNDEFINED
                                 , SDL_WINDOWPOS_UNDEFINED
                                 , SCREEN_W
                                 , SCREEN_H
                                 , SDL_WINDOW_SHOWN
                               ) ;
      if ( window == NULL ) {
        cerr << "window could not be created! SDL_Error: "
             << SDL_GetError() << endl ;
      } // if
      else {
        screenSurface = SDL_GetWindowSurface( window ) ;
        // SDL_FillRect( screenSurface, NULL, SDL_MapRGB( screenSurface->format, 0xFF, 0xFF, 0xFF ) ) ;
        SDL_Surface* defaultSurface = NULL ;

        if ( !LoadSurface( "resource/png/test.png", defaultSurface ) )
          return -1 ;

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

          // SDL_BlitSurface( cSurface, NULL, screenSurface, NULL ) ;
          // Because bg.bmp is a non 16:9 image, we need to scaled it to fit our window.
          SDL_BlitScaled( cSurface, NULL, screenSurface, NULL ) ;
          SDL_UpdateWindowSurface( window ) ;

          SDL_Delay( 20 ) ; // reduce CPU usage.
        } // while
      } // else

      SDL_DestroyWindow( window ) ;
      SDL_Quit() ;
    } // else
  } // else

  return 0;
}
