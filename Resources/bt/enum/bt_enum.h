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
	//无打断
	none,
	//自打断
	self,
	//外打断
	priority,
	//打断
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