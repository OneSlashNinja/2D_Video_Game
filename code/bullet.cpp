#include "bullet.h"

void Bullet::update(Uint32 ticks) {
  
  float x = X();
  //Sprite::update(ticks);
  
  float incr = velocityY() * static_cast<float>(ticks) * 0.001;
  Y( Y()+incr );


  incr = velocityX() * static_cast<float>(ticks) * 0.001;
  X( X()+incr );
 
  distance += fabs(x - X());
}
