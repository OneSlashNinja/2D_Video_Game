#include <cmath>
#include "drawable.h"
#include <vector>

class CollisionStrategy {
public:
  virtual bool execute(const Drawable&, const Drawable&) const = 0;
  virtual void draw() const = 0;
  virtual ~CollisionStrategy() {}
};

class RectangularCollisionStrategy : public CollisionStrategy {
public:
  RectangularCollisionStrategy() {}
  virtual bool execute(const Drawable&, const Drawable&) const;
  virtual void draw() const;
};

//In the game, all sprite would use the RectangularCollisionStrategy
//so block the other two class, if need to reactivate them, please
//remember to cast the "sprite" type up to"Drawable"

