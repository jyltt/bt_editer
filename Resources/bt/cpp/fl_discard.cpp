#include "fl_discard.h"
#include "SceneManager.h"
#include "cocos2d.h"

FL_Discard::FL_Discard(std::string name)
	:BtActionNode(name)
{ }

void FL_Discard::onBegin()
{
	SceneManager::getSingleton().GetUIControlMgr().SetMainUIBtn(2, "over", [](){
		SET_FM_TAG("over_discard", 1);
		SceneManager::getSingleton().UpdateGameLogic();
	});
}

EBTState FL_Discard::onUpdate()
{
    BtActionNode::onUpdate();
	SceneManager::getSingleton().GetUIControlMgr().SetShowInfoLab("Running Disscard!!!!!!!");
	CCLOG("Running Disscard!!!!!!!");
	return EBTState::Success;
}