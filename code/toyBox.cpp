#include "toyBox.h"

ToyBox::ToyBox() :factory( SpriteFactory::getInstance() ),
                  box(),explodingsp(), //erasedsp(),
                  player(factory->makeMultiframeSprite("craft")),
                  sensorMines(),
                  rcs(),
                  showInfo(false),
                  currentSprite(0),
                  io(IOManager::getInstance()),
                  sound(),
                  health(200),
                  timeLeft(120.0)
                  {}


void ToyBox::addSprite(const std::string& name) {
  box.push_back( factory->makeSprite(name) );
}

void ToyBox::addMultiSprite(const std::string& name) {
  box.push_back( factory->makeMultiframeSprite(name) );
}

void ToyBox::addSmartSprite(const std::string& name){
  sensorMines.push_back( factory->makeSmartSprite(name, player.getPlayerSprite()) );
}

//override the two functions above
void ToyBox::addSprite(const std::string& name, int xLoc, int yLoc, int xSpeed, int ySpeed) {
  box.push_back( factory->makeSpecificSprite(name, xLoc, yLoc, xSpeed, ySpeed) );
}

void ToyBox::addMultiSprite(const std::string& name, int xLoc, int yLoc, int xSpeed, int ySpeed) {
  box.push_back( factory->makeSpecificMultiframeSprite(name, xLoc, yLoc, xSpeed, ySpeed) );
}

void ToyBox::addSmartSprite(const std::string& name, int xLoc, int yLoc, int xSpeed, int ySpeed){
  sensorMines.push_back( factory->makeSmartSprite(name, player.getPlayerSprite(), xLoc, yLoc, xSpeed, ySpeed) );
}


void ToyBox::addLsystemSprite(const std::string& name){
  box.push_back( factory->makeLsystemSprite(name) );
}

void ToyBox::switchInfoDisplay(){
  if(showInfo){
    showInfo = false;
  }else{
    showInfo = true;
  }
}

Drawable* ToyBox::getCurrentSprite(){
  return box[currentSprite];
}

void ToyBox::setCurrentSprite(Drawable* d){
  box[currentSprite] = d;
}

bool ToyBox::hasNextSprite(){
  if(box.size() > 0){
    return true;
  }else{
    return false;
  }
}

void ToyBox::nextSprite(){
  currentSprite = (currentSprite+1) % box.size();
}

void ToyBox::draw() {
  
  for (unsigned i = 0; i < box.size(); ++i) {
    box[i]->draw();
  }
  
  for (unsigned j = 0; j < explodingsp.size(); ++j) {
    explodingsp[j]->draw();
  }
  
  //draw the player
  player.draw();
  
  for (unsigned k = 0; k < sensorMines.size(); ++k) {
    sensorMines[k]->draw();
  }
  
  if(showInfo){
  
    io.printMessageAt("Press a / SPACE to shoot!",50, 10);
    io.printMessageAt("Press r to track the Player",50, 30);
    io.printMessageAt("Press t to switch and track other sprites",50, 50);
    io.printMessageAt("Press p to pause game", 50,70);
    io.printMessageAt("Press m to pause the music", 50,90);
    io.printMessageAt("Press UP / DOWN / LEFT / RIGHT to control player", 50,110);
    io.printMessageAt("Press F1 to show / hide help info", 50,130);
    io.printMessageAt("Press q / ESC to quit game", 50,150);

    
    io.printMessageAt("Author: Qiyue Sheng",500,10);
    io.printMessageAt("Sprites resource from 'Metal Slug'",500,30);
    io.printMessageAt("http://spriters-resource.com/",500,50);
    io.printMessageAt("Except the lsystem sprite",500,70);
    
  }else{
    io.printMessageAt("Health:",10,10);
    //----border of the health bar
    Draw_AALine(io.getScreen(), 88, 22, 292, 22, 2, 0, 0, 0, 255);
    Draw_AALine(io.getScreen(), 88, 22, 88, 38, 2, 0, 0, 0, 255);
    Draw_AALine(io.getScreen(), 88, 38, 292, 38, 2, 0, 0, 0, 255);
    Draw_AALine(io.getScreen(), 293, 22, 293, 38, 2, 0, 0, 0, 255);
    //----------------------------
    Draw_AALine(io.getScreen(), 90, 30, 90+health, 30, 10, 200, 0, 0, 255);
    io.printMessageCenteredAt("Press F1 for help", 30);
    
    
    io.printMessageValueAt("Time left: ", timeLeft, 600, 10);
  }
  
  
}

void ToyBox::update(Uint32 ticks) {
  for (unsigned i = 0; i < box.size(); ++i) {
    box[i]->update(ticks);
  }
  
  for (unsigned j = 0; j < explodingsp.size(); ++j) {
    explodingsp[j]->update(ticks);
  }
  
  //draw the player
  player.update(ticks);
  
  for (unsigned k = 0; k < sensorMines.size(); ++k) {
    sensorMines[k]->update(ticks);
  }

}

void ToyBox::eraseCurrentSprite(){
  std::vector<Drawable*>::iterator it = box.begin();
  it += currentSprite;
  box.erase(it);
}


void ToyBox::explodeCurrentSprite(){

  explodingsp.push_back(
		new ExplodingSprite(getCurrentSprite())
	);
	
	//erasedsp.push_back(getCurrentSprite());
	eraseCurrentSprite();
}

//The function blow is to detect the collision between the bullets and sprites
void ToyBox::checkForCollisions() {
  std::list<Bullet>::iterator bit = player.getBulletsIterBegin();
  std::vector<Drawable*>::iterator spit = box.begin();
  std::vector<SmartSprite*>::iterator mit = sensorMines.begin();
  
  for( ;bit != player.getBulletsIterEnd(); ++bit){
   spit = box.begin();
   while(spit != box.end()){
      if ( rcs.execute(*(bit), *(*spit)) ) {
      
        //to make sound
        if((*spit)->getName() == "soldier" || (*spit)->getName() == "shootsoldier"){
          sound[1];
        }else if((*spit)->getName() == "ufo"){
          sound[2];
        }else{
          sound[2];
        }
      
        explodingsp.push_back(
		      new ExplodingSprite(*spit)
	      );

	      delete (*spit);
	      spit = box.erase(spit);
	      //add this break can improve efficiency?
	      //break;
        
      }else{
        ++spit;
      }
    }
    
    mit = sensorMines.begin();
    while(mit != sensorMines.end()){
      if ( rcs.execute(*(bit), *(*mit)) ) {
      
        //to make sound
        sound[2];
      
        explodingsp.push_back(
          new ExplodingSprite(*mit)
        );

        delete (*mit);
        mit = sensorMines.erase(mit);
        //break;
        
      }else{
        ++mit;
      }
    }
     
  }
}

void ToyBox::checkMineCollisions() {
  std::vector<SmartSprite*>::iterator mit = sensorMines.begin();
  while(mit != sensorMines.end()){
    if ( rcs.execute(*(player.getPlayerSprite()), *(*mit)) ) {
    
      //to make sound
      sound[2];
    
      explodingsp.push_back(
        new ExplodingSprite(*mit)
      );

      delete (*mit);
      mit = sensorMines.erase(mit);
      
      if(health > 30){
        health -= 30;
      }else{
        health = 0;
      }
      //break;
      
    }else{
      ++mit;
    }
  } 
}


void ToyBox::toggleMusic(){
  sound.toggleMusic();
}


//return the state of the game
//0 stand for the normal state
//1 stand for the gameover state
//2 stand for the win state

//in fact it should be a const function
//but the implementation of operator[] of SDLSound is not compatible for const
int ToyBox::checkGameState() {
  if(health <= 0 || timeLeft <= 0.0){
    return 1;
  }else if(box.size() == 0){
    sound[3];
    return 2;
  }else{
    return 0;
  }
}

//when the it is win or over, the manager should call this funtion
void ToyBox::toyboxReset(){
  health = 200;
  timeLeft = 120.0;
  
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
}
