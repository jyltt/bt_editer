#ifndef BT_COMPOSITE_NODE_H_
#define BT_COMPOSITE_NODE_H_

#include "bt_base_node.h"
#include <vector>

class BtCompositeNode :
	public BtBaseNode
{
public:
	BtCompositeNode(std::string name,EBTNodeType type);
	~BtCompositeNode();
	virtual bool AddChild(BtBaseNode *child);
	virtual bool RemoveChild(BtBaseNode *child);
	virtual void Reset()override;
	int Abort();
	CC_SYNTHESIZE(EBTAbortType, m_AbortType, AbortType);
protected:
	int m_curNodeCnt;
	std::vector<BtBaseNode*> m_Childs;
};
#endif