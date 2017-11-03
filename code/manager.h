#include <SDL.h>
#include <iostream>
#include <string>

#include "ioManager.h"
#include "clock.h"
#include "gamedata.h"
#include "world.h"
#include "viewport.h"
#include "spriteFactory.h"
#include "toyBox.h"
#include "menuItemsManager.h"

class Manager {
public:
  Manager ();
  ~Manager ();
  void play();
  
  void resetViewPort();

private:
  const bool env;
  const Gamedata* gdata;
  const IOManager& io;
  Clock& clock;
  ToyBox tb;

  SDL_Surface *screen;
  
  SDL_Surface * const bgSurface;
  const Frame background;
  SDL_Surface * const fgSurface;
  const Frame foreground;
  
  World backWorld;
  World frontWorld;
  
  Viewport& viewport;
  
  Uint32 total_ticks;
  
  void initSprites();
  void gameReset();

  Manager(const Manager&);
  Manager& operator=(const Manager&);
};

