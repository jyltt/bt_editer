#ifndef FL_DRAW_CARD_H_
#define FL_DRAW_CARD_H_

#include "bt_action_node.h"

//����
class FL_DrawCard:
	public BtActionNode
{
public:
	FL_DrawCard(std::string name);
	virtual void onBegin()override;
	virtual EBTState onUpdate()override;
	virtual void onEnd()override;
protected:
private:
	int i = 0;
};

#endif