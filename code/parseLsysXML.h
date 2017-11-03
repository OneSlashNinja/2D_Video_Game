#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <expat.h>

const int BUFLENGTH = 128;

class ParseLsysXML {
public:
  ParseLsysXML(const std::string& fn) : 
    filename(fn),
    parser(NULL), 
    nextToLastTag(), 
    lastTag(),
    lastElementTag(),
    lastNonTerminal(),
    xmlData(),
    grammar()
  { parseXML(); }
  virtual ~ParseLsysXML() { XML_ParserFree(parser); }

  void displayData() const;
  std::map<std::string, std::string> getXmlData() const { return xmlData; }
  std::multimap<char, std::string> getGrammar() const { return grammar; }

  const std::string& getLastTag() const { return lastTag; }
  const std::string& getNextToLastTag() const { return nextToLastTag; }
  float getXmlFloat(const std::string&) const;
  int getXmlInt(const std::string&) const;
  const std::string& getXmlStr(const std::string&) const;

  static void wrapper4Start(void *data, const char *el, const char **attr);
  static void wrapper4End(void *data, const char *el);
  static void wrapper4Chars(void *data, const char *text, int textlen);

private:
  const std::string filename;
  XML_Parser parser;
  char buff[BUFLENGTH];
  std::string  nextToLastTag;
  std::string  lastTag;
  std::string  lastElementTag;
  std::string  lastNonTerminal;

  std::map<std::string, std::string> xmlData;
  std::multimap<char, std::string> grammar;

  void parseXML();
  void start(const char *el, const char *attr[]);
  void end(const char *) {}
  void chars(const char *text, int textlen);

  void stripTrailWhiteSpace(std::string&) const;
  ParseLsysXML& operator=(const ParseLsysXML&);
  ParseLsysXML(const ParseLsysXML&);
};

