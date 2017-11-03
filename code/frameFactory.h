#ifndef FRAMEFACTORY__H
#define FRAMEFACTORY__H

#include <iostream>
#include <string>
using std::string;
#include <map>
#include <algorithm>
#include "gamedata.h"
#include "frame.h"
#include "lsystem.h"

class FrameFactory {
public:
  static FrameFactory* getInstance();
  ~FrameFactory();

  // Must pass both width and height here because the sprite might
  // be embedded in a sprite sheet; i.e., only part of the surface.
  Frame* getFrame(const string& filename, Uint16 width, Uint16 height,
      Sint16 src_x, Sint16 src_y, bool setcolorkey=true);
      
  Frame* getLsystemFrame(const string& filename, Uint16 width, Uint16 height,
      Sint16 src_x, Sint16 src_y);
private:
  static FrameFactory* instance;
  const Gamedata* gdata;
  
  FrameFactory() : gdata(Gamedata::getInstance()), frames( std::map<string, Frame*>() ) {}
  std::map<string, Frame*> frames;
  

  FrameFactory(const FrameFactory&);
  FrameFactory& operator=(const FrameFactory&);
};

#endif
