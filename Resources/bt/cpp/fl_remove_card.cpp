// author: wuming
#include "fl_remove_card.h"
#include "ex_skill_node.h"
#include "fight_player.h"
#include "SceneManager.h"
#include "buff_manager.h"
#include "fight_event_enum.h"

FL_RemoveCard::FL_RemoveCard(std::string name)
	:SkillActionNode(name)
    ,m_eCardAccessType(ECardAccessType::AssignCard)
{

}

void FL_RemoveCard::onBegin()
{
	int card_uuid = 0;
	switch (m_eCardAccessType)
	{
    case ECardAccessType::AssignCard:
		card_uuid = m_nUUID;
		break;
    case ECardAccessType::FromStorageBySkill:
	{
		auto cardList = getSkillCreator()->getBuffMgr()->getCard();
		if (cardList.size() < m_nIndex)
			card_uuid = cardList[m_nIndex];
		break;
	}
    case ECardAccessType::FromStorageByBuff:
	{
		auto cardList = getBuffOwner()->getBuffMgr()->getCard();
		if (cardList.size() < m_nIndex)
			card_uuid = cardList[m_nIndex];
		break;
	}
    case ECardAccessType::FromHandCardGroup:
		card_uuid = SceneManager::getSingleton().GetFightMgr().GetCardMgr().GetOneHandCard();
		break;
	default:
		CC_ASSERT(false);
		break;
	}
	if (card_uuid == 0)
		CC_ASSERT(false);
	return;

	getBuffOwner()->RemoveCard(card_uuid, EStorageLocation::All);
}
