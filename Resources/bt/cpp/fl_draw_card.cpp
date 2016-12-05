#include "fl_draw_card.h"
#include "SceneManager.h"
#include "cocos2d.h"

FL_DrawCard::FL_DrawCard(std::string name)
	:BtActionNode(name)
{ }

void FL_DrawCard::onBegin()
{
	SceneManager::getSingleton().GetUIControlMgr().SetMainUIBtn(2, "over", [](){
		SET_FM_TAG("over_drawcard", 1);
		SceneManager::getSingleton().GetUIControlMgr().SetMainUIBtn(2, "over", nullptr);
		SceneManager::getSingleton().GetUIControlMgr().SetMainUIBtn(1, "over", nullptr);
		SceneManager::getSingleton().UpdateGameLogic();
	});
	SceneManager::getSingleton().GetUIControlMgr().SetMainUIBtn(1, "update", [](){
		SceneManager::getSingleton().UpdateGameLogic();
	});
}

EBTState FL_DrawCard::onUpdate()
{
    BtActionNode::onUpdate();
	return EBTState::Success;
}

void FL_DrawCard::onEnd()
{
}