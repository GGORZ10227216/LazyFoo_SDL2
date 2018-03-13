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

enum RECTSTYLE { FILL, OUTLINE } ;

void DrawRect( SDL_Rect const& rect, short const& r, short const& g, short const& b, const short style ) {
  SDL_SetRenderDrawColor( gRenderer, r, g, b, 0xFF ) ;
  if ( style == RECTSTYLE::FILL )
    SDL_RenderFillRect( gRenderer, &rect ) ;
  else
    SDL_RenderDrawRect( gRenderer, &rect ) ;
  return ;
} // DrawRect()

void SetSpriteFrames( Sprite& s ) {
  SDL_Rect f1 = { 9,63, 14, 45 } ;
  SDL_Rect f2 = { 28,63, 13, 45 } ;
  SDL_Rect f3 = { 49,63, 15, 45 } ;
  SDL_Rect f4 = { 68,63, 19, 45 } ;
  SDL_Rect f5 = { 92,63, 28, 45 } ;
  SDL_Rect f6 = { 125,63, 23, 45 } ;
  SDL_Rect f7 = { 153,63, 23, 45 } ;
  SDL_Rect f8 = { 180,63, 27, 45 } ;
  SDL_Rect f9 = { 212,63, 27, 45 } ;
  SDL_Rect f10 = { 245,63, 26, 45 } ;
  SDL_Rect f11 = { 277,63, 26, 45 } ;
  SDL_Rect f12 = { 309,63, 28, 45 } ;
  SDL_Rect f13 = { 344,63, 30, 45 } ;
  SDL_Rect f14 = { 380,63, 25, 45 } ;
  SDL_Rect f15 = { 412,63, 25, 45 } ;
  SDL_Rect f16 = { 445,63, 21, 45 } ;
  SDL_Rect f17 = { 472,63, 20, 45 } ;
  SDL_Rect f18 = { 497,63, 19, 45 } ;
  SDL_Rect f19 = { 520,63, 20, 45 } ;
  SDL_Rect f20 = { 545,63, 26, 45 } ;
  s.AddFrame( f1 ) ;
  s.AddFrame( f2 ) ;
  s.AddFrame( f3 ) ;
  s.AddFrame( f4 ) ;
  s.AddFrame( f5 ) ;
  s.AddFrame( f6 ) ;
  s.AddFrame( f7 ) ;
  s.AddFrame( f8 ) ;
  s.AddFrame( f9 ) ;
  s.AddFrame( f10 ) ;
  s.AddFrame( f11 ) ;
  s.AddFrame( f12 ) ;
  s.AddFrame( f13 ) ;
  s.AddFrame( f14 ) ;
  s.AddFrame( f15 ) ;
  s.AddFrame( f16 ) ;
  s.AddFrame( f17 ) ;
  s.AddFrame( f18 ) ;
  s.AddFrame( f19 ) ;
  s.AddFrame( f20 ) ;
  s.SetRepeatFrame( 5 ) ;
} // SetSpriteFrames()

void MainLoop() {
  bool quit = false ;
  SDL_Event e ;

  SDL_Surface* sheetSurface = SDL_Utility::LoadSurface( "resource/png/CVSOTN_Maria.png", gSurface->format ) ;
  SDL_SetColorKey( sheetSurface, SDL_TRUE, SDL_MapRGB( sheetSurface->format, 0xC0, 0x00, 0xA8 ) );
  TextureManager sheetTexture( sheetSurface, gRenderer ) ;

  int fpsCounter = 0, lastCheckTime = 0 ;

  int duration = 50 ;
  Sprite test( 20, duration, std::move( sheetTexture ) ) ;
  SetSpriteFrames( test ) ;

  int currentFrame = 0 ;
  int offsetX = 0 ;
  while ( !quit ) {
    while ( SDL_PollEvent( &e ) != 0 ) {
      switch ( e.type ) {
      case SDL_QUIT :
        quit = true ;
        break ;
      case SDL_KEYDOWN : {
        switch ( e.key.keysym.sym ) {
        case SDLK_UP :
          ++currentFrame ;
          break ;
        case SDLK_DOWN:
          --currentFrame ;
          break ;
        case SDLK_LEFT:
          ++offsetX ;
          break ;
        case SDLK_RIGHT:
          --offsetX ;
          break ;
        case SDLK_q:
          break;
        default :
          break ;
        } // switch

        test.SetDuration( duration ) ;
      } // inner switch
      break ;
      default :
        break ;
      } // switch
    } // while

    SDL_SetRenderDrawColor( gRenderer, 0x00, 0x00, 0x00, 0xFF ) ;
    SDL_RenderClear( gRenderer ) ;
    SDL_RenderSetViewport( gRenderer, NULL ) ;

    test.Render( 640, 360, 0, SDL_FLIP_HORIZONTAL ) ;

    SDL_RenderPresent( gRenderer ) ;
    if ( lastCheckTime == 0 || SDL_GetTicks() - lastCheckTime >= 1000 ) {
      cout << fpsCounter << '\r' ;
      fpsCounter = 0 ;
      lastCheckTime = SDL_GetTicks() ;
    } // if
    else
      ++fpsCounter ;

    // SDL_Delay( 16 ) ;
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
    } // if
    else {
      gMainWindow = SDL_CreateWindow( "Animated Sprites and VSync", SDL_WINDOWPOS_UNDEFINED
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
