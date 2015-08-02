#ifndef BT_NODE_MANAGER_H_
#define BT_NODE_MANAGER_H_

#include "bt_Node.h"
#include "Singleton.h"
#include "tools.h"
#include <Vector>

class BtNodeManager
{
	Singleton(BtNodeManager);
public:
	CC_SYNTHESIZE(BtNode*, m_RootNode, RootNode);
	CC_SYNTHESIZE(BtNode*, m_btNode, ChoseNode);
	BtNode *CreateNode();
	void DeleteNode(BtNode* node);
	BtNode* TouchNode(Vec2 vec);
	void onDraw();
	std::string WriteFile();
	BtNode* FindBtNode(int uuid);
protected:
	std::string GetChild(BtNode* parent,BtNode* node);
	std::string FileCreateNode(NodeType type, std::string var,std::string class_name);
	std::string FileAddChild(std::string child, std::string parent);
	std::string FileSetAbort(AbortType type, std::string var);
private:
	std::string m_FileBuff = "";
	int id = 0;
	std::vector<BtNode*> m_NodeList;
};

#endif