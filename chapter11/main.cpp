#include <iostream>
#include <string>
#include <cmath>

#include <SDL_Utility.h>
#include <texturemanager.h>

using namespace std;

const int SCREEN_W = 1024 ;
const int SCREEN_H = 768 ;

SDL_Window* gMainWindow = NULL ;
SDL_Surface* gSurface = NULL ;
SDL_Renderer* gRenderer = NULL ;

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

  SDL_Surface* spriteSheet = SDL_Utility::LoadSurface( "resource/png/3873.png", gSurface->format ) ;
  SDL_SetColorKey( spriteSheet, SDL_TRUE, SDL_MapRGB( gSurface->format, 0x80, 0x00, 0x00 ) ) ;

  TextureManager spriteTexture( spriteSheet, gRenderer ) ;
  TextureManager background( "resource/png/SaveHouse.png",
                             gSurface->format,
                             gRenderer
                           ) ;

  SDL_Rect sprite_IDLE = { 11, 95, 15, 45 } ;
  SDL_Rect sprite_TALK = { 200, 158, 20, 45 } ;
  int fpsCounter = 0, lastCheckTime = 0 ;
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

    background.Render() ;

    spriteTexture.Render( 430, 440, &sprite_IDLE, 4 ) ;
    spriteTexture.Render( 600, 440, &sprite_TALK, 4 ) ;
    SDL_RenderPresent( gRenderer ) ;

    if ( lastCheckTime == 0 || SDL_GetTicks() - lastCheckTime >= 1000 ) {
      cout << fpsCounter << '\r' ;
      fpsCounter = 0 ;
      lastCheckTime = SDL_GetTicks() ;
    } // if
    else
      ++fpsCounter ;

    SDL_Delay( 16 ) ;
  } // while
} // MainLoop()

int main( int argc, char* argv[] ) {
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    cerr << "SDL could not initialize! SDL_Error: "
         << SDL_GetError() << endl ;
  } // if
  else {
    int imgFlags = IMG_INIT_JPG ;
    if ( IMG_Init( imgFlags ) != imgFlags ) {
      cerr << "SDL_image could not initialize! SDL_image Error: "
           << IMG_GetError() << endl ;
    } // if
    else {
      gMainWindow = SDL_CreateWindow( "Clip Rendering and Sprite Sheets", SDL_WINDOWPOS_UNDEFINED
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
  } // else

  return 0;
}
