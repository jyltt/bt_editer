#ifndef TOOLS_H_
#define TOOLS_H_

#include <vector>

enum class NodeType;
enum class AbortType;

class Tools
{
public:
	static std::string GetEnumToString(NodeType type);
	static std::string GetEnumToString(AbortType type);
	static NodeType GetNextEnum(NodeType type);
	static AbortType GetNextEnum(AbortType type);
	static std::string FormPathToName(std::string path);
	static std::vector<std::string> StringSegment(std::string str,std::string delim);
	static std::string StringRemoveChar(std::string str, char ch);
protected:
private:
};

#endif // !TOOLS_H_
