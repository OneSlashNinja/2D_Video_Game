#ifndef BULLETS__H
#define BULLETS__H

#include <SDL.h>
#include <iostream>
#include <list>
using std::list;

#include "bullet.h"
#include "spriteFactory.h"

class Bullets {
public:
  Bullets ();
  ~Bullets ();

  void shoot(const string& bulletName, int xLoc, int yLoc, int xSpeed, int ySpeed);
  void update(Uint32);
  void draw() const;
  
  //added by Qiyue
  list<Bullet>::iterator getBulletsIterBegin(){
    list<Bullet>::iterator bi = bullets.begin();
    return bi;
  }
  list<Bullet>::iterator getBulletsIterEnd(){
    list<Bullet>::iterator bi = bullets.end();
    return bi;
  }


private:
  int maxDistance;
  list<Bullet> bullets;

  bool shooting() const { return bullets.size() > 0; }
  void cullBullets(); 
  
  Bullets(const Bullets& b);
  Bullets& operator=(const Bullets& b);
};

#endif
