// author: wuming
#ifndef FL_CHOOSE_PLAYER_H_
#define FL_CHOOSE_PLAYER_H_

#include "skill_action_node.h"

class FL_ChoosePlayer:
	public SkillActionNode
{
public:
	FL_ChoosePlayer(std::string name);
	virtual void onBegin() override;
	EBTState onUpdate()override;
protected:
	void on_choose(Card* card, void* param);
private:

};

#endif
