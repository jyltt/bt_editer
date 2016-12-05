// author: wuming
#include "fl_get_handcard.h"
#include "ex_skill_node.h"
#include "fight_player.h"
#include "SceneManager.h"
#include "buff_manager.h"

FL_GetHandcard::FL_GetHandcard(std::string name)
	:SkillActionNode(name)
	, m_eStorageLocation(EStorageLocation::HandCard)
	, m_eCardAccessType(ECardAccessType::FromHandCardGroup)
	, m_nIndex(1)
	, m_nUUID(-1)
{

}

void FL_GetHandcard::onBegin()
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

	auto target_list = getBuffOwner()->getBuffMgr()->getTargetPlayer();
	for (auto target:target_list)
	{
		switch (m_eStorageLocation)
		{
		case EStorageLocation::Weapons:
			target->AddWeapons(card_uuid);
			break;
		case EStorageLocation::Armor:
			target->AddArmor(card_uuid);
			break;
		case EStorageLocation::HandCard:
			target->AddHandCard(card_uuid);
			break;
		case EStorageLocation::Pet:
			target->AddPet(card_uuid);
			break;
		default:
			CC_ASSERT(false);
			break;
		}
	}
}
