#include <cmath>
#include "sprite.h"

class Bullet : public Sprite {
public:
  Bullet(const Sprite& s) :
    Sprite(s), 
    distance(0) 
  {}
  void update(Uint32 ticks);
  float getDistance() const { return distance; }
  void setDistance(float d) { distance = d; }
  
  virtual ~Bullet(){}
private:
  Bullet();
  float distance;
};
