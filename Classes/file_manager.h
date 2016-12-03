// author: wuming
#pragma once

#include "Singleton.h"
#include <map>

struct FileList;
struct ClassData;

class FileManager
{
	Singleton(FileManager);
public:
	void Init();
	FileList* GetFileTree();
	void AddClassData(std::string file_name, ClassData* class_data);
	ClassData* FindClassDataByClassName(std::string name);
	ClassData* FindClassDataByPath(std::string name);
	ClassData* FindClassDataByFileName(std::string name);
protected:
private:
	FileList* m_DecTree;
	std::map<std::string,ClassData*> m_listClassName2Class;
	std::map<std::string,ClassData*> m_listFileName2Class;
};
