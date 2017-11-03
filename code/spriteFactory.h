#ifndef SPRITEFACTORY__H
#define SPRITEFACTORY__H

#include <iostream>
#include <string>
using std::string;
#include <map>
#include <cmath>
#include <algorithm>
#include <sstream>
#include "sprite.h"
#include "frameFactory.h"
#include "gamedata.h"
#include "multisprite.h"
#include "smartSprite.h"

class SpriteFactory {
public:
  static SpriteFactory* getInstance();
  ~SpriteFactory();

  // Must pass both width and height here because the sprite might
  // be embedded in a sprite sheet; i.e., only part of the surface.
  Sprite* makeSprite(const string& name);
  MultiframeSprite* makeMultiframeSprite(const string& name);
  Sprite* makeLsystemSprite(const string& name);
  
  Sprite* makeSpecificSprite(const string& name, int xLoc, int yLoc, int xSpeed, int ySpeed);
  MultiframeSprite* makeSpecificMultiframeSprite(const string& name, int xLoc, int yLoc, int xSpeed, int ySpeed);
  
  SmartSprite* makeSmartSprite(const string& spriteName, const MultiframeSprite* msp);
  //overload
  SmartSprite* makeSmartSprite(const string& spriteName, const MultiframeSprite* msp,
                               int xLoc, int yLoc, int xSpeed, int ySpeed);
  
private:
  static SpriteFactory* instance;
  FrameFactory* ff;
  const Gamedata* gdata;

  //to reduce the code number
  //The core code for make single and multi sprite
  Sprite* makeSingleCore(const string& spriteName);
  MultiframeSprite* makeMultiCore(const string& spriteName);
  
  //the same funtion above with specify the x,y position and x,y speed
  Sprite* makeSpecificSingleCore(const string& spriteName, int xLoc, int yLoc, int xSpeed, int ySpeed);
  MultiframeSprite* makeSpecificMultiCore(const string& spriteName, int xLoc, int yLoc, int xSpeed, int ySpeed);

  SpriteFactory():ff(FrameFactory::getInstance()),
  gdata(Gamedata::getInstance()){}
  
  SpriteFactory(const SpriteFactory&);
  SpriteFactory& operator=(const SpriteFactory&);
};

#endif
