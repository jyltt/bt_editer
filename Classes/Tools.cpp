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
	case NodeType::Decorate:
		type_str = "Decorate";
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
		return NodeType::Decorate;
	case NodeType::Decorate:
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

std::string Tools::FormPathToName(std::string path)
{
	auto begin = path.find_last_of("\\");
	auto end = path.find_last_of(".");
	auto name = path.substr(begin+1, end-begin-1);
	return name;
}

std::vector<std::string> Tools::StringSegment(std::string str,std::string delim)
{
	std::vector<std::string> ret;
	while (true)
	{
		str = StringRemoveChar(str,' ');
		auto begin = str.find(delim);
		auto buff = str.substr(0, begin);
		buff = StringRemoveChar(buff,' ');
		ret.push_back(buff);
		if (begin != str.npos)
			str = str.substr(begin+1);
		else
			break;
	}
	return ret;
}

std::string Tools::StringRemoveChar(std::string str, char ch)
{
	auto begin = str.find(ch);
	while (begin==0)
	{
		str = str.substr(1);
		begin = str.find(ch);
	}
	auto end = str.find_last_of(ch);
	while (end != str.npos && end==str.size()-1)
	{
		str = str.substr(0,end);
		end = str.find_last_of(ch);
	}
	return str;
}