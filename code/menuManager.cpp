#include <cmath>
#include <sstream>
#include "menuManager.h"

MenuManager::MenuManager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  parser( "xmlSpec/menu.xml" ),
  screen( IOManager::getInstance().getScreen() ),
  bgSurface(io.loadAndSet(parser.getXmlStr("bgImage"), false)),
  menu(),
  numberOfStars(-1)
{ 
  atexit(SDL_Quit); 
}

//modified by Qiyue
void MenuManager::drawBackground() const {
  
  SDL_BlitSurface(bgSurface,NULL,screen,NULL);
}

void MenuManager::play() {
  bool keyCatch = false; // To get only 1 key per keydown
  SDL_Event event;
  bool done = false;
  bool returnKey = false;
  
  Manager man;
  MenuCredits mCredits;
  MenuHelp mHelp;
  MenuTutorial mTutorial;

  while ( not done ) {

    drawBackground();
    menu.draw();
    SDL_Flip(screen);

    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_RETURN : {
          if ( !keyCatch ) {
            menu.lightOn();
            returnKey = true;
          }
          break;
        }
        case SDLK_DOWN   : {
          if ( !keyCatch ) {
            menu.increment();
          }
          break;
        }
        case SDLK_UP   : {
          if ( !keyCatch ) {
            menu.decrement();
          }
          break;
        }
        default          : break;
      }
      keyCatch = true;
    }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
      if ( returnKey ) {
        returnKey = false;
        //cout << "Chosen: " << menu.getIconClicked() << endl;
        SDL_Delay(250);
        if ( menu.getIconClicked() == "Exit" ) {
          done = true;
          //exit(0);
        }
        else if ( menu.getIconClicked() == "Start Game" ) {
          //done = true;
          man.play();
          man.resetViewPort();
        }
        else if ( menu.getIconClicked() == "Tutorial" ) {
          mTutorial.play();
        }
        else if (menu.getIconClicked() == "Credits") {
          mCredits.play();
        }
        else if (menu.getIconClicked() == "Help") {
          mHelp.play();
        }
      }
      menu.lightOff();
    }
  }
}
