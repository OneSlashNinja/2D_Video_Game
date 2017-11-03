#include <cstring>
#include <sstream>
#include "parseLsysXML.h"
using std::string;
using std::cout;
using std::endl;

int ParseLsysXML::getXmlInt(const string& tag) const {
  std::map<string, string>::const_iterator ptr = xmlData.find(tag);
  if ( ptr == xmlData.end() )
    throw string("Didn't find integer tag in xml");
  else {
    std::stringstream strm;
    strm << ptr->second;
    int data;
    strm >> data;
    return data;
  }
}

float ParseLsysXML::getXmlFloat(const string& tag) const {
  std::map<string, string>::const_iterator ptr = xmlData.find(tag);
  if ( ptr == xmlData.end() )
    throw string("Didn't find float tag in xml");
  else {
    std::stringstream strm;
    strm << ptr->second;
    int data;
    strm >> data;
    return data;
  }
}

const string& ParseLsysXML::getXmlStr(const string& tag) const {
  std::map<string, string>::const_iterator ptr = xmlData.find(tag);
  if ( ptr == xmlData.end() )
    throw string("Didn't find string tag in xml");
  else return ptr->second;
}

void ParseLsysXML::displayData() const {
  std::map<string, string>::const_iterator ptr = xmlData.begin();
  while ( ptr != xmlData.end() ) {
    cout << ptr->first << ", " << ptr->second << endl;
    ++ptr;
  }
}

void ParseLsysXML::parseXML() {
  parser = XML_ParserCreate(NULL);
  if (!parser) {
    throw string("Couldn't allocate memory for parser");
  }

  XML_SetUserData(parser, this);
  XML_SetElementHandler(parser, wrapper4Start, wrapper4End);
  XML_SetCharacterDataHandler(parser, wrapper4Chars);
  std::fstream in;
  in.open(filename.c_str(), std::ios::in);
  if (!in) { 
    throw string("Cannot open xml file: ")+filename;
  }

  int length = 0;
  in.getline(buff, BUFLENGTH);
  while ( true ) {

    if (! XML_Parse(parser, buff, strlen(buff), length)) {
      cout << "Parse error at line "
	         << XML_GetCurrentLineNumber(parser)
	         << XML_ErrorString(XML_GetErrorCode(parser))
           << endl;
      throw string("Couldn't parse file: ") + filename;
    }

    if ( in.eof() ) break;
    else in.getline(buff, BUFLENGTH);
  }
}

void ParseLsysXML::start(const char *el, const char *attr[]) {
  nextToLastTag = lastTag;
  lastTag = el;
  lastElementTag = el;
  //cout << el;
  for (int i = 0; attr[i]; i += 2) {
    if ( string(el)=="rule" && attr[i]==string("nonterminal") ) { 
      lastNonTerminal = attr[i+1];
    }
  }
}

void ParseLsysXML::stripTrailWhiteSpace(string& str) const {
  int length = str.size();   
  int i = length-1;
  while (i >= 0) { 
    if (str[i] != ' ' && str[i] != '\n' && str[i] != '\t') {
      break;
    }
    else if (str[i] == ' ' || str[i] == '\n' || str[i] == '\t') {
      str.erase(i, 1);
    }
    --i;
  }
}

void ParseLsysXML::chars(const char *text, int textlen) {
  // The text is not zero terminated; thus we need the  length:
  string str(text, textlen);
  // The text is likely to have trailing white space, e.g. newline, etc
  stripTrailWhiteSpace(str);
  if ( str.size() ) {
    if ( lastElementTag == "rule") {
      grammar.insert(std::pair<char,string>(lastNonTerminal[0], str));
    }
    else {
      xmlData.insert(std::pair<string,string>(lastElementTag, str));
    }
  }
}

void ParseLsysXML::
wrapper4Start(void *data, const char *el, const char **attr) {
  ParseLsysXML * parser = static_cast<ParseLsysXML*>(data);
  parser->start(el, attr);
}

void ParseLsysXML::wrapper4End(void *data, const char *el) {
  ParseLsysXML * parser = static_cast<ParseLsysXML*>(data);
  parser->end(el);
}

void ParseLsysXML::wrapper4Chars(void *data, const char *text, int textlen) {
  ParseLsysXML * parser = static_cast<ParseLsysXML*>(data);
  parser->chars(text, textlen);
}

