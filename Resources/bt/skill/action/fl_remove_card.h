// author: wuming
#pragma once

#include "skill_action_node.h"

enum class ECardAccessType;

class FL_RemoveCard:
	public SkillActionNode
{
public:
	FL_RemoveCard(std::string name);
	virtual void onBegin() override;
	// ��ʲô�ط���ȡ����
	CC_SYNTHESIZE(ECardAccessType, m_eCardAccessType, CardAccessType);
	/* ��������id
	// ������ECardAccessTypeΪFromStorageBySkill����FromStorageByBufʱ��Ч
	// ��ȡbuffmanager���������� ��Ӧλ�ÿ���
	*/
	CC_SYNTHESIZE(int, m_nIndex, CardIndex);
	/* ָ������id
	// ������ECardAccessTypeΪAssignCardʱ��Ч
	*/
	CC_SYNTHESIZE(int, m_nUUID, CardUUID);
protected:
private:
};
