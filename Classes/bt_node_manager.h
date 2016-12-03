#ifndef BT_NODE_MANAGER_H_
#define BT_NODE_MANAGER_H_

#include "Singleton.h"
#include "cocos2d.h"
#include <Vector>

class BtNode;

class BtNodeManager
{
	Singleton(BtNodeManager);
public:
	CC_SYNTHESIZE(BtNode*, m_RootNode, RootNode);
	CC_SYNTHESIZE(BtNode*, m_btNode, ChoseNode);
	BtNode *CreateNode();
	void DeleteNode(BtNode* node);
	BtNode* TouchNode(const cocos2d::Vec2 &vec);
	void onDraw();
	BtNode* FindBtNode(int uuid);
	void ClearNode();
protected:
private:
	int id = 0;
	std::vector<BtNode*> m_NodeList;
};

#endif