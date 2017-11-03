#include "player.h"

void Player::right() { 
  //if ( player.X() < gdata->getXmlInt("worldWidth")-ballWidth) {
    player->velocityX(gdata->getXmlInt("playerXspeed"));
  //}
} 
void Player::left()  { 
  //if ( player.X() > 0) {
    player->velocityX(-gdata->getXmlInt("playerXspeed"));
  //}
} 
void Player::up()    { 
  if ( player->Y() > 0) {
    player->velocityY(-gdata->getXmlInt("playerYspeed"));
  }
} 
void Player::down()  { 
  if ( player->Y() < gdata->getXmlInt("worldHeight")-ballHeight) {
    player->velocityY(gdata->getXmlInt("playerYspeed"));
  }
} 

MultiframeSprite* Player::getPlayerSprite() const {
  return player;
}


void Player::shoot() {
  static int oldTicks = Clock::getInstance().getTicks();
  int ticks = Clock::getInstance().getTicks();
  if ( (ticks - oldTicks) < Gamedata::getInstance()->getXmlInt("bulletDelay") ) return;
  oldTicks = ticks;
  // adjust (x,y) so bullets  appear to come from middle of ball:
  int x = static_cast<int>(player->X())+60;
  int y = static_cast<int>(player->Y())+120;
  // I want the velocity in the y direction to be zero:
  bullets.shoot( "bullet", x, y, Gamedata::getInstance()->getXmlInt("bulletSpeed"), 0);
}

