#ifndef MENUMANAGER__H
#define MENUMANAGER__H

#include <SDL.h>
#include <iostream>
#include <string>
using std::cout; using std::endl; 
using std::string;

#include "manager.h"
#include "ioManager.h"
#include "parseXML.h"
#include "menu.h"
#include "menuItemsManager.h"
#include "clock.h"

class MenuManager {
public:
  MenuManager ();
  void play();
  int getNumberOfStars() const { return numberOfStars; }
  
  //added by Qiyue
  virtual ~MenuManager(){
    SDL_FreeSurface(bgSurface);
  }

private:
  bool env;
  const IOManager& io;
  const Clock& clock;

  ParseXML parser;

  SDL_Surface *screen;
  //SDL_Color bakColor;
  
  //added by Qiyue
  SDL_Surface * const bgSurface;
  
  Menu menu;
  int numberOfStars;

  void drawBackground() const;
  MenuManager(const MenuManager&);
  MenuManager& operator=(const MenuManager&);
};

#endif
