#ifndef BT_ENUM_H_
#define BT_ENUM_H_

enum class EBTNodeType
{
	Action,
	Condition,
	Sequence,
	Selector,
	Parallel,
	Decorate,
	BuffManager,
};

enum class EBTAbortType
{
	//�޴��
	none,
	//�Դ��
	self,
	//����
	priority,
	//���
	both,
};

enum class EBTState
{
	Inaction,
	Failed,
	Success,
	Running,
};

#endif