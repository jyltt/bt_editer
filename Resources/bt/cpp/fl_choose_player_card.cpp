// author: wuming
#include "fl_choose_player_card.h"
#include "fight_event_enum.h"
#include "fight_player.h"
#include "buff_manager.h"
#include "SceneManager.h"

FL_ChoosePlayerCard::FL_ChoosePlayerCard(std::string name)
	:SkillActionNode(name)
{
}

void FL_ChoosePlayerCard::onBegin()
{
	FightPlayer* player = nullptr;
	switch (m_eSourceType)
	{
	case ESourceType::BuffOwer:
		player = getBuffOwner();
		break;
	case ESourceType::SkillCreator:
		player = getSkillCreator();
		break;
	}
	CC_ASSERT(player != nullptr);
	std::vector<int> cardList;
	switch (m_eCardType)
	{
	case EStorageLocation::All:
		cardList.insert(cardList.end(), player->GetWeapons().begin(), player->GetWeapons().end());
		cardList.insert(cardList.end(), player->GetArmor().begin(), player->GetArmor().end());
		cardList.insert(cardList.end(), player->GetHandCard().begin(), player->GetHandCard().end());
		break;
	case EStorageLocation::Weapons:
		cardList = player->GetWeapons();
		break;
	case EStorageLocation::Armor:
		cardList = player->GetArmor();
		break;
	case EStorageLocation::HandCard:
		cardList = player->GetHandCard();
		break;
	case EStorageLocation::Pet:
		cardList = player->GetPet();
		break;
	default:
		break;
	}
	if (m_bNeedPlayer)
	{
		SceneManager::getSingleton().GetUIControlMgr().ShowChoseCard(cardList, CC_CALLBACK_2(FL_ChoosePlayerCard::on_choose, this));
		m_isChose = false;
	}
	else
	{
		m_isChose = true;
		auto index = rand()%(cardList.size());
		auto uuid = cardList[index];
		SaveInfo(uuid);
	}
}

EBTState FL_ChoosePlayerCard::onUpdate()
{
	if (m_isChose)
		return EBTState::Success;
	else
		return EBTState::Running;
}

void FL_ChoosePlayerCard::on_choose(Card* card, void* param)
{
	int card_uuid = card->getUUid();
	SaveInfo(card_uuid);
	m_isChose = true;
	SceneManager::getSingleton().GetProcessMgr().onUpdate();
}

void FL_ChoosePlayerCard::SaveInfo(int uuid)
{
	switch (m_eSavePos)
	{
	case ESourceType::BuffOwer:
		getBuffOwner()->getBuffMgr()->addCard(uuid);
		break;
	case ESourceType::SkillCreator:
		getSkillCreator()->getBuffMgr()->addCard(uuid);
		break;
	default:
		break;
	}
}
