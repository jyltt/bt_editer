#ifndef TOOLS_H_
#define TOOLS_H_

#include <iostream>
#include "enum.h"

class Tools
{
public:
	static std::string GetEnumToString(NodeType type);
	static std::string GetEnumToString(AbortType type);
	static NodeType GetNextEnum(NodeType type);
	static AbortType GetNextEnum(AbortType type);
protected:
private:
};

#endif // !TOOLS_H_
