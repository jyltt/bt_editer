#ifndef STRUCT_H_
#define STRUCT_H_

#include <vector>
#include "enum.h"

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
	void PuchDoc(FileList *doc)
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
	AttrType type = AttrType::number;
	std::string name;
	float number = 0;
	std::string str = "";
};
struct ClassData
{
	std::string className;
	NodeType type;
	std::vector<Attr*> attrList;
	~ClassData()
	{
		for (int i = 0; i<attrList.size(); i++)
			delete attrList[i];
		attrList.clear();
	}
};

#endif // !STRUCT_H_
