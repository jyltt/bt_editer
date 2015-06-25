#ifndef BT_NODE_MANAGER_H_
#define BT_NODE_MANAGER_H_

#include "bt_Node.h"
#include "Singleton.h"
#include <Vector>

class BtNodeManager
{
	Singleton(BtNodeManager);
public:
	CC_SYNTHESIZE(BtNode*, m_RootNode, RootNode);
	BtNode *CreateNode();
	void DeleteNode(BtNode* node);
	BtNode* TouchNode(Vec2 vec);
	void onDraw();
	std::string WriteFile();
protected:
	std::string GetChild(BtNode* parent,BtNode* node);
	std::string GetEnumToString(BtNode::NodeType type);
private:
	std::string m_FileBuff = "";
	int id = 0;
	std::vector<BtNode*> m_NodeList;
};

#endif