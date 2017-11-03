#include <iostream>
#include <cmath>
#include "explodingSprite.h"

ExplodingSprite::ExplodingSprite(const Sprite& s) :
  Sprite(s), 
  chunks(), 
  freeList(),
  frames() {
  makeChunks(Gamedata::getInstance()->getXmlInt("orbChunkSize"));
}

//added by Qiyue
ExplodingSprite::ExplodingSprite(const Drawable * s) :
  Sprite(s->getPosition(), s->getVelocity(), s->getName(), s->getFrame()), 
  chunks(), 
  freeList(),
  frames() {
  makeChunks(Gamedata::getInstance()->getXmlInt("orbChunkSize"));
}

ExplodingSprite::~ExplodingSprite() { 
  chunks.clear();
  freeList.clear();
  for ( unsigned int i = 0; i < frames.size(); ++i ) {
    delete frames[i];
  }
}

void ExplodingSprite::draw() const { 
  std::list<Chunk>::const_iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->draw();
    ++ptr;
  }
}

void ExplodingSprite::update(Uint32 ticks) { 

  std::list<Chunk>::iterator ptr = chunks.begin();
  while (ptr != chunks.end()) {
    ptr->update(ticks);
    if (ptr->goneTooFar()) {
      freeList.push_back(*ptr);
      ptr = chunks.erase(ptr);
    }   
    else ++ptr;
    

  }
}

void ExplodingSprite::makeChunks(unsigned int n) { 
  unsigned int chunk_width = frame->getWidth()/n;
  unsigned int chunk_height = frame->getHeight()/n;
  Sint16 source_x = frame->getSourceX();
  Sint16 source_y = frame->getSourceY();
  //modified by Qiyue
  //If not modified, the explosion of immobile sprite would be very weird
  int speedx = Gamedata::getInstance()->getXmlInt("orbChunkXspeed");
  int speedy = Gamedata::getInstance()->getXmlInt("orbChunkYspeed");
  
  SDL_Surface* spriteSurface(frame->getSurface()); 
  for (unsigned int i = 0; i < n; ++i) {
    for (unsigned int j = 0; j < n; ++j) {
      float sx = (rand() % speedx + 40) * (rand()%2?-1:1); // 'cause %0 is 
      float sy = (rand() % speedy + 40) * (rand()%2?-1:1); // float except
      Frame* frame = 
            new Frame(spriteSurface, chunk_width, chunk_height,
                  source_x+i*chunk_width,  // x coord of surface
                  source_y+j*chunk_height // y coord of surface
                );
      Chunk chunk(
                Vector2f(X()+i*chunk_width,   // x coord of destination 
                         Y()+j*chunk_height), // y coord of destination
                Vector2f(sx, sy),
                "orbChunk",
                frame);
      chunks.push_back(chunk);
      frames.push_back(frame);
    }
  }
}

