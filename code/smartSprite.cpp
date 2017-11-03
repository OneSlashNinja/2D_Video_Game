#include <cmath>
#include "smartSprite.h"

float distance(float x1, float y1, float x2, float y2) {
  float x = x1-x2;
  float y = y1-y2;
  return hypot(x, y);
}


void SmartSprite::draw() {
  MultiframeSprite::draw();
}

void SmartSprite::update(Uint32 ticks) {
  MultiframeSprite::update(ticks);
  float x= X()+getFrame()->getWidth()/2;
  float y= Y()+getFrame()->getHeight()/2;
  float ex= enemy->X()+(enemy->getFrame())->getWidth()/2;
  float ey= enemy->Y()+(enemy->getFrame())->getHeight()/2;
  float distanceToEnemy = ::distance( x, y, ex, ey );
  //"+0.1" is to prevent that the xDistance and yDistance
  //equals to the 0 at the same time
  float xDistance = abs(ex - x) + 0.1;
  float yDistance = abs(ey - y) + 0.1;
  float xFactor = xDistance / (xDistance + yDistance);
  float yFactor = yDistance / (xDistance + yDistance);

  if  ( currentMode == NORMAL ) {
    if(distanceToEnemy < safeDistance) currentMode = CHASE;
  }
  else if  ( currentMode == CHASE ) {
    if(distanceToEnemy > safeDistance) currentMode=NORMAL;
    else {
      
      if ( x < ex ) {velocity[0] = 200 * xFactor;}
      if ( x > ex ) {velocity[0] = 200 * -xFactor;}
      if ( y < ey ) {velocity[1] = 200 * yFactor;}
      if ( y > ey ) {velocity[1] = 200 * -yFactor;}
      
    }
  }
}

