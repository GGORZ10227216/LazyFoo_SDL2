#include <iostream>
#include <string>
#include <cmath>

#include <SDL.h>
#include <SDL_image.h>

using namespace std;

const int SCREEN_W = 1280 ;
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
  SDL_Rect lavenderRect = { SCREEN_W / 4, SCREEN_H / 4, SCREEN_W / 2, SCREEN_H / 2 } ;
  SDL_Rect cyanRect = { 60, 60, 300, 300 } ;

  unsigned long lastTick = 0 ;
  unsigned long thisTick = 0 ;
  float startTheta = 0 ;

  while ( !quit ) {
    while ( SDL_PollEvent( &e ) != 0 ) {
      switch ( e.type ) {
      case SDL_QUIT :
        quit = true ;
        break ;
      default :
        cout << e.type << endl ;
        break ;
      } // switch
    } // while

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0xFF, 0xFF, 0xFF ) ;
    SDL_RenderClear( gRenderer ) ;
    DrawRect( lavenderRect, 0xE6, 0XE6, 0XFA, RECTSTYLE::FILL ) ;
    DrawRect( cyanRect, 0xAF, 0XEE, 0XEE, RECTSTYLE::OUTLINE ) ;

    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0xFF, 0xFF );
    SDL_RenderDrawLine( gRenderer, 0, SCREEN_H / 2, SCREEN_W, SCREEN_H / 2 );

    SDL_SetRenderDrawColor( gRenderer, 0xFF, 0x45, 0x00, 0xFF );
    for ( float i = 0 ; i < SCREEN_W ; i += 1.f) {
      float dt = ( SDL_GetTicks() / 100 ) % 90 ;
      float sinValue = sin(i*3.14/180) * dt + SCREEN_H / 2 ;
      SDL_RenderDrawPoint( gRenderer, i, (int)sinValue ) ;
    } // for

    SDL_SetRenderDrawColor( gRenderer, 0x6B, 0x8E, 0x23, 0xFF );
    int a = SCREEN_W / 2, b = SCREEN_H / 2 ;

    startTheta += 0.01 ;
    startTheta = ( startTheta > 6.3 ) ? 0 : startTheta ;

    for ( float theta = startTheta ; theta < 6.3 ; theta += 0.001 ) {
      int x = ( int ) ( 300 * cos( theta ) + a ) ;
      int y = ( int ) ( 300 * sin( theta ) + b ) ;
      SDL_RenderDrawPoint( gRenderer, x, y ) ;
    } // for

    SDL_RenderPresent( gRenderer ) ;
    SDL_Delay( 20 ) ;
  } // while
} // MainLoop()

int main( int argc, char* argv[] ) {
  if ( SDL_Init( SDL_INIT_VIDEO ) < 0 ) {
    cerr << "SDL could not initialize! SDL_Error: "
         << SDL_GetError() << endl ;
  } // if
  else {
    gMainWindow = SDL_CreateWindow( "Geometry Rendering", SDL_WINDOWPOS_UNDEFINED
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
      SDL_Quit() ;
    } // else
  } // else

  return 0;
}
