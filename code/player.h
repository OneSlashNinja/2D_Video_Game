#include "multisprite.h"
#include "gamedata.h"
#include "bullets.h"
#include "clock.h"

class Player {
public:
  Player(MultiframeSprite * s) : 
    gdata(Gamedata::getInstance()),
    player(s), 
    ballWidth( gdata->getXmlInt(s->getName() + "Width") ),
    ballHeight( gdata->getXmlInt(s->getName() + "Height") ),
    bullets()
  {}
  virtual ~Player() {
    delete player;
    //bullets would be deleted automaticlly as well;
  }

  virtual void update(Uint32 ticks) { 
    player->update(ticks);
    bullets.update(ticks);
  }
  virtual void draw() const { 
    player->draw();
    bullets.draw();
  }
  //const MultiframeSprite& getSprite() const { return *player; }

  void stop() { 
    player->velocityX(0);  
    player->velocityY(0);  
  }
  void right();
  void left();
  void up();
  void down();
  
  MultiframeSprite* getPlayerSprite() const;
  
  //to shoot the bullet
  void shoot();
  
  //added by Qiyue
  list<Bullet>::iterator getBulletsIterBegin(){
    return bullets.getBulletsIterBegin();
  }
  list<Bullet>::iterator getBulletsIterEnd(){
    return bullets.getBulletsIterEnd();
  }

private:
  //added by Qiyue
  const Gamedata* gdata;

  MultiframeSprite * player;
  float ballWidth;
  float ballHeight;
  
  Bullets bullets;
  
  //to block the copy constructor
  Player(const Player& pl);
  Player& operator=(const Player&);
};

