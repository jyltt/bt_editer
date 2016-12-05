#include "fl_end_round.h"
#include "SceneManager.h"
#include "cocos2d.h"

FL_EndRound::FL_EndRound(std::string name)
	:BtActionNode(name)
{ }

EBTState FL_EndRound::onUpdate()
{
    BtActionNode::onUpdate();
	SET_FM_TAG("is_next_player", true);
	SceneManager::getSingleton().GetUIControlMgr().SetShowInfoLab("Running End Round!!!!!!!");
	CCLOG("Running End Round!!!!!!!");
	return EBTState::Success;
}