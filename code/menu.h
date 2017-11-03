#ifndef MENU__H
#define MENU__H

#include <vector>
#include <string>
#include "frame.h"
#include "ioManager.h"
#include "vector2f.h"

class Menu {
public:
  Menu();
  void draw() const;
  void lightOn() { click = 1; }
  void lightOff() { click = 0; }
  void increment() { nextIcon = (nextIcon + 1) % words.size(); }
  void decrement() { 
    nextIcon = (nextIcon + words.size()-1) % words.size(); 
  }
  const string& getIconClicked() const;
private:
  const IOManager& io;
  std::vector<std::string> words; 
  Vector2f position;
  Vector2f space;
  std::vector<Frame> clicks;
  unsigned nextIcon;
  unsigned click;

  Menu(const Menu&);
  Menu& operator=(const Menu&);
};

#endif
