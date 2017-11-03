#include <cmath>
#include "manager.h"

Manager::~Manager() { 
  // These deletions eliminate "definitely lost" and
  // "still reachable"s in Valgrind.
  SDL_FreeSurface(bgSurface);
  SDL_FreeSurface(fgSurface);
  delete SpriteFactory::getInstance();
  //delete tb
}

void Manager::initSprites(){
  tb.addMultiSprite("soldier");
  tb.addMultiSprite("soldier",20,540,100,0);
  tb.addMultiSprite("soldier",100,550,150,0);
  tb.addMultiSprite("soldier",500,542,200,0);
  tb.addMultiSprite("soldier",800,544,180,0);
  tb.addMultiSprite("soldier",1000,543,140,0);
  tb.addMultiSprite("soldier",800,544,180,0);
  tb.addMultiSprite("soldier",1000,543,250,0);
  tb.addMultiSprite("soldier",1300,544,220,0);
  tb.addMultiSprite("soldier",1900,543,190,0);
  tb.addMultiSprite("soldier",3000,544,170,0);
  tb.addMultiSprite("soldier",4000,543,180,0);
  tb.addMultiSprite("shootsoldier");
  tb.addMultiSprite("truck");
  tb.addSprite("stoptruck");
  tb.addMultiSprite("ufo");
  tb.addMultiSprite("ufo",500,340,200,0);
  tb.addMultiSprite("ufo",2000,240,-200,0);
  tb.addMultiSprite("ufo",3000,100,-100,0);
  tb.addMultiSprite("ufo",5000,400,100,0);
  tb.addLsystemSprite("cross");
  tb.addMultiSprite("dictator");
  tb.addSmartSprite("mine",700,340,200,100);
  tb.addSmartSprite("mine",2200,240,-200,200);
  tb.addSmartSprite("mine",900,30,200,0);
  tb.addSmartSprite("mine",15000,240,-300,300);
  tb.addSmartSprite("mine",11000,40,-300,300);
  tb.addSmartSprite("mine",17000,140,-300,300);
  tb.addSmartSprite("mine",10000,340,-300,300);
  tb.addSmartSprite("mine",1000,200,-200,100);
  tb.addSmartSprite("mine",8200,550,-400,100);
  tb.addSmartSprite("mine",3200,300,-50,30);
  tb.addSmartSprite("mine",2500,560,-120,330);
  tb.addSmartSprite("mine",9000,670,-500,700);
  tb.addSmartSprite("mine",10000,340,-100,50);
  viewport.setObjectToTrack(tb.getPlayer());
}

Manager::Manager() :
  env( SDL_putenv(const_cast<char*>("SDL_VIDEO_CENTERED=center")) ),
  gdata( Gamedata::getInstance() ),
  io( IOManager::getInstance() ),
  clock( Clock::getInstance() ),
  tb(),
  screen( io.getScreen() ),
  bgSurface( io.loadAndSet(gdata->getXmlStr("backgroundFile"), false) ),
  background(bgSurface,
             gdata->getXmlInt("backgroundWidth"), 
             gdata->getXmlInt("backgroundHeight"), 
             gdata->getXmlInt("backgroundSrcX"),
             gdata->getXmlInt("backgroundSrcY")),
  fgSurface( io.loadAndSet(gdata->getXmlStr("foregroundFile"), false) ),
  foreground(fgSurface,
             gdata->getXmlInt("foregroundWidth"), 
             gdata->getXmlInt("foregroundHeight"), 
             gdata->getXmlInt("foregroundSrcX"),
             gdata->getXmlInt("foregroundSrcY")),
  backWorld(&background, 2),
  frontWorld(&foreground),
  viewport( Viewport::getInstance() ),
  total_ticks(0)
{
  clock.pause();
  //important modification to prevent the seg fault from Mix_CloseAudio();
  if (SDL_Init(SDL_INIT_VIDEO) != 0) {
     throw string("Unable to initialize SDL: ");
  }

  initSprites();

  atexit(SDL_Quit);
  
  SDL_WM_SetCaption( "*** The Counterattack of the Alien --By Qiyue Sheng ***", NULL );
}

void Manager::play() {

  clock.unpause();

  SDL_Event event;

  bool done = false;
  bool keyCatch = false;
  
  float seconds = 0;
  Uint32 ticks = 0;
  
  OverScreen over;
  WinScreen win;
  
  while ( not done ) {
    backWorld.draw();
    frontWorld.draw();
    tb.checkForCollisions();
    tb.checkMineCollisions();
    tb.draw();
    SDL_Flip(screen);
    
    //check the game state
    switch (tb.checkGameState()){
      //normal state
      case 0:
        break;
        
      //Gameover state
      case 1:
        clock.pause();
        over.play();
        done = true;
        gameReset();
        break;
        
      //win state
      case 2:
        clock.pause();
        win.play();
        clock.pause();
        done = true;
        gameReset();
        break;
    }
    
    ticks = clock.getElapsedTicks();
    total_ticks += ticks;
    seconds = total_ticks*0.001;
    
    
    viewport.update();
    backWorld.update();
    frontWorld.update();
    tb.update(ticks);
    tb.setTime(seconds);


    SDL_PollEvent(&event);
    if (event.type ==  SDL_QUIT) { 
      clock.pause();
      break; 
    }
    if(event.type == SDL_KEYUP) { 
      tb.playerStop();
      keyCatch = false; 
    }
    if(event.type == SDL_KEYDOWN) {
      switch ( event.key.keysym.sym ) {
        case SDLK_ESCAPE : clock.pause(); done = true; break;
        case SDLK_q      : clock.pause(); done = true; break;
        case SDLK_F1     : 
          if ( !keyCatch ) {
            keyCatch = true;
            tb.switchInfoDisplay();
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
          }
          break;
          
        case SDLK_t :{
          if ( !keyCatch ) {
            keyCatch = true;
            if(tb.hasNextSprite()){
              tb.nextSprite();
              viewport.setObjectToTrack(tb.getCurrentSprite());
            }
          }
          break;
        }
        
        case SDLK_m :{
          if ( !keyCatch ) {
            keyCatch = true;
            tb.toggleMusic();
          }
          break;
        }
        case SDLK_p      : {
          if (!keyCatch) {
            keyCatch = true;
            if ( clock.isPaused() ) clock.unpause();
            else clock.pause();
          }
          break;
        }
        
        case SDLK_r      : {
          if (!keyCatch) {
            keyCatch = true;
            viewport.setObjectToTrack(tb.getPlayer());
          }
          break;
        }
        
        case SDLK_a      : case SDLK_SPACE : {
          tb.playerShoot();
          break;
        }
        
        case SDLK_LEFT  : { tb.playerLeft(); break; }
        case SDLK_RIGHT : { tb.playerRight(); break; }
        case SDLK_UP    : { tb.playerUp(); break; }
        case SDLK_DOWN  : { tb.playerDown(); break; }
        default          : break;
      }
    }
  }
}

void Manager::resetViewPort(){
  viewport.X(0);
  viewport.Y(0);
}

void Manager::gameReset(){
  tb.toyboxReset();
  total_ticks = 0;
  initSprites();
}
