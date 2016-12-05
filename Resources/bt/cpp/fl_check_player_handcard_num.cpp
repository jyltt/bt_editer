// author: wuming
#include "fight_player.h"
#include "fl_check_player_handcard_num.h"
#include "SceneManager.h"
#include "cocos2d.h"

FL_CheckPlayerHandcardNum::FL_CheckPlayerHandcardNum(std::string name)
	:BtConditionNode(name)
	, m_CheckPlayerIndex(-1)
	, m_nCheckNum(3)
{

}

EBTState FL_CheckPlayerHandcardNum::onUpdate()
{
	FightPlayer* curPlayer = nullptr;
	if (m_CheckPlayerIndex != -1)
	{
		auto player = SceneManager::getSingleton().GetPlayerMgr().FindPlayer(m_CheckPlayerIndex);
		if (player != nullptr)
			curPlayer = player;
	}
	else
	{
		curPlayer = SceneManager::getSingleton().GetPlayerMgr().GetCurPlayer();
	}
	CC_ASSERT(curPlayer);
	if (!curPlayer->getIsDead() && curPlayer->GetHandCardNum() > m_nCheckNum)
	{
		m_curState = EBTState::Success;
	}
	else
	{
		m_curState = EBTState::Failed;
	}
	return m_curState;
}
