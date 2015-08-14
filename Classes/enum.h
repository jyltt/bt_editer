#ifndef ENUM_H_
#define ENUM_H_
enum class NodeType
{
	Sequence,
	Selector,
	Parallel,
	Condition,
	Action,
	Decorate,
};
enum class AbortType
{
	none,
	self,
	priority,
	both,
};
enum class ClassType
{
	Function,
	Class,
};
enum class AttrType
{
	number,
	string,
};
#endif