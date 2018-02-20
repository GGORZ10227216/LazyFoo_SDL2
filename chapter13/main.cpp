#include <iostream>
#include <string>
#include <cmath>

#include <SDL_Utility.h>
#include <texturemanager.h>

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

void MainLoop() {
  bool quit = false ;
  SDL_Event e ;

  TextureManager noon( "resource/jpg/noon.jpg", gSurface->format, gRenderer ) ;
  noon.SetBlendMode( SDL_BLENDMODE_BLEND ) ;
  TextureManager afternoon( "resource/jpg/afternoon.jpg", gSurface->format, gRenderer ) ;
  afternoon.SetBlendMode( SDL_BLENDMODE_BLEND ) ;
  TextureManager night( "resource/jpg/night.jpg", gSurface->format, gRenderer ) ;
  night.SetBlendMode( SDL_BLENDMODE_BLEND ) ;

  int fpsCounter = 0, lastCheckTime = 0 ;
  float t1 = 0, t2 = 0, t3 = 0 ;
  while ( !quit ) {
    t1 = sin( (float)SDL_GetTicks() / 100 * 3.14 / 180 ) ;
    t2 = sin( (float)SDL_GetTicks() / 100 * 3.14 / 180 + 90 ) ;
    t3 = sin( (float)SDL_GetTicks() / 100 * 3.14 / 180 + 180 ) ;
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

    noon.SetAlpha( t1 >= 0 ? t1 * 255 : 0 ) ;
    noon.Render() ;
    afternoon.SetAlpha( t2 >= 0 ? t2 * 255 : 0 ) ;
    afternoon.Render() ;
    night.SetAlpha( t3 >= 0 ? t3 * 255 : 0 ) ;
    night.Render() ;

    SDL_RenderPresent( gRenderer ) ;
    cout << t1 << " " << t2 << " " << t3 << '\r' ;
    if ( lastCheckTime == 0 || SDL_GetTicks() - lastCheckTime >= 1000 ) {
      // cout << fpsCounter << '\r' ;
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
    int imgFlags = IMG_INIT_JPG | IMG_INIT_PNG ;
    if ( IMG_Init( imgFlags ) != imgFlags ) {
      cerr << "SDL_image could not initialize! SDL_image Error: "
           << IMG_GetError() << endl ;
    } // if
    else {
      gMainWindow = SDL_CreateWindow( "Alpha Blending", SDL_WINDOWPOS_UNDEFINED
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
