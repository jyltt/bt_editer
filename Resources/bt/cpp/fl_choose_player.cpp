// author: wuming
#include "fl_choose_player.h"
#include "ex_skill_node.h"
#include "fight_player.h"
#include "SceneManager.h"
#include "buff_manager.h"
#include "fight_event_enum.h"

FL_ChoosePlayer::FL_ChoosePlayer(std::string name)
	:SkillActionNode(name)
	, m_bNeedClearTarget(true)
	, m_eChosePerson(EChosePerson::Enemy)
	, m_bNeedPlayer(true)
{

}

void FL_ChoosePlayer::onBegin()
{
	std::vector<FightPlayer*> _playerList;
	switch (m_eChosePerson)
	{
	case EChosePerson::Enemy:
	{
		auto myCamp = getBuffOwner()->getCamp();
		auto list = SceneManager::getSingleton().GetPlayerMgr().GetPlayerList();
		for (auto player:list)
		{
			if (player->getCamp() != myCamp)
			{
				_playerList.push_back(player);
			}
		}
		break;
	}
	case EChosePerson::Friend:
	{
		auto myCamp = getBuffOwner()->getCamp();
		auto list = SceneManager::getSingleton().GetPlayerMgr().GetPlayerList();
		for (auto player:list)
		{
			if (player->getCamp() == myCamp)
			{
				_playerList.push_back(player);
			}
		}
		break;
	}
	case EChosePerson::Violator:
		break;
	case EChosePerson::Supporter:
		break;
	case EChosePerson::Self:
		_playerList.push_back(getBuffOwner());
		break;
	case EChosePerson::All:
		_playerList = SceneManager::getSingleton().GetPlayerMgr().GetPlayerList();
		break;
	case EChosePerson::BloodLeast:
	{
		auto list = SceneManager::getSingleton().GetPlayerMgr().GetPlayerList();
		int blood = 0;
		for (auto player:list)
		{
			if (blood == 0 || (blood > player->getHP() && player->getHP() != 0))
				blood = player->getHP();
		}
		for (auto player:list)
		{
			if (blood == player->getHP())
				_playerList.push_back(player);
		}
		break;
	}
	default:
		CC_ASSERT(false);
		break;
	}
	if (m_bNeedPlayer)
	{
		m_isChose = false;
		SceneManager::getSingleton().GetUIControlMgr().ShowChosePlayerDlg(_playerList, CC_CALLBACK_2(FL_ChoosePlayer::on_choose, this));
	}
	else
	{
		auto buffMgr = getBuffOwner()->getBuffMgr();
		if (m_bNeedClearTarget)
		{
			buffMgr->clearTargetPlayerList();
		}
		for (auto player:_playerList)
		{
			buffMgr->addTargetPlayer(player);
		}
		m_isChose = true;
	}
}

EBTState FL_ChoosePlayer::onUpdate()
{
	if (m_isChose)
		return EBTState::Success;
	else
		return EBTState::Running;
}

void FL_ChoosePlayer::on_choose(Card* card, void*param)
{
	auto player = (FightPlayer*)param;
	auto buffMgr = getBuffOwner()->getBuffMgr();
	if (m_bNeedClearTarget)
	{
		buffMgr->clearTargetPlayerList();
	}
	buffMgr->addTargetPlayer(player);
	m_isChose = true;
	SceneManager::getSingleton().GetProcessMgr().onUpdate();
}
