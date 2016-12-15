#ifndef STRUCT_H_
#define STRUCT_H_

#include <vector>
#include "enum.h"
#include "cocos2d.h"

struct FileList
{
	std::string docName;
	std::vector<std::string> fileList;
	std::vector<std::string> docListName;
	FileList *FindDoc(std::string name)
	{
		for (auto doc :docList)
		{
			if (doc->docName == name)
				return doc;
		}
		return nullptr;
	}
	void PushDoc(FileList *doc)
	{
		docList.push_back(doc);
	}
	~FileList()
	{
		for (int i = 0; i<docList.size(); i++)
		{
			delete docList[i];
		}
		docList.clear();
	}
private:
	std::vector<FileList*> docList;
};
struct Attr
{
	Attr(Attr *data)
	{
		type = data->type;
		name = data->name;
		strType = data->strType;
		str = data->str;
	}
	Attr() {};
	AttrType type = AttrType::Number;
	std::string name;
	std::string strType = "";
	// value
	std::string str = "";
};
struct EnumData
{
	std::string name;
	std::map<std::string, int> value;
	void PushValue(const std::string &str, const std::string &value)
	{
		if (value.empty())
		{
			this->value[str] = ++lastNum;
		}
		else
		{
			auto num = atoi(value.c_str());
			this->value[str] = num;
			lastNum = num;
		}
	}
private:
	int lastNum=-1;
};
struct ClassData
{
	std::string filePath;
	std::string className;
	NodeType type;
	std::map<std::string, Attr*> attrList;
	ClassData() {};
	ClassData(ClassData *data)
	{
		className = data->className;
		type = data->type;
		for (auto attr:data->attrList)
		{
			attrList[attr.second->name] = new Attr(attr.second);
		}
	}
	void SetAttr(std::string name,std::string value)
	{
		attrList[name]->str = value;
	}
	~ClassData()
	{
		for (auto attr:attrList)
		{
			delete attr.second;
		}
		attrList.clear();
	}
};
struct NodeInfo
{
	ClassData cd;
	int uuid;
	bool isFailure;
	cocos2d::Vec2 pos;
	AbortType abort_type;
	std::vector<NodeInfo*> child_list;
};

#endif // !STRUCT_H_
