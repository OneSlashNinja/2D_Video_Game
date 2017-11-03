#include <map>
#include <string>
#include <stack>
#include <iostream>
using std::cout; using std::endl;
using std::string;

#include <SDL/SDL.h>
#include "ioManager.h"
#include "parseLsysXML.h"

class LSystem {
public:
  LSystem(const string &filename);
  ~LSystem();
  void buildSentence();
  void draw() const;
  void fillSprite();
  void displaySystem() const;
  SDL_Surface* getSurface() const { return spriteSurface; }
private:
  struct State {
    State() : facing(0), x(0), y(0) {}
    int facing;
    int x;
    int y;
  };
private:
  SDL_Surface *screen;
  ParseLsysXML parser;
  std::map<string, string> xmlData;
  SDL_Surface *spriteSurface;
  unsigned width, height;

  State state;

  const Uint32 BLACK;
  const Uint32 MAGENTA;
  const Uint32 WHITE;
  int levels;
  int angle;
  int startX;
  int startY;
  int strokeLength;
  int strokeWidth;
  int facing;
  Uint32 strokeColor;
  char startSymbol;
  std::multimap<char, string> grammar;
  std::stack<State>  stateStack;
  string sentence;

  unsigned findXmlVal( const string& val ) const;
  void printGrammar() const;

  void line32(int x1, int y1, int x2, int y2, Uint32 color);
  void loadSpecification();
  void drawSprite() const;

  LSystem(const LSystem&);
  LSystem& operator=(const LSystem&);
};
