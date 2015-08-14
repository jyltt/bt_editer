#include "read_file.h"
#include <io.h>
#include <fstream>
#include "Tools.h"

ReadFile::ReadFile()
{
	m_DecTree = new FileList();
	OpenDoc("bt\\",m_DecTree);
}

void ReadFile::OpenDoc(std::string filepath,FileList *doc)
{
	_finddata_t file;
	auto path = filepath+"*.*";
	long lf;
	//输入文件夹路径  
	if ((lf = _findfirst(path.c_str() , &file))!=-1)
	{
		//输出文件名  
		while (_findnext(lf, &file)==0)
		{
			if (strcmp(file.name, "..")==0) continue;
			auto b = file.attrib&_A_SUBDIR;
			if ((file.attrib&_A_SUBDIR) != 0)
			{
				auto newDoc = new FileList();
				newDoc->docName = file.name;
				doc->PuchDoc(newDoc);
				doc->docListName.push_back(file.name);
				OpenDoc(filepath+"\\"+file.name+"\\", newDoc);
			}
			else
			{
				if (strstr(file.name, ".h"))
				{
					auto path = filepath+file.name;
					doc->fileList.push_back(path);
					ReadClass(path);
				}
			}
		}
	}
	_findclose(lf);
}

const FileList &ReadFile::GetDoc(std::string doc)
{
	return *m_DecTree;
}

void ReadFile::ReadClass(std::string path)
{
	char buff[1000];
	std::ifstream file(path);
	while(file)
	{
		file.getline(buff, 1000);
		auto str = FindClass(buff);
		if (str != "")
		{
			auto data = new ClassData();
			auto fileName = Tools::FormPathToName(path);
			m_ClassList[fileName] = data;
			data->className = str;
			bool isPublic = false;
			
			while (file)
			{
				file.getline(buff, 1000);
				if (strstr(buff, "public:"))
					isPublic = true;
				else if (strstr(buff, "private:") || strstr(buff, "protected:"))
					isPublic = false;
				if (isPublic)
				{
					auto attr = FindParam(buff, data);
					if (attr)
						data->attrList.push_back(attr);
				}

			}
		}
	}
	file.close();
}

std::string ReadFile::FindClass(char* str)
{
	if(strstr(str, "class"))
	{
		std::string buff = str;
		std::string className;
		auto end = buff.find(":");
		if (end == buff.npos)
			className = buff.substr(5);
		else
			className = buff.substr(5, end-1-5);
		return className.c_str();
	}
	return "";
}

Attr *ReadFile::FindParam(char* str,ClassData* data)
{
	int begin;
	if (strstr(str, "CC_SYNTHESIZE("))
		begin = sizeof("CC_SYNTHESIZE(");
	else if (strstr(str, "CC_PROPERTY("))
		begin = sizeof("CC_PROPERTY(");
	else
		return nullptr;
	std::string buff = str;
	auto end = buff.find(")");
	if (end == buff.npos)
		buff = buff.substr(begin);
	else
		buff = buff.substr(begin, end-begin);
	auto list = Tools::StringSegment(buff, ",");
	auto attr = new Attr();
	if (strstr(list[0].c_str(), "string"))
	{
		attr->type = AttrType::string;
		attr->name = list[2];
	}
	else
	{
		attr->type = AttrType::number;
		attr->name = list[2];
	}
	return attr;
}

ReadFile::~ReadFile()
{
}
