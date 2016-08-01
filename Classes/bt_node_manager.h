#ifndef BT_NODE_MANAGER_H_
#define BT_NODE_MANAGER_H_

#include "bt_Node.h"
#include "Singleton.h"
#include "tools.h"
#include "struct.h"
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
	BtNode* FindBtNode(int uuid);
	void ClearNode();
protected:
private:
	int id = 0;
	std::vector<BtNode*> m_NodeList;
};

#endif