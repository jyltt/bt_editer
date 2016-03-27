#ifndef XML_FILE_H_
#define XML_FILE_H_

#include "bt_Node.h"
#include "tinyxml2/tinyxml2.h"
#include "struct.h"
#include "bt_node_manager.h"
#include "Singleton.h"

class XmlFile
{
	Singleton(XmlFile);
public:
	BtNode* CreateNode(std::string name, std::function<BtNode *(cocos2d::Vec2, ClassData*)> set_node);
	void WriteFile(BtNode *root,std::string name);
protected:
	tinyxml2::XMLNode* GetChild(BtNode* node);
	BtNode* CreateChild(tinyxml2::XMLElement* node, std::function<BtNode *(cocos2d::Vec2, ClassData*)> set_node);
private:
	tinyxml2::XMLDocument *m_pDoc;
};

#endif