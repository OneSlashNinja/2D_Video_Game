#ifndef MULTISPRITE__H
#define MULTISPRITE__H

#include <string>
#include <iostream>
#include <vector>
using std::string;

#include "drawable.h"
#include "frame.h"

class MultiframeSprite : public Drawable {
public:
  MultiframeSprite(const Vector2f& pos, const Vector2f& vel,
         const string& n, const std::vector<Frame*>& fms,
         const int numOfFrames, const int frameIntervals);
  
  //constructor that has no argument for frames ** add by Qiyue
  MultiframeSprite(const Vector2f& pos, const Vector2f& vel,
         const string& n,const int numOfFrames, 
         const int frameIntervals);
         
  MultiframeSprite(const MultiframeSprite& s);
  virtual ~MultiframeSprite();
  virtual const string& getName() const { return name; }
  void setName(const string& n) { name = n; }

  //add by Qiyue
  void addFrame(Frame* newFrame);

  virtual void draw() const;
  virtual void update(Uint32 ticks);
  
  //add by Qiyue
  virtual const Frame* getFrame() const;

private:
  string name;
  std::vector<Frame *> frames;
  float dt;
  unsigned currentFrame;
  unsigned numberOfFrames;
  unsigned frameInterval;
  void advanceFrame(Uint32 ticks);
  
};
#endif
