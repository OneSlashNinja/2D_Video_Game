#ifndef SMARTSPRITE__H
#define SMARTSPRITE__H

#include <iostream>
#include "multisprite.h"
#include "ioManager.h"

class SmartSprite : public MultiframeSprite {
public:
  SmartSprite(const Vector2f& pos, const Vector2f& vel, 
               const string& n, const int numOfFrames, 
               const int frameIntervals, const MultiframeSprite * const p) :
   MultiframeSprite(pos, vel, n, numOfFrames, frameIntervals), 
   io(IOManager::getInstance()), 
   enemy(p),
   safeDistance(300),
   currentMode(NORMAL) { }
   
   virtual ~SmartSprite(){}

  float getSafeDistance() { return safeDistance; }

  void draw();
  void update(Uint32 ticks);
  enum MODE {NORMAL, CHASE};
private:	
  const IOManager& io;
  const MultiframeSprite * const enemy;
  float safeDistance;
  MODE currentMode;
  
  //blocked
  SmartSprite(const SmartSprite &s);
  SmartSprite& operator=(const SmartSprite &rhs);
};

#endif
