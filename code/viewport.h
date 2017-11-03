#ifndef VIEWPORT__H
#define VIEWPORT__H
#include "sprite.h"
#include "gamedata.h"

class Viewport {
public:
  static Viewport& getInstance();
  void update();
  void setObjExploded();

  float X() const { return position[0]; }
  void X(float x) { position[0] = x; }
  float Y() const { return position[1]; }
  void Y(float y) { position[1] = y; }

  void setObjectToTrack(const Drawable *obj);
  const Drawable* getObjectToTrack() const { return objectToTrack; } 
  void freeze() { frozen = true; }
  void draw() const;

private:
  bool frozen;
  const Gamedata* gdata;
  Vector2f position;
  unsigned viewWidth;
  unsigned viewHeight;
  unsigned worldWidth;
  unsigned worldHeight;
  Uint16 objWidth;
  Uint16 objHeight;
  int objX;
  
  const Drawable *objectToTrack;

  Viewport();
  Viewport(const Viewport&);
  Viewport& operator=(const Viewport&);
};
#endif
