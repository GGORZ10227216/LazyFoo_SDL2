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

Mix_Music* gBGM = NULL ;
Mix_Chunk* gSFX = NULL ;
Mix_Chunk* gSFX2 = NULL ;

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
    switch ( e.type ) {
    case SDL_QUIT :
      quit = true ;
      break ;
    case SDL_KEYUP : {
      switch ( e.key.keysym.sym ) {
      case SDLK_UP :
        if( !Mix_PlayingMusic() ) {
          //Play the music
          Mix_PlayMusic( gBGM, -1 );
        } // if
        else {
          Mix_ResumeMusic() ;
        } // else
        break ;
      case SDLK_DOWN:
        if ( Mix_PlayingMusic() )
      Mix_PauseMusic();
        break ;
      case SDLK_LEFT:
        Mix_PlayChannel( -1, gSFX, 0 );
        break ;
      case SDLK_RIGHT:
        Mix_PlayChannel( -1, gSFX2, 0 );
        break ;
      default :
        break ;
      } // switch
    } // inner case
    break ;
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

void LoadResource() {
  gBGM = Mix_LoadMUS( "resource/mp3/Maid_with_the_Flaxen_Hair.mp3" ) ;
  gSFX = Mix_LoadWAV( "resource/wav/bird.wav" ) ;
  gSFX2 = Mix_LoadWAV( "resource/wav/wind.wav" ) ;
} // LoadResource()

void MainLoop() {
  SDL_Event e ;

  int fpsCounter = 0, lastCheckTime = 0 ;
  LoadResource() ;
  while ( !quit ) {

    EventPolling( e ) ;

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

  Mix_FreeMusic( gBGM ) ;
  Mix_FreeChunk( gSFX ) ;
  Mix_FreeChunk( gSFX2 ) ;
} // MainLoop()

int main( int argc, char* argv[] ) {
  if ( SDL_Init( SDL_INIT_VIDEO | SDL_INIT_AUDIO ) < 0 ) {
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
