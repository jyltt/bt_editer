#ifndef XML_FILE_H_
#define XML_FILE_H_

#include "tinyxml2/tinyxml2.h"
#include "Singleton.h"
#include <string>

class BtNode;
struct NodeInfo;

class XmlFile
{
	Singleton(XmlFile);
public:
	NodeInfo* ReadFileToNodeInfo(std::string name);
	int WriteFile(BtNode *root,std::string name);
protected:
	tinyxml2::XMLNode* GetChild(BtNode* node);
	NodeInfo* CreateChild(tinyxml2::XMLElement* node);
private:
	tinyxml2::XMLDocument *m_pDoc;
};

#endif