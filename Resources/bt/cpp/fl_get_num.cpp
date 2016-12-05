// author: wuming
#include "fl_get_num.h"
#include "fight_event_enum.h"
#include "fight_player.h"
#include "buff_manager.h"

FL_GetNum::FL_GetNum(std::string name)
	:SkillActionNode(name)
	, m_eSavePos(ESourceType::BuffOwer)
	, m_eGetNumPos(EStorageLocation::HandCard)
	, m_bNeedSuper(false)
{
}

void FL_GetNum::onBegin()
{
	int num = 0;
	FightPlayer* player=getBuffOwner();
	switch (m_eGetNumPos)
	{
	case EStorageLocation::Weapons:
		num = player->GetWeapons().size();
		break;
	case EStorageLocation::Armor:
		num = player->GetArmor().size();
		break;
	case EStorageLocation::HandCard:
		num = player->GetHandCard().size();
		break;
	case EStorageLocation::Pet:
		num = player->GetPet().size();
		break;
	default:
		break;
	}
	FightPlayer* savePlayer=nullptr;
	switch (m_eSavePos)
	{
	case ESourceType::BuffOwer:
		savePlayer = getBuffOwner();
		break;
	case ESourceType::SkillCreator:
		savePlayer = getSkillCreator();
		break;
	}
	CC_ASSERT(savePlayer==nullptr);
	if (m_bNeedSuper)
	{
		num += savePlayer->getBuffMgr()->getSaveNum();
	}
	savePlayer->getBuffMgr()->setSaveNum(num);
}
