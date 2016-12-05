// author: wuming
#ifndef FL_CHOOSE_PLAYER_H_
#define FL_CHOOSE_PLAYER_H_

#include "skill_action_node.h"

class Card;
enum class EChosePerson;

class FL_ChoosePlayer:
	public SkillActionNode
{
public:
	FL_ChoosePlayer(std::string name);
	virtual void onBegin() override;
	EBTState onUpdate()override;
	/**
	//  �Ƿ���Ҫ���֮ǰ�洢������
	**/
	CC_SYNTHESIZE(bool, m_bNeedClearTarget, NeedClearTArget);
	/** 
	//  ѡ���������
	//  �з�
	//  ����
	//  ������
	//  ֧Ԯ��
	//  �Լ�
	//  ������
	//  Ѫ������
	**/
	CC_SYNTHESIZE(EChosePerson, m_eChosePerson, ChosePerson);
	/**
	//  �Ƿ������ѡ��
	**/
	CC_SYNTHESIZE(bool, m_bNeedPlayer, NeedPlayer);
protected:
	void on_choose(Card* card, void* param);
private:
	bool m_isChose=false;

};

#endif
