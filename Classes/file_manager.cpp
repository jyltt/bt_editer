// author: wuming
#include "file_manager.h"
#include "struct.h"
#include "Tools.h"
#include "read_file.h"

FileManager::FileManager()
{
}

FileManager::~FileManager()
{
	delete m_DecTree;
	m_DecTree = nullptr;
	for (auto iter = m_listEnum.begin(); iter != m_listEnum.end(); iter++)
	{
		delete iter->second;
	}
	m_listEnum.clear();
}

void FileManager::Init()
{
	m_DecTree = new FileList();
	ReadFile::getSingleton().OpenDoc("bt/", m_DecTree);
}

void FileManager::AddClassData(const std::string &file_name, ClassData* class_data)
{
	m_listClassName2Class[class_data->className] = class_data;
	m_listFileName2Class[file_name] = class_data;
}

ClassData* FileManager::FindClassDataByClassName(const std::string &class_name)
{
	return m_listClassName2Class[class_name];
}

ClassData* FileManager::FindClassDataByFileName(const std::string &file_name)
{
	return m_listFileName2Class[file_name];
}

ClassData* FileManager::FindClassDataByPath(const std::string &path)
{
	auto file_name = Tools::FormPathToName(path);
	return FindClassDataByFileName(file_name);
}

FileList* FileManager::GetFileTree()
{
	return m_DecTree;
}

void FileManager::AddEnumData(EnumData *data)
{
	m_listEnum[data->name] = data;
}

const EnumData& FileManager::GetEnumData(const std::string &name)
{
	return *(m_listEnum[name]);
}
