#include <cmath>
#include <sstream>
#include "menuItemsManager.h"

//implements of base class--------------------------------------------

BaseItem::BaseItem() :
  //clock( Clock::getInstance() ),
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  io(IOManager::getInstance()),
  screen( io.getScreen() )
{ 
  atexit(SDL_Quit); 
}

//implements of child classes--------------------------------------------

//MenuCredits************************************************************

MenuCredits::MenuCredits() :
  BaseItem(),
  creditsSurface(io.loadAndSet(Gamedata::getInstance()->getXmlStr("creditsScreen"), false))
{ 
  atexit(SDL_Quit); 
}

void MenuCredits::drawBackground() const{
  SDL_BlitSurface(creditsSurface,NULL,screen,NULL);
}

void MenuCredits::drawCredits() const{
  io.printMessageCenteredAt("Game created by:",130);
  io.printMessageCenteredAt("Qiyue Sheng",150);
  io.printMessageCenteredAt("Music From:",210);
  io.printMessageCenteredAt("Game 'Metal Slug' stage#1",230);
  io.printMessageCenteredAt("Sprite Images From:",290);
  io.printMessageCenteredAt("http://spriters-resource.com/",310);
  
  io.printMessageCenteredAt("Press [ESC] to return to previous menu",380);
}

void MenuCredits::play() {
  bool keyCatch = false; // To get only 1 key per keydown
  SDL_Event event;
  bool done = false;

  while ( not done ) {

    drawBackground();
    drawCredits();
    SDL_Flip(screen);

    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_RETURN : {
          if ( !keyCatch ) {
          
          }
          break;
        }

        default          : break;
      }
      keyCatch = true;
    }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
    }
  }
}

//menuHelp************************************************************
MenuHelp::MenuHelp() :
  BaseItem(),
  helpSurface(io.loadAndSet(Gamedata::getInstance()->getXmlStr("helpScreen"), false))
{ 
  atexit(SDL_Quit); 
}

void MenuHelp::drawBackground() const{
  SDL_BlitSurface(helpSurface,NULL,screen,NULL);
}

void MenuHelp::drawHelp() const{
  io.printMessageAt("Press a / SPACE to shoot!",280, 100);
  io.printMessageAt("Press r to track the Player",280, 130);
  io.printMessageAt("Press t to switch and track other sprites",280, 160);
  io.printMessageAt("Press p to pause game", 280,190);
  io.printMessageAt("Press m to pause the music", 280,220);
  io.printMessageAt("Press UP / DOWN / LEFT / RIGHT to control player", 280,250);
  io.printMessageAt("Press F1 to show / hide help info", 280,280);
  io.printMessageAt("Press q / ESC to quit game", 280,310);
  
  io.printMessageCenteredAt("Press [ESC] to return to previous menu",480);
}

void MenuHelp::play() {
  bool keyCatch = false; // To get only 1 key per keydown
  SDL_Event event;
  bool done = false;

  while ( not done ) {

    drawBackground();
    drawHelp();
    SDL_Flip(screen);

    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_RETURN : {
          if ( !keyCatch ) {
          
          }
          break;
        }

        default          : break;
      }
      keyCatch = true;
    }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
    }
  }
}

//MenuTutorial************************************************************
MenuTutorial::MenuTutorial() :
  BaseItem(),
  tutorialSurface(io.loadAndSet(Gamedata::getInstance()->getXmlStr("tutorialScreen"), false))
{ 
  atexit(SDL_Quit); 
}

void MenuTutorial::drawBackground() const{
  SDL_BlitSurface(tutorialSurface,NULL,screen,NULL);
}

void MenuTutorial::play() {
  bool keyCatch = false; // To get only 1 key per keydown
  SDL_Event event;
  bool done = false;

  while ( not done ) {

    drawBackground();
    SDL_Flip(screen);

    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { break; }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : done = true; break;
        case SDLK_q      : done = true; break;
        case SDLK_RETURN : {
          if ( !keyCatch ) {
          
          }
          break;
        }

        default          : break;
      }
      keyCatch = true;
    }
    if(event.type == SDL_KEYUP) { 
      keyCatch = false; 
    }
  }
}


//WinScreen************************************************************
WinScreen::WinScreen() :
  BaseItem(),
  winSurface(io.loadAndSet(Gamedata::getInstance()->getXmlStr("winScreen"), false)),
  ticks(0)
{ 
  atexit(SDL_Quit); 
}

void WinScreen::drawBackground() const{
  SDL_BlitSurface(winSurface,NULL,screen,NULL);
}

void WinScreen::play() {
  SDL_Event event;
  Uint32 start_ticks = SDL_GetTicks();
  Uint32 curr_ticks = 0;

  bool done = false;

  drawBackground();
  SDL_Flip(screen);
  
  while ( ! done ) {

    curr_ticks = SDL_GetTicks();
    ticks = curr_ticks - start_ticks;
    if ( ticks > 4000 ) {
      done = true;
    }
     
     Uint8 *keystate = SDL_GetKeyState(NULL);
     if ( SDL_PollEvent(&event) )
     switch (event.type) {
       case SDL_QUIT: {
           done = true;
           break;
       }
       case SDL_KEYDOWN: {
         if (keystate[SDLK_q] || keystate[SDLK_ESCAPE]) {
           done = true;
           break;
         }
         if (keystate[SDLK_p]) {
           done = true;
           break;
         }
       }
     }
  }
}


//OverScreen************************************************************
OverScreen::OverScreen() :
  BaseItem(),
  overSurface(io.loadAndSet(Gamedata::getInstance()->getXmlStr("overScreen"), false)),
  ticks(0)
{ 
  atexit(SDL_Quit); 
}

void OverScreen::drawBackground() const{
  SDL_BlitSurface(overSurface,NULL,screen,NULL);
}

void OverScreen::play() {
  SDL_Event event;
  Uint32 start_ticks = SDL_GetTicks();
  Uint32 curr_ticks = 0;

  bool done = false;
  drawBackground();
  SDL_Flip(screen);
  
  while ( ! done ) {

    curr_ticks = SDL_GetTicks();
    ticks = curr_ticks - start_ticks;
    if ( ticks > 4000 ) {
      done = true;
    }
     
     Uint8 *keystate = SDL_GetKeyState(NULL);
     if ( SDL_PollEvent(&event) )
     switch (event.type) {
       case SDL_QUIT: {
           done = true;
           break;
       }
       case SDL_KEYDOWN: {
         if (keystate[SDLK_q] || keystate[SDLK_ESCAPE]) {
           done = true;
           break;
         }
         if (keystate[SDLK_p]) {
           done = true;
           break;
         }
       }
     }
  }
}
