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
      SDL_Surface* defaultSurface = NULL ;
      SDL_Surface* upSurface = NULL ;
      SDL_Surface* downSurface = NULL ;
      SDL_Surface* leftSurface = NULL ;
      SDL_Surface* rightSurface = NULL ;

      if ( !LoadMedia( "test.bmp", defaultSurface ) )
        return -1 ;
      if ( !LoadMedia( "up.bmp", upSurface ) )
        return -1 ;
      if ( !LoadMedia( "down.bmp", downSurface ) )
        return -1 ;
      if ( !LoadMedia( "left.bmp", leftSurface ) )
        return -1 ;
      if ( !LoadMedia( "right.bmp", rightSurface ) )
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
          else if ( e.type == SDL_KEYDOWN ) {
            switch ( e.key.keysym.sym ) {
            case SDLK_UP :
              cSurface = upSurface ;
              break ;
            case SDLK_DOWN:
              cSurface = downSurface ;
              break ;
            case SDLK_LEFT:
              cSurface = leftSurface ;
              break ;
            case SDLK_RIGHT:
              cSurface = rightSurface ;
              break ;
            default :
              cSurface = defaultSurface ;
              break ;
            } // switch
          } // else if
        } // while

        SDL_BlitSurface( cSurface, NULL, screenSurface, NULL ) ;
        SDL_UpdateWindowSurface( window ) ;

        SDL_Delay( 20 ) ; // reduce CPU usage.
      } // while
    } // else

    SDL_DestroyWindow( window ) ;
    SDL_Quit() ;
  } // else

  return 0;
}
