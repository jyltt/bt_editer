// author: wuming
#pragma once

#include "Singleton.h"
#include <map>

struct FileList;
struct ClassData;
struct EnumData;

class FileManager
{
	Singleton(FileManager);
public:
	void Init();
	FileList* GetFileTree();
	void AddClassData(const std::string &file_name, ClassData* class_data);
	ClassData* FindClassDataByClassName(const std::string &name);
	ClassData* FindClassDataByPath(const std::string &name);
	ClassData* FindClassDataByFileName(const std::string &name);
	void AddEnumData(EnumData *data);
	const EnumData &GetEnumData(const std::string &name);
protected:
private:
	FileList* m_DecTree;
	std::map<std::string,ClassData*> m_listClassName2Class;
	std::map<std::string,ClassData*> m_listFileName2Class;
	std::map<std::string, EnumData*> m_listEnum;
};
