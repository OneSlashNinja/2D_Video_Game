#include <sstream>
#include "menu.h"
#include "parseXML.h"

Menu::Menu() : 
  io( IOManager::getInstance() ),
  words(), 
  position(),
  space(),
  clicks(),
  nextIcon(0),
  click(0) 
{ 
  ParseXML parser( "xmlSpec/menu.xml" );
  unsigned int n = parser.getXmlInt("wordsNumber");
  position[0] = parser.getXmlInt("wordsX");
  position[1] = parser.getXmlInt("wordsY");
  std::stringstream strm;
  for ( unsigned i = 0; i < n; ++i ) {
    strm << "words" << i;
    words.push_back( parser.getXmlStr(strm.str()) );
    strm.clear(); // clear error flags
    strm.str(std::string()); // clear contents
  }

  space[0] = parser.getXmlInt("wordsSpaceX");
  space[1] = parser.getXmlInt("wordsSpaceY");

  string filename = parser.getXmlStr("clickoffFile");
  SDL_Surface* surfaceOff(io.loadAndSet(filename, true));
  Frame clickoff(surfaceOff, 
              parser.getXmlInt("clickoffWidth"), 
              parser.getXmlInt("clickoffHeight"), 
              parser.getXmlInt("clickoffSrcX"), 
              parser.getXmlInt("clickoffSrcX")); 
  clicks.push_back( clickoff );

  filename = parser.getXmlStr("clickonFile");
  SDL_Surface* surfaceOn(io.loadAndSet(filename, true));
  Frame clickon(surfaceOn, 
              parser.getXmlInt("clickonWidth"), 
              parser.getXmlInt("clickonHeight"), 
              parser.getXmlInt("clickonSrcX"), 
              parser.getXmlInt("clickonSrcX")); 
  clicks.push_back( clickon );

}

void Menu::draw() const {
  int x = position[0];
  int y = position[1];
  for (unsigned i = 0; i < words.size(); ++i) {
    io.printMessageAt(words[i], x, y);
    y += space[1];
  }
  y = position[1] + nextIcon*space[1];
  
  //modified by Qiyue
  clicks[click].draw(position[0]-space[0], y - 12);
}

const string& Menu::getIconClicked() const { 
  return words[nextIcon]; 
} 

