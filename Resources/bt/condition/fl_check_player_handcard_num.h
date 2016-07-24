// author: wuming
#ifndef FL_CHECK_PLAYER_HANDCARD_NUM_H_
#define FL_CHECK_PLAYER_HANDCARD_NUM_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_condition_node.h"
#else
#include "bt_condition_node.h"
#endif

class FL_CheckPlayerHandcardNum:
	public BtConditionNode
{
public:
	FL_CheckPlayerHandcardNum(std::string name);
	virtual EBTState onUpdate()override;
	CC_SYNTHESIZE(int, m_nCheckNum, CheckNum);
	CC_SYNTHESIZE(int, m_CheckPlayerIndex, CheckPlayer);
protected:
private:
	bool m_isOver = false;
};

#endif // !FL_CHECK_PLAYER_HANDCARD_NUM_H_
