#ifndef BT_BASE_NODE_H_
#define BT_BASE_NODE_H_

#include "cocos2d.h"
#include "bt_enum.h"

class BtBaseNode
{
public:
	~BtBaseNode();
	virtual void onBegin();
	virtual EBTState onUpdate() = 0;
	virtual void onEnd();
	CC_SYNTHESIZE(std::string, m_Name, Name);
	CC_SYNTHESIZE(EBTState, m_curState, CurState);
	virtual void Reset();
	EBTNodeType GetNodeType();
protected:
	BtBaseNode(std::string name,EBTNodeType type);
private:
	EBTNodeType m_NodeType;
};
#endif