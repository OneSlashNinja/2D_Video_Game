#ifndef MENUITEMS__H
#define MENUITEMS__H


#include <SDL.h>
#include <iostream>
#include <string>
using std::cout; using std::endl; 
using std::string;

#include "ioManager.h"
#include "clock.h"
#include "gamedata.h"

//All classes added by Qiyue

//The base class of the menu items unifiy the basic methods and drawBackground method
//The play method should be overridden by every child class

class BaseItem{
public:
  BaseItem ();
  virtual void play() = 0;
  
  virtual ~BaseItem(){}

//should be protected, or the child classed cannot access
protected:
  //const Clock& clock;
  bool env;

  const IOManager& io;
  SDL_Surface *screen;

  virtual void drawBackground() const = 0;
  
  BaseItem(const BaseItem&);
  BaseItem& operator=(const BaseItem&);
};

//MenuCredits---------------------------------------------------

class MenuCredits : BaseItem {
public:
  MenuCredits();
  void play();
  
  virtual ~MenuCredits(){
    SDL_FreeSurface(creditsSurface);
  }

private:

  SDL_Surface * creditsSurface;

  virtual void drawBackground() const;
  void drawCredits() const;
  
  MenuCredits(const MenuCredits&);
  MenuCredits& operator=(const MenuCredits&);
};

//MenuHelp--------------------------------------------------------

class MenuHelp : BaseItem {
public:
  MenuHelp();
  void play();
  
  virtual ~MenuHelp(){
    SDL_FreeSurface(helpSurface);
  }

private:

  SDL_Surface * helpSurface;

  virtual void drawBackground() const;
  void drawHelp() const;
  
  MenuHelp(const MenuHelp&);
  MenuHelp& operator=(const MenuHelp&);
};

//MenuTutorial------------------------------------------------------

class MenuTutorial : BaseItem {
public:
  MenuTutorial();
  void play();
  
  virtual ~MenuTutorial(){
    SDL_FreeSurface(tutorialSurface);
  }

private:

  SDL_Surface * tutorialSurface;

  virtual void drawBackground() const;
  
  MenuTutorial(const MenuTutorial&);
  MenuTutorial& operator=(const MenuTutorial&);
};

//WinScreen--------------------------------------------------------
class WinScreen : BaseItem {
public:
  WinScreen();
  void play();
  
  //added by Qiyue
  virtual ~WinScreen(){
    SDL_FreeSurface(winSurface);
  }

private:

  SDL_Surface * winSurface;
  Uint32 ticks;
  virtual void drawBackground() const;
  
  WinScreen(const WinScreen&);
  WinScreen& operator=(const WinScreen&);
};

//OverScreen-------------------------------------------------------
class OverScreen : BaseItem {
public:
  OverScreen();
  void play();
  
  //added by Qiyue
  virtual ~OverScreen(){
    SDL_FreeSurface(overSurface);
  }

private:

  SDL_Surface * overSurface;
  Uint32 ticks;
  virtual void drawBackground() const;
  
  OverScreen(const OverScreen&);
  OverScreen& operator=(const OverScreen&);
};


#endif
