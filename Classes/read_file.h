#ifndef READ_FILE_H_
#define READ_FILE_H_

#include <vector>
#include <map>
#include "Singleton.h"
#include "struct.h"

class ReadFile
{
	Singleton(ReadFile);
public:
	void LoadFile();
	FileList *GetDoc(std::string doc);
	ClassData* GetNodeClassInfo(std::string name);
protected:
	void OpenDoc(std::string filepath,FileList *doc);
	void ReadClass(std::string path);
	std::string FindClass(char* str);
	NodeType FindClassType(char* str,std::string class_name);
	Attr *FindParam(char* str,ClassData* data);
private:
	FileList* m_DecTree;
	std::map<std::string,ClassData*> m_ClassList;
};
#endif // !READ_FILE_H_
