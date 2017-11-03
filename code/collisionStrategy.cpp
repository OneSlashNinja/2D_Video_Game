#include <algorithm>
#include "ioManager.h"
#include "collisionStrategy.h"
using std::cout; using std::endl;
using std::vector;

void RectangularCollisionStrategy::draw() const {
  IOManager::getInstance().printMessageAt("Rectangular Collision Strategy", 320, 10);
}

bool RectangularCollisionStrategy::execute(
      const Drawable& obj1, const Drawable& obj2) const {
  float left1 = obj1.X();
  float left2 = obj2.X();
  float right1 = left1+obj1.getFrame()->getWidth();
  float right2 = left2+obj2.getFrame()->getWidth();
  float top1 = obj1.Y();
  float top2 = obj2.Y();
  float bottom1 = top1+obj1.getFrame()->getHeight();
  float bottom2 = top2+obj2.getFrame()->getHeight();
  if ( right1 < left2 ) return false;
  if ( left1 > right2 ) return false;
  if ( bottom1 < top2 ) return false;
  if ( bottom2 < top1 ) return false;
  return true;
}

//In the game, all sprite would use the RectangularCollisionStrategy
//so block the other two class, if need to reactivate them, please
//remember to cast the "sprite" type up to"Drawable"
