#include <iostream>
#include <string>

#include <SDL_Utility.h>
#include <LTimer.h>

using namespace std;

const int SCREEN_W = 1280 ;
const int SCREEN_H = 720 ;

SDL_Window* gMainWindow = NULL ;
SDL_Surface* gSurface = NULL ;
SDL_Renderer* gRenderer = NULL ;
const Uint8* currentKeyStates = NULL ;

bool quit = false ;
LTimer lt ;

enum RECTSTYLE { FILL, OUTLINE } ;

void DrawRect( SDL_Rect const& rect, short const& r, short const& g, short const& b, const short style ) {
  SDL_SetRenderDrawColor( gRenderer, r, g, b, 0xFF ) ;
  if ( style == RECTSTYLE::FILL )
    SDL_RenderFillRect( gRenderer, &rect ) ;
  else
    SDL_RenderDrawRect( gRenderer, &rect ) ;
  return ;
} // DrawRect()

inline void ReadableErr( const string& msg ) {
  cerr << msg << "SDL Error: " << SDL_GetError() << endl ;
} // ReadableErr()

void Draw() {

} // Draw()

void EventPolling( SDL_Event & e ) {
  while ( SDL_PollEvent( &e ) != 0 ) {
    switch ( e.type ) {
    case SDL_QUIT :
      quit = true ;
      break ;
    case SDL_KEYUP : {
      switch ( e.key.keysym.sym ) {
      case SDLK_UP :
        lt.start() ;
        break ;
      case SDLK_DOWN:
        lt.stop() ;
        break ;
      case SDLK_LEFT:
        lt.pause() ;
        break ;
      case SDLK_RIGHT:
        lt.unpause() ;
        break ;
      default :
        break ;
      } // switch
    } // inner case
    break ;
    case SDL_MOUSEBUTTONDOWN :
      break ;
    case SDL_MOUSEBUTTONUP :
      break ;
    default :
      break ;
    } // switch
  } // while
} // EventPolling()

void LoadResource() {
} // LoadResource()

void MainLoop() {
  SDL_Event e ;

  int fpsCounter = 0, lastCheckTime = 0 ;
  while ( !quit ) {

    EventPolling( e ) ;

    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF ) ;
    SDL_RenderClear( gRenderer ) ;
    SDL_RenderSetViewport( gRenderer, NULL ) ;

    cout << lt.getTicks() << '\r' ;

    SDL_RenderPresent( gRenderer ) ;
    if ( lastCheckTime == 0 || SDL_GetTicks() - lastCheckTime >= 1000 ) {
      //cout << fpsCounter << '\r' ;
      fpsCounter = 0 ;
      lastCheckTime = SDL_GetTicks() ;
    } // if
    else
      ++fpsCounter ;
  } // while
} // MainLoop()

int main( int argc, char* argv[] ) {
  if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_JOYSTICK | SDL_INIT_HAPTIC ) < 0 ) {
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

    if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 ) {
      cerr << "SDL_mixer could not initialize! SDL_mixer Error: "
           << Mix_GetError() << endl ;
      return -2 ;
    } // if

    gMainWindow = SDL_CreateWindow( "SDL_Mixer", SDL_WINDOWPOS_UNDEFINED
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
