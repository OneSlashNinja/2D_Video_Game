#include <iostream>
#include "world.h"

void World::update() {
  worldX = static_cast<int>(view.X() / factor) % frameWidth;
  worldY = view.Y();
}

void World::draw() const { 
  frame1.draw(worldX, worldY, 0, 0); 
  frame2.draw(0, worldY, frameWidth-worldX, 0); 
}

