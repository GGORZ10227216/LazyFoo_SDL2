#include <iostream>
#include <string>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

#define deltaX 0.01635991820040899795501022494888
#define deltaY 0.015

using namespace std;

const int SCREEN_W = 1024 ;
const int SCREEN_H = 720 ;

SDL_Window* gMainWindow = NULL ;
SDL_Surface* gSurface = NULL ;
SDL_Renderer* gRenderer = NULL ;

enum RECTSTYLE { FILL, OUTLINE } ;

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
  float startTheta = 0 ;

  SDL_Surface* hugeMap = LoadSurface( "resource/jpg/castlevsotnMap.jpg" ) ;
  SDL_Texture* hugeTexture = LoadTexture( hugeMap ) ;
  SDL_FreeSurface( hugeMap ) ;

  SDL_Rect miniMap = { 0, 0, SCREEN_W / 4, SCREEN_H / 4 } ;
  SDL_Rect camera = { 20, 8790, 512, 360 } ;
  SDL_Rect camView = { 0, 132, 8, 5 } ;

  float trueViewX = 0.f, trueViewY = 132.f ;
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
              camera.y -= 10 ;
              trueViewY -= deltaY * 10 ;
              if ( trueViewY != camView.y )
                camView.y = (int)trueViewY ;
              break ;
            case SDLK_DOWN:
              camera.y += 10 ;
              trueViewY += deltaY * 10 ;
              if ( trueViewY != camView.y )
                camView.y = (int)trueViewY ;
              break ;
            case SDLK_LEFT:
              camera.x -= 10 ;
              trueViewX -= deltaX * 10 ;
              if ( trueViewX != camView.x )
                camView.x = (int)trueViewX ;
              break ;
            case SDLK_RIGHT:
              camera.x += 10 ;
              trueViewX += deltaX * 10 ;
              if ( trueViewX != camView.x )
                camView.x = (int)trueViewX ;
              break ;
            default :
              break ;
          } // switch

          // cout << camera.x << " " << camera.y << '\r' ;
        } // inner switch
        break ;
      default :
        // cout << e.type << endl ;
        break ;
      } // switch
    } // while

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ) ;
    SDL_RenderClear( gRenderer ) ;

    SDL_RenderCopy( gRenderer, hugeTexture, &camera, NULL ) ;

    SDL_RenderSetViewport( gRenderer, &miniMap );
      SDL_RenderCopy( gRenderer, hugeTexture, NULL, NULL ) ;
      DrawRect( camView, 0xFF, 0x00, 0x00, RECTSTYLE::OUTLINE ) ;
    SDL_RenderSetViewport( gRenderer, NULL );

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
      gMainWindow = SDL_CreateWindow( "Viewport", SDL_WINDOWPOS_UNDEFINED
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
