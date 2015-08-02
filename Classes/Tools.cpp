#include "Tools.h"

std::string Tools::GetEnumToString(NodeType type)
{
	std::string type_str = "";
	switch (type)
	{
	case NodeType::Sequence:
		type_str = "Sequence";
		break;
	case NodeType::Selector:
		type_str = "Selector";
		break;
	case NodeType::Parallel:
		type_str = "Parallel";
		break;
	case NodeType::Condition:
		type_str = "Condition";
		break;
	case NodeType::Action:
		type_str = "Action";
		break;
	default:
		break;
	}
	return type_str;
}

std::string Tools::GetEnumToString(AbortType type)
{
	std::string type_str = "";
	switch (type)
	{
	case AbortType::none:
		type_str = "none";
		break;
	case AbortType::self:
		type_str = "self";
		break;
	case AbortType::priority:
		type_str = "priority";
		break;
	case AbortType::both:
		type_str = "both";
		break;
	default:
		break;
	}
	return type_str;
}

NodeType Tools::GetNextEnum(NodeType type)
{
	switch (type)
	{
	case NodeType::Sequence:
		return NodeType::Selector;
	case NodeType::Selector:
		return NodeType::Parallel;
	case NodeType::Parallel:
		return NodeType::Condition;
	case NodeType::Condition:
		return NodeType::Action;
	case NodeType::Action:
		return NodeType::Sequence;
	}
}

AbortType Tools::GetNextEnum(AbortType type)
{
	switch (type)
	{
	case AbortType::none:
		return AbortType::self;
	case AbortType::self:
		return AbortType::priority;
	case AbortType::priority:
		return AbortType::both;
	case AbortType::both:
		return AbortType::none;
	}
}