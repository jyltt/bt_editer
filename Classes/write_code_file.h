#ifndef WRITE_CODE_FILE_H_
#define WRITE_CODE_FILE_H_

#include <string>
#include "Singleton.h"

struct NodeInfo;
struct ClassData;
enum class AbortType;
enum class NodeType;

class WriteCodeFile
{
	Singleton(WriteCodeFile);
public:
    std::string WriteFile(std::string xml_file,std::string file_name);
protected:
	std::string GetChild(NodeInfo* parent, NodeInfo* node);
	std::string FileCreateNode(NodeType type, std::string var, std::string class_name);
	std::string FileAddChild(std::string child, std::string parent);
	std::string FileSetAbort(AbortType type, std::string var);
	std::string FileSetAttr(const ClassData &data, std::string var);
private:
	std::string m_FileBuff = "";
};

#endif // !WRITE_CODE_FILE_H_
