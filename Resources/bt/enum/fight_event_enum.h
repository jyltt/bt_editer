#ifndef FIGHT_EVENT_ENUM_H_
#define FIGHT_EVENT_ENUM_H_

#define SET_FM_TAG(_key_,_data_) SceneManager::getSingleton().GetProcessMgr().setTag(_key_,_data_)
#define GET_FM_TAG(_key_,_type_,_default_) ((_type_)SceneManager::getSingleton().GetProcessMgr().getTag(_key_) ? *(_type_)SceneManager::getSingleton().GetProcessMgr().getTag(_key_):_default_)

enum class EFL_Flag
{
	None = -1,
	Failure = 0,
	Success = 1,
};

enum class ECardAccessType
{
	// ָ������
	AssignCard,
	// �洢�Ŀ���(���ܷ����ߣ�
	FromStorageBySkill,
	// �洢�Ŀ��ƣ�buff�洢�ߣ�
	FromStorageByBuff,
	// �ӿ������ȡ
	FromHandCardGroup,
};

enum class EStorageLocation
{
	All,
	Weapons,
	Armor,
	HandCard,
	Pet,
};

enum class EChosePerson
{
	// ����
	Enemy,
	// �ѷ�
	Friend,
	// ������
	Violator,
	// ֧Ԯ��
	Supporter,
	// �Լ�
	Self,
	// ������
	All,
	// ����Ѫ����
	BloodLeast,
};

enum class ESourceType
{
	BuffOwer,
	SkillCreator,
};

enum class ECalcType
{
	Add,
	Sub,
	Mul,
	Div,
};
#endif
