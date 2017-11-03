#include <cmath>
#include <sstream>
#include "bullets.h"
#include "gamedata.h"
using std::string;

Bullets::~Bullets() {
  
}

Bullets::Bullets() :
  maxDistance(Gamedata::getInstance()->getXmlInt("bulletDistance")),
  bullets()
  {}

void Bullets::cullBullets() {
   list<Bullet>::iterator bi = bullets.begin(); 
   while ( bi != bullets.end() ) {
     if ( bi->getDistance() >= maxDistance ) {
       bi = bullets.erase(bi);
     }
     else ++bi;
   }
}

//important modification, let the spriteFactory make the sprite for the bullet
void Bullets::shoot(const string& bulletName, int xLoc, int yLoc, int xSpeed, int ySpeed) {
  Bullet b(*(SpriteFactory::getInstance()->makeSpecificSprite(bulletName, xLoc, yLoc, xSpeed, ySpeed)));
  bullets.push_back( b );
}

void Bullets::update(Uint32 ticks) { 
   cullBullets();
   for( list<Bullet>::iterator bi = bullets.begin(); 
        bi != bullets.end(); ++bi ) {
     bi->update( ticks );
   }
}

void Bullets::draw() const { 
  for( list<Bullet>::const_iterator bi = bullets.begin(); 
       bi != bullets.end(); ++bi ) {
    bi->draw();
  }
}

