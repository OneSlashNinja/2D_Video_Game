#include <sstream>
#include "frameFactory.h"

FrameFactory* FrameFactory::getInstance() {
  if ( instance == NULL ) instance = new FrameFactory;
  return instance;
}

FrameFactory::~FrameFactory() { 
  std::map<string, Frame*>::iterator pos = frames.begin(); 
  while ( pos != frames.end() ) {
    delete pos->second;
    ++pos;
  }
  frames.clear();
  
}

Frame* FrameFactory::getFrame(const string& filename,
    Uint16 width, Uint16 height,
    Sint16 src_x, Sint16 src_y, bool setcolorkey) {
  Frame * spriteFrame;
  
  std::stringstream ss;
  ss <<filename<<width<<height<<src_x<<src_y;
  string exactName = ss.str();
  ss.str("");
  
  std::map<string, Frame*>::iterator pos = frames.begin(); 
  while ( pos != frames.end() ) {
    if ( pos->first == exactName ) break;
    else ++pos;
  }
  if ( pos == frames.end() ) {
    spriteFrame = new Frame(gdata->getXmlStr(filename),
                  width, height, src_x, src_y, setcolorkey);
    frames[exactName] = spriteFrame;
  }
  else {
    spriteFrame = pos->second;
  }
  return spriteFrame;
}


Frame* FrameFactory::getLsystemFrame(const string& filename,
    Uint16 width, Uint16 height,
    Sint16 src_x, Sint16 src_y) {
  Frame * spriteFrame;
  
  
  std::stringstream ss;
  ss << "xmlSpec/" << filename << ".xml";
  string xmlFileName = ss.str();
  ss.str("");
  ss << "lsystem" << filename;
  string exactName = ss.str();
  ss.str("");
  
  LSystem lsystem(xmlFileName);
  
  std::map<string, Frame*>::iterator pos = frames.begin(); 
  while ( pos != frames.end() ) {
    if ( pos->first == exactName ) break;
    else ++pos;
  }
  if ( pos == frames.end() ) {
    spriteFrame = new Frame(lsystem.getSurface(),
                  width, height, src_x, src_y);
    frames[exactName] = spriteFrame;
  }
  else {
    spriteFrame = pos->second;
  }
  
  return spriteFrame;
}

