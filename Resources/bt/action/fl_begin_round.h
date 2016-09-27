#ifndef FL_BEGIN_ROUND_H_
#define FL_BEGIN_ROUND_H_

#include "bt_action_node.h"

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