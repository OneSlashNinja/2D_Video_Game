#ifndef SPRITE__H
#define SPRITE__H

#include <string>
using std::string;
#include <iostream>

#include "drawable.h"
#include "frame.h"

class Sprite : public Drawable {
public:
  Sprite(const Vector2f& pos, const Vector2f& vel,
         const string& n, const Frame*);
  Sprite(const Sprite& s);
  virtual ~Sprite() { } 
  Sprite& operator=(const Sprite&);
  virtual const string& getName() const { return name; }
  void setName(const string& n) { name = n; }

  virtual const Frame* getFrame() const { return frame; }
  virtual void setFrame(const Frame* f) { frame = f; }
  virtual void draw() const;
  virtual void update(Uint32 ticks);
  unsigned getPixel(Uint32, Uint32) const;

  Vector2f getCenter() const { 
    return Vector2f( X()+frame->getWidth()/2, Y()+frame->getHeight()/2 );
  }

private:
  string name;
protected:
  const Frame * frame;
  int getDistance(const Sprite*) const;
};
#endif
