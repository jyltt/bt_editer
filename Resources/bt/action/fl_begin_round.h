#ifndef FL_BEGIN_ROUND_H_
#define FL_BEGIN_ROUND_H_

#ifdef WIN32
#include "tools/bt/node/actions/bt_action_node.h"
#else
#include "bt_action_node.h"
#endif

// 回合开始
class FL_BeginRound:
	public BtActionNode
{
public:
	FL_BeginRound(std::string name);
	virtual void onBegin() override;
	virtual EBTState onUpdate() override;
	virtual void onEnd()override;
protected:
	void onYesCallback();
private:
	bool isOver = false;
};

#endif