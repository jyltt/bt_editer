// author: wuming
#ifndef FL_GET_ONE_HAND_CARD_H_
#define FL_GET_ONE_HAND_CARD_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_action_node.h"
#else
#include "bt_action_node.h"
#endif

class FL_GetOneHandCard:
	public BtActionNode
{
public:
	FL_GetOneHandCard(std::string name);
	virtual void onBegin()override;
protected:
private:
};

#endif // !FL_GET_ONE_HAND_CARD_H_
