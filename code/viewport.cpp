#include "ioManager.h"
#include "viewport.h"

Viewport& Viewport::getInstance() {
  static Viewport viewport;
  return viewport;
}

Viewport::Viewport() : 
  frozen(false),       
  gdata(Gamedata::getInstance()),
  position(0, 0),
  viewWidth(gdata->getXmlInt("viewWidth")), 
  viewHeight(gdata->getXmlInt("viewHeight")),
  worldWidth(gdata->getXmlInt("worldWidth")),
  worldHeight(gdata->getXmlInt("worldHeight")),
  objWidth(0), objHeight(0), objX(0),
  objectToTrack(NULL) 
{}

void Viewport::draw() const {
  std::stringstream strm;
  std::string msg;
  //strm << "viewport: (" << static_cast<int>( X() ) 
              //<< ", " << static_cast<int>( Y() ) << ")\0";
  //msg = strm.str();
  //IOManager::getInstance().printMessageAt(msg.c_str(), 10, 90);
  strm.str("");
  strm << "Pter at: " << objX << "\0";
  msg = strm.str();
  IOManager::getInstance().printMessageAt(msg.c_str(), 10, 70);
}

void Viewport::setObjectToTrack(const Drawable *obj) { 
  objectToTrack = obj; 
  objWidth = objectToTrack->getFrame()->getWidth();
  objHeight = objectToTrack->getFrame()->getHeight();
}

void Viewport::update() {
  if ( frozen ) return;
  const float x = objectToTrack->X();
  objX =  static_cast<int>(x);
  const float y = objectToTrack->Y();
  position[0] = (x + objWidth/2) - viewWidth/2;
  position[1] = (y + objHeight/2) - viewHeight/2;
  if (position[0] < 0) position[0] = 0;
  if (position[1] < 0) position[1] = 0;
  if (position[0] > (worldWidth - viewWidth)) {
    position[0] = worldWidth-viewWidth;
  }
  if (position[1] > (worldHeight - viewHeight)) {
    position[1] = worldHeight-viewHeight;
  }
}
