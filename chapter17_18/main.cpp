#include <iostream>
#include <string>
#include <cmath>

#include <SDL_Utility.h>
#include <Sprite.h>

using namespace std;

const int SCREEN_W = 1280 ;
const int SCREEN_H = 720 ;

SDL_Window* gMainWindow = NULL ;
SDL_Surface* gSurface = NULL ;
SDL_Renderer* gRenderer = NULL ;
const Uint8* currentKeyStates = NULL ;
bool quit = false ;

enum RECTSTYLE { FILL, OUTLINE } ;

void DrawRect( SDL_Rect const& rect, short const& r, short const& g, short const& b, const short style ) {
  SDL_SetRenderDrawColor( gRenderer, r, g, b, 0xFF ) ;
  if ( style == RECTSTYLE::FILL )
    SDL_RenderFillRect( gRenderer, &rect ) ;
  else
    SDL_RenderDrawRect( gRenderer, &rect ) ;
  return ;
} // DrawRect()

void Draw() {

} // Draw()

void EventPolling( SDL_Event & e ) {
  while ( SDL_PollEvent( &e ) != 0 ) {
    currentKeyStates = SDL_GetKeyboardState( NULL );
    switch ( e.type ) {
    case SDL_QUIT :
      quit = true ;
      break ;
    /*
    case SDL_KEYDOWN : {
      switch ( e.key.keysym.sym ) {
      case SDLK_UP :
        break ;
      case SDLK_DOWN:
        break ;
      case SDLK_LEFT:
        break ;
      case SDLK_RIGHT:
        break ;
      default :
        break ;
      } // switch
    } // inner case
    break ;
    */
    case SDL_MOUSEMOTION : {
      int x, y ;
      SDL_GetMouseState( &x, &y ) ;
      cout << x << " " << y << endl ;
    } // inner switch
    break ;
    case SDL_MOUSEBUTTONDOWN :
      cout << "Mouse Down!" << endl ;
      break ;
    case SDL_MOUSEBUTTONUP :
      cout << "Mouse Up!" << endl ;
      break ;
    default :
      break ;
    } // switch
  } // while
} // EventPolling()

void ProcessLogic() {
  if( currentKeyStates[ SDL_SCANCODE_UP ] ) {
    cout << "Up" << endl ;
  } // if
  else if( currentKeyStates[ SDL_SCANCODE_DOWN ] ) {
    cout << "Down" << endl ;
  } // else if
  else if( currentKeyStates[ SDL_SCANCODE_LEFT ] ) {
    cout << "Left" << endl ;
  } // else if
  else if( currentKeyStates[ SDL_SCANCODE_RIGHT ] ) {
    cout << "Right" << endl ;
  } // else if
} // ProcessLogic()

void MainLoop() {
  SDL_Event e ;

  int fpsCounter = 0, lastCheckTime = 0 ;
  while ( !quit ) {

    EventPolling( e ) ;
    ProcessLogic() ;

    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF ) ;
    SDL_RenderClear( gRenderer ) ;
    SDL_RenderSetViewport( gRenderer, NULL ) ;

    Draw() ;

    SDL_RenderPresent( gRenderer ) ;
    if ( lastCheckTime == 0 || SDL_GetTicks() - lastCheckTime >= 1000 ) {
      cout << fpsCounter << '\r' ;
      fpsCounter = 0 ;
      lastCheckTime = SDL_GetTicks() ;
    } // if
    else
      ++fpsCounter ;
  } // while
} // MainLoop()

int main( int argc, char* argv[] ) {
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    cerr << "SDL could not initialize! SDL_Error: "
         << SDL_GetError() << endl ;
  } // if
  else {
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG ;
    if ( IMG_Init( imgFlags ) != imgFlags ) {
      cerr << "SDL_image could not initialize! SDL_image Error: "
           << IMG_GetError() << endl ;
      return -1 ;
    } // if

    gMainWindow = SDL_CreateWindow( "Mouse event and Key state", SDL_WINDOWPOS_UNDEFINED
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
      gRenderer = SDL_Utility::InitRenderer( gMainWindow ) ;

      MainLoop() ;

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
