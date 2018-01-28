#include <iostream>
#include <string>

#include <SDL.h>

using namespace std;

const int SCREEN_W = 1280 ;
const int SCREEN_H = 720 ;

bool LoadMedia( const char* path, SDL_Surface*& dst ) {
  bool result = false ;
  dst = SDL_LoadBMP( path ) ;
  if ( dst == NULL ) {
    cerr << "Unable to load image \"" << path << "\" SDL_Error: "
         << SDL_GetError() << endl ;
  } // if
  else
    result = true ;

  return result ;
} // LoadMedia()

int main( int argc, char* argv[] ) {
    SDL_Window* window = NULL ;
    SDL_Surface* screenSurface = NULL ;

    if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
      cerr << "SDL could not initialize! SDL_Error: "
           << SDL_GetError() << endl ;
    } // if
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
        SDL_Surface* bmpSurface = NULL ;
        if ( LoadMedia( "test.bmp", bmpSurface ) ) {
          SDL_BlitSurface( bmpSurface, NULL, screenSurface, NULL ) ;
          SDL_UpdateWindowSurface( window ) ;
          SDL_FreeSurface( bmpSurface ) ;
          SDL_Delay( 2000 ) ;
        } // if
        else
          cerr << "Failed to load media." << endl ;
      } // else

      SDL_DestroyWindow( window ) ;
      SDL_Quit() ;
    } // else

    return 0;
}
