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
private:
	int id = 0;
	std::vector<BtNode*> m_NodeList;
};

#endif