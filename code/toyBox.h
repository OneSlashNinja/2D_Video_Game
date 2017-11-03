#ifndef TOYBOX__H
#define TOYBOX__H

#include <string>
#include <vector>
#include <sstream>
#include "drawable.h"
#include "ioManager.h"
#include "spriteFactory.h"
#include "explodingSprite.h"
#include "player.h"
#include "collisionStrategy.h"
#include "sound.h"
#include "smartSprite.h"
#include "aaline.h"

class ToyBox {
public:
  ToyBox();
  void addSprite(const std::string& name);
  
  void addMultiSprite(const std::string& name);
  
  void addSmartSprite(const std::string& name);
  
  //override the two function above to allow to specify the location and speed
  
  void addSprite(const std::string& name, int xLoc, int yLoc, int xSpeed, int ySpeed);
  
  void addMultiSprite(const std::string& name, int xLoc, int yLoc, int xSpeed, int ySpeed);
  
  void addSmartSprite(const std::string& name, int xLoc, int yLoc, int xSpeed, int ySpeed);
  
  //----------------------------------------------------------------------------------------
  
  void addLsystemSprite(const std::string& name);
  
  void switchInfoDisplay();
  
  void setCurrentSprite(Drawable* d);
  
  Drawable* getCurrentSprite();
  
  bool hasNextSprite();
  
  void nextSprite();
  
  void draw();
  
  void update(Uint32 ticks);
  
  void explodeCurrentSprite();
  
  
  //For the player to move
  void playerUp(){player.up();}
  void playerDown(){player.down();}
  void playerLeft(){player.left();}
  void playerRight(){player.right();}
  void playerStop(){player.stop();}
  
  MultiframeSprite* getPlayer(){
    return player.getPlayerSprite();
  }
  
  //then player can shoot
  void playerShoot(){
    player.shoot();
    //to make sound
    sound[0];
  }
  
  void checkForCollisions();
  
  void checkMineCollisions();
  
  void toggleMusic();
  
  //but the implementation of operator[] of SDLSound is not compatible for const
  int checkGameState();
  
  void setTime(float t){
    timeLeft = 120 - t;
    //should be read from the xml
  }
  
  //it seems to be that there is no need to clean the
  //sprites. Because what free the sprites do is only 
  //detele the frames. But when delete the frameFactory
  //all the frames would be deleted.
  
  ~ToyBox(){
    for (unsigned i = 0; i < box.size(); ++i) {
      delete box[i];
    }
    
    box.clear();
    
    for (unsigned j = 0; j < explodingsp.size();++j){
      delete explodingsp[j];
    }
    
    explodingsp.clear();
    
    for(unsigned k = 0; k < sensorMines.size();++k){
      delete sensorMines[k];
    }
    
    sensorMines.clear();
    
    //player would be deleted automaticlly
  }
  
  void toyboxReset();

private:

  SpriteFactory* factory;
  std::vector<Drawable*> box;
  std::vector<ExplodingSprite*> explodingsp;
  
  Player player;
  
  std::vector<SmartSprite*> sensorMines;
  
  //collision detect
  RectangularCollisionStrategy rcs;
  
  bool showInfo;
  unsigned currentSprite;
  const IOManager& io;
  
  SDLSound sound;
  
  int health;
  
  float timeLeft;
  
  void eraseCurrentSprite();
    
  ToyBox(const ToyBox& tb);
  ToyBox& operator=(const ToyBox& tb);
};

#endif
