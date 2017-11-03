// Brian Malloy        Game Construction

#include "menuManager.h"
//#include "frameFactory.h"
//#include "spriteFactory.h"
Gamedata* Gamedata::instance;
FrameFactory* FrameFactory::instance = NULL;
SpriteFactory* SpriteFactory::instance = NULL;

int main(int, char*[]) {
   try {
      MenuManager menuMan;
      menuMan.play();
   }
   catch (const string& msg) { std::cout << msg << std::endl; }
   catch (...) {
      std::cout << "Oops, someone threw an exception!" << std::endl;
   }
   return 0;
}
