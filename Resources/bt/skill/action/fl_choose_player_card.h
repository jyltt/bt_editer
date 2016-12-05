// author: wuming
#ifndef FL_CHOOSE_PLAYER_CARD_H_
#define FL_CHOOSE_PLAYER_CARD_H_

#include "skill_action_node.h"

class Card;
enum class EStorageLocation;
enum class ESourceType;

class FL_ChoosePlayerCard :
	public SkillActionNode
{
public:
	FL_ChoosePlayerCard(std::string name);
	virtual void onBegin() override;
	EBTState onUpdate()override;
	/**
	//  �Ƿ������ѡ��
	**/
	CC_SYNTHESIZE(bool, m_bNeedPlayer, NeedPlayer);
	/** 
	//  ѡ��λ��
	**/
	CC_SYNTHESIZE(EStorageLocation, m_eCardType, CardType);
	/**
	//  ���������ȡλ��
	**/
	CC_SYNTHESIZE(ESourceType, m_eSourceType, SourceType);
	/** 
	//  ��������λ��
	**/
	CC_SYNTHESIZE(ESourceType, m_eSavePos, SavePos);
protected:
	void on_choose(Card* card, void* param);
	void SaveInfo(int uuid);
private:
	bool m_isChose = false;

};

#endif
