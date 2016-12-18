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
	// 指定卡牌
	AssignCard,
	// 存储的卡牌(技能发动者）
	FromStorageBySkill,
	// 存储的卡牌（buff存储者）
	FromStorageByBuff,
	// 从卡组里获取
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
	// 敌人
	Enemy,
	// 友方
	Friend,
	// 妨碍者
	Violator,
	// 支援者
	Supporter,
	// 自己
	Self,
	// 所有人
	All,
	// 最少血量者
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
