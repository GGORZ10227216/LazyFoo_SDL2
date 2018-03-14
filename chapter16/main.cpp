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
TTF_Font* gFont = NULL ;

enum RECTSTYLE { FILL, OUTLINE } ;

void DrawRect( SDL_Rect const& rect, short const& r, short const& g, short const& b, const short style ) {
  SDL_SetRenderDrawColor( gRenderer, r, g, b, 0xFF ) ;
  if ( style == RECTSTYLE::FILL )
    SDL_RenderFillRect( gRenderer, &rect ) ;
  else
    SDL_RenderDrawRect( gRenderer, &rect ) ;
  return ;
} // DrawRect()

void MainLoop() {
  bool quit = false ;
  SDL_Event e ;

  int fpsCounter = 0, lastCheckTime = 0 ;
  int offsetX = 0 ;

  SDL_Color textColor = { 0, 0, 255 };
  gFont = SDL_Utility::LoadTureTypeFont( "resource/ttf/Tangerine-Regular.ttf", 28 ) ;
  TTF_Font* biggerFont = SDL_Utility::LoadTureTypeFont( "resource/ttf/Tangerine-Regular.ttf", 140 ) ;
  TextureManager helloworld( "Hello, world!!", textColor, gFont, gRenderer ) ;
  TextureManager helloworld2( "Hello, world!!", textColor, biggerFont, gRenderer ) ;

  while ( !quit ) {
    while ( SDL_PollEvent( &e ) != 0 ) {
      switch ( e.type ) {
      case SDL_QUIT :
        quit = true ;
        break ;
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
        case SDLK_q:
          break;
        default :
          break ;
        } // switch
      } // inner switch
      break ;
      default :
        break ;
      } // switch
    } // while

    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF ) ;
    SDL_RenderClear( gRenderer ) ;
    SDL_RenderSetViewport( gRenderer, NULL ) ;

    helloworld.RenderUsingCenterPoint( 640, 180, NULL, 5 ) ;
    helloworld2.RenderUsingCenterPoint( 640, 540, NULL, 1 ) ;

    SDL_RenderPresent( gRenderer ) ;
    if ( lastCheckTime == 0 || SDL_GetTicks() - lastCheckTime >= 1000 ) {
      cout << fpsCounter << '\r' ;
      fpsCounter = 0 ;
      lastCheckTime = SDL_GetTicks() ;
    } // if
    else
      ++fpsCounter ;
  } // while

  delete biggerFont ;
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
    if ( TTF_Init() == -1 ) {
      cerr << "SDL_TTF could not initialize! SDL_TTF Error: "
           << TTF_GetError() << endl ;
      return -2 ;
    } // if

    gMainWindow = SDL_CreateWindow( "TrueType Font", SDL_WINDOWPOS_UNDEFINED
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
