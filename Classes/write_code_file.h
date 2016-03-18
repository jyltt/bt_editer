#ifndef WRITE_CODE_FILE_H_
#define WRITE_CODE_FILE_H_

#include "bt_Node.h"
#include "tools.h"
#include "struct.h"
#include "Singleton.h"

class WriteCodeFile
{
	Singleton(WriteCodeFile);
public:
	std::string WriteFile(BtNode *rootNode);
protected:
	std::string GetChild(BtNode* parent, BtNode* node);
	std::string FileCreateNode(NodeType type, std::string var, std::string class_name);
	std::string FileAddChild(std::string child, std::string parent);
	std::string FileSetAbort(AbortType type, std::string var);
	std::string FileSetAttr(ClassData *data, std::string var);
private:
	std::string m_FileBuff = "";
};

#endif // !WRITE_CODE_FILE_H_
