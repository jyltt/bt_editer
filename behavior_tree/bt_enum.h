#ifndef BT_ENUM_H_
#define BT_ENUM_H_

enum class EBTNodeType
{
	Action,
	Condition,
	Sequence,
	Selector,
	Parallel,
};

enum class EBTAbortType
{
	none,
	self,
	priority,
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