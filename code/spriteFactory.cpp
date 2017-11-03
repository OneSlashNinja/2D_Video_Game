#include "spriteFactory.h"

SpriteFactory* SpriteFactory::getInstance() {
  if ( instance == NULL ) instance = new SpriteFactory;
  return instance;
}

Sprite* SpriteFactory::makeSingleCore(const string& spriteName){
  Sprite* tmp =NULL;
  
  tmp = new Sprite(Vector2f(gdata->getXmlInt(spriteName + "X"), 
           gdata->getXmlInt(spriteName + "Y")), 
  Vector2f(gdata->getXmlInt(spriteName + "Xspeed"),
           gdata->getXmlInt(spriteName + "Yspeed")),
  spriteName, ff->getFrame(spriteName + "File",gdata->getXmlInt(spriteName + "Width"), 
            gdata->getXmlInt(spriteName + "Height"), 0, 0, true));
  
  return tmp;
}

Sprite* SpriteFactory::makeSpecificSingleCore(const string& spriteName, int xLoc, int yLoc, int xSpeed, int ySpeed){
  Sprite* tmp =NULL;
  
  tmp = new Sprite(Vector2f(xLoc,yLoc), 
                   Vector2f(xSpeed,ySpeed),
  spriteName, ff->getFrame(spriteName + "File",gdata->getXmlInt(spriteName + "Width"), 
            gdata->getXmlInt(spriteName + "Height"), 0, 0, true));
  
  return tmp;
}


MultiframeSprite* SpriteFactory::makeMultiCore(const string& spriteName){
  MultiframeSprite* tmp =NULL;
  
  unsigned numberOfFrames = gdata->getXmlInt(spriteName + "FrameNum");
  Uint16 eachWidth = gdata->getXmlInt(spriteName + "Width") / numberOfFrames;
  Uint16 eachHeight = gdata->getXmlInt(spriteName + "Height");
  Uint16 srcX = gdata->getXmlInt(spriteName + "SrcX");
  Uint16 srcY = gdata->getXmlInt(spriteName + "SrcY");
  Uint16 interval = gdata->getXmlInt(spriteName + "Interval");
  Vector2f position(gdata->getXmlInt(spriteName + "X"), 
    gdata->getXmlInt(spriteName + "Y"));
  Vector2f velocity(gdata->getXmlInt(spriteName + "Xspeed"), 
    gdata->getXmlInt(spriteName + "Yspeed")); 
  
  //instanciate it firstly, then add the frames
  tmp = new MultiframeSprite(position, velocity, spriteName, numberOfFrames, interval);

  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * eachWidth + srcX;
    tmp->addFrame( 
      //new Frame(pterSurface, eachWidth, eachHeight, frameX, srcY) );
      ff->getFrame(spriteName+"File",eachWidth, 
             eachHeight,  frameX, srcY, false));
  }
  
  return tmp;
}

MultiframeSprite* SpriteFactory::makeSpecificMultiCore(const string& spriteName, int xLoc, int yLoc, int xSpeed, int ySpeed){
  MultiframeSprite* tmp =NULL;
  
  unsigned numberOfFrames = gdata->getXmlInt(spriteName + "FrameNum");
  Uint16 eachWidth = gdata->getXmlInt(spriteName + "Width") / numberOfFrames;
  Uint16 eachHeight = gdata->getXmlInt(spriteName + "Height");
  Uint16 srcX = gdata->getXmlInt(spriteName + "SrcX");
  Uint16 srcY = gdata->getXmlInt(spriteName + "SrcY");
  Uint16 interval = gdata->getXmlInt(spriteName + "Interval");
  Vector2f position(xLoc, yLoc);
  Vector2f velocity(xSpeed, ySpeed); 
  
  //instanciate it firstly, then add the frames
  tmp = new MultiframeSprite(position, velocity, spriteName, numberOfFrames, interval);

  for (unsigned i = 0; i < numberOfFrames; ++i) {
    unsigned frameX = i * eachWidth + srcX;
    tmp->addFrame( 
      //new Frame(pterSurface, eachWidth, eachHeight, frameX, srcY) );
      ff->getFrame(spriteName+"File",eachWidth, 
             eachHeight,  frameX, srcY, false));
  }
  
  return tmp;
}

Sprite* SpriteFactory::makeSprite(const string& name){
  Sprite * temp = NULL;
  if(name == "stoptruck"){
  
    temp = makeSingleCore("stoptruck");
    
  }else{
    throw string("There is no such sprite");
  }
  
  return temp;
}

Sprite* SpriteFactory::makeSpecificSprite(const string& name, int xLoc, int yLoc, int xSpeed, int ySpeed){
  Sprite * temp = NULL;
  if(name == "bullet"){
  
    temp = makeSpecificSingleCore("bullet", xLoc, yLoc, xSpeed, ySpeed);
              
  }else{
    throw string("There is no such sprite");
  }
  
  return temp;
}

//-----------------------------------------------------------------------------

MultiframeSprite* SpriteFactory::makeMultiframeSprite(const string& name){
  MultiframeSprite * temp = NULL;
  
  if(name == "craft"){      
    temp = makeMultiCore("craft");
    
  }else if(name == "ufo"){
  
    temp = makeMultiCore("ufo");
    
    
  }else if(name == "soldier"){
  
    temp = makeMultiCore("soldier");
    
  }else if(name == "shootsoldier"){
  
    temp = makeMultiCore("shootsoldier");
    
  }else if(name == "truck"){
    
    temp = makeMultiCore("truck");
    
  }else if(name == "dictator"){
  
    temp = makeMultiCore("dictator");
    
  }else{
    throw string("There is no such sprite");
  }
  
  return temp;
}

MultiframeSprite* SpriteFactory::makeSpecificMultiframeSprite(const string& name, int xLoc, int yLoc, int xSpeed, int ySpeed){
  MultiframeSprite * temp = NULL;
  
  if(name == "soldier"){      
    temp = makeSpecificMultiCore("soldier", xLoc, yLoc, xSpeed, ySpeed);
    
  }else if(name == "ufo"){
    temp = makeSpecificMultiCore("ufo", xLoc, yLoc, xSpeed, ySpeed);
  }else if(name == "truck"){
    temp = makeSpecificMultiCore("truck", xLoc, yLoc, xSpeed, ySpeed);
  }else{
    throw string("There is no such sprite");
  }
  
  return temp;
}

//-----------------------------------------------------------------------------

Sprite* SpriteFactory::makeLsystemSprite(const string& name){
  Sprite * temp = NULL;
  
  temp = new Sprite(Vector2f(gdata->getXmlInt("lsystemX"), 
             gdata->getXmlInt("lsystemY")), 
    Vector2f(gdata->getXmlInt("lsystemXspeed"),
             gdata->getXmlInt("lsystemYspeed")),
    "lsystem", ff->getLsystemFrame(name,gdata->getXmlInt("lsystemWidth"), 
              gdata->getXmlInt("lsystemHeight"), 
              gdata->getXmlInt("lsystemSrcX"), 
              gdata->getXmlInt("lsystemSrcY")));
  
  return temp;
}

SmartSprite* SpriteFactory::makeSmartSprite(const string& spriteName, const MultiframeSprite* msp){
  SmartSprite* tmp =NULL;
  
  if(spriteName == "mine"){
    unsigned numberOfFrames = gdata->getXmlInt(spriteName + "FrameNum");
    Uint16 eachWidth = gdata->getXmlInt(spriteName + "Width") / numberOfFrames;
    Uint16 eachHeight = gdata->getXmlInt(spriteName + "Height");
    Uint16 srcX = gdata->getXmlInt(spriteName + "SrcX");
    Uint16 srcY = gdata->getXmlInt(spriteName + "SrcY");
    Uint16 interval = gdata->getXmlInt(spriteName + "Interval");
    Vector2f position(gdata->getXmlInt(spriteName + "X"), 
      gdata->getXmlInt(spriteName + "Y"));
    Vector2f velocity(gdata->getXmlInt(spriteName + "Xspeed"), 
      gdata->getXmlInt(spriteName + "Yspeed")); 
    
    //instanciate it firstly, then add the frames
    tmp = new SmartSprite(position, velocity, spriteName, numberOfFrames, interval, msp);

    for (unsigned i = 0; i < numberOfFrames; ++i) {
      unsigned frameX = i * eachWidth + srcX;
      tmp->addFrame( 
        //new Frame(pterSurface, eachWidth, eachHeight, frameX, srcY) );
        ff->getFrame(spriteName+"File",eachWidth, 
               eachHeight,  frameX, srcY, false));
    }
    
  }else{
    throw string("There is no such smartSprite.");
  }
  
  return tmp;
}

SmartSprite* SpriteFactory::makeSmartSprite(const string& spriteName, const MultiframeSprite* msp, 
                                            int xLoc, int yLoc, int xSpeed, int ySpeed){
  SmartSprite* tmp =NULL;
  
  if(spriteName == "mine"){
    unsigned numberOfFrames = gdata->getXmlInt(spriteName + "FrameNum");
    Uint16 eachWidth = gdata->getXmlInt(spriteName + "Width") / numberOfFrames;
    Uint16 eachHeight = gdata->getXmlInt(spriteName + "Height");
    Uint16 srcX = gdata->getXmlInt(spriteName + "SrcX");
    Uint16 srcY = gdata->getXmlInt(spriteName + "SrcY");
    Uint16 interval = gdata->getXmlInt(spriteName + "Interval");
    Vector2f position(xLoc, yLoc);
    Vector2f velocity(xSpeed, ySpeed); 
    
    //instanciate it firstly, then add the frames
    tmp = new SmartSprite(position, velocity, spriteName, numberOfFrames, interval, msp);

    for (unsigned i = 0; i < numberOfFrames; ++i) {
      unsigned frameX = i * eachWidth + srcX;
      tmp->addFrame( 
        //new Frame(pterSurface, eachWidth, eachHeight, frameX, srcY) );
        ff->getFrame(spriteName+"File",eachWidth, 
               eachHeight,  frameX, srcY, false));
    }
    
  }else{
    throw string("There is no such smartSprite.");
  }
  
  return tmp;
}

SpriteFactory::~SpriteFactory() { 
  
  delete FrameFactory::getInstance();
  delete Gamedata::getInstance();
}
