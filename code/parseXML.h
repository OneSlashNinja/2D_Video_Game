#ifndef PARSEXML__H
#define PARSEXML__H

#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <expat.h>
using std::map;

using std::cout; using std::endl;
using std::string; 
const int BUFSIZE = 128;

class ParseXML {
public:
  ParseXML( const string& fn ) : 
    filename(fn),
    parser(NULL), 
    nextToLastTag(), 
    lastTag(),
    lastElementTag(),
    lastNonTerminal(),
    xmlData()
  { parseXML(); }
  virtual ~ParseXML() { XML_ParserFree(parser); }

  void displayData() const;
  const map<string, string> getXmlData() const { return xmlData; }

  const string& getLastTag() const { return lastTag; }
  const string& getNextToLastTag() const { return nextToLastTag; }

  float getXmlFloat(const string&) const;
  int getXmlInt(const string&) const;
  const string& getXmlStr(const string&) const;

  static void wrapper4Start(void *data, const char *el, const char **attr);
  static void wrapper4End(void *data, const char *el);
  static void wrapper4Chars(void *data, const char *text, int textlen);

private:
  const string filename;
  XML_Parser parser;
  char buff[BUFSIZE];
  string  nextToLastTag;
  string  lastTag;
  string  lastElementTag;
  string  lastNonTerminal;

  std::map<string, string> xmlData;

  void parseXML();
  void start(const char *el, const char *attr[]);
  void end(const char *) {}
  void chars(const char *text, int textlen);

  void stripTrailWhiteSpace(string&) const;
  ParseXML& operator=(const ParseXML&);
  ParseXML(const ParseXML&);
};

#endif
