#include "read_file.h"
#ifndef WIN32
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>
#else
#include <io.h>
#endif
#include <fstream>
#include <regex>
#include "Tools.h"
#include "struct.h"
#include "file_manager.h"

ReadFile::ReadFile()
{
}

#ifndef WIN32
void ReadFile::OpenDoc(std::string filepath,FileList *doc)
{
    DIR *dir;
    if(!(dir = opendir(filepath.c_str())))
    {
        return;
    }
    dirent *d_ent;
    char fullpath[128];
    while ( (d_ent = readdir(dir)) != NULL )
    {
        struct stat file_stat;
        if ( strncmp(d_ent->d_name, ".", 1) == 0 )
        {
          continue;   // 忽略"."目录
        }
        memset(fullpath, '\0', sizeof(fullpath));
        strcpy( fullpath,  filepath.c_str());
        if ( !strcmp(fullpath, "/") )
        {
            fullpath[0] = '\0';
        }
        strcat(fullpath, "/");
        strcat(fullpath, d_ent->d_name);
        if ( lstat(fullpath, &file_stat) < 0 )
        {
            return;
        }
        if ((d_ent->d_type&DT_DIR) != 0)
        {
            auto newDoc = new FileList();
            newDoc->docName = d_ent->d_name;
            doc->PushDoc(newDoc);
            doc->docListName.push_back(d_ent->d_name);
            OpenDoc(filepath+d_ent->d_name+"/", newDoc);
        }
        else
        {
            if (strstr(d_ent->d_name, ".h"))
            {
                auto path = filepath+d_ent->d_name;
                doc->fileList.push_back(path);
                ReadClass(path);
            }
        }
    }
    closedir(dir);
}
#else
void ReadFile::OpenDoc(std::string filepath,FileList *doc)
{
	_finddata_t file;
	auto path = filepath+"*.*";
	long lf;
	// ‰»ÎŒƒº˛º–¬∑æ∂  
	if ((lf = _findfirst(path.c_str() , &file))!=-1)
	{
		// ‰≥ˆŒƒº˛√˚  
		while (_findnext(lf, &file)==0)
		{
			if (strcmp(file.name, "..")==0) continue;
			auto b = file.attrib&_A_SUBDIR;
			if ((file.attrib&_A_SUBDIR) != 0)
			{
				auto newDoc = new FileList();
				newDoc->docName = file.name;
				doc->PushDoc(newDoc);
				doc->docListName.push_back(file.name);
				OpenDoc(filepath+file.name+"/", newDoc);
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
#endif

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
			auto type = FindClassType(buff,str);
			if (type == NodeType::Error)
			{
				file.getline(buff, 1000);
				type = FindClassType(buff,str);
			}
			if (type == NodeType::Error)
				continue;

			auto data = new ClassData();
			auto fileName = Tools::FormPathToName(path);
			data->filePath = path.substr(3, path.npos);
			data->className = str;
			data->type = type;
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
					auto new_attr = FindParam(buff, data);
					if (new_attr)
					{
						for (auto attr:data->attrList)
						{
							if (new_attr->name == attr->name)
							{
								delete new_attr;
								new_attr = nullptr;
							}
						}
						if (new_attr)
							data->attrList.push_back(new_attr);
					}
				}

			}
			FileManager::getSingleton().AddClassData(fileName, data);
		}
	}
	file.close();
}

std::string ReadFile::FindClass(char* str)
{
	if(strstr(str, "class"))
	{
		std::string buff = str;
		std::regex re("class +([^ :]+) *:*");
		std::match_results<std::string::const_iterator> result;
		bool valid = std::regex_match(buff, result, re);
		return result[1].str();
	}
	return "";
}

NodeType ReadFile::FindClassType(char* str,std::string class_name)
{
	if (strstr(str, "public "))
	{
		if (strstr(str, "BtCompositeNode"))
		{
			if (class_name.find("BtSequenceNode") != class_name.npos)
				return NodeType::Sequence;
			else if (class_name.find("BtSelectorNode") != class_name.npos)
				return NodeType::Selector;
			else if (class_name.find("BtParallelNode") != class_name.npos)
				return NodeType::Parallel;
			else
				return NodeType::Error;
		}
		else if (strstr(str, "ActionNode"))
			return NodeType::Action;
		else if (strstr(str, "ConditionNode"))
			return NodeType::Condition;
		else if (strstr(str, "DecorateNode"))
			return NodeType::Decorate;
		else if (strstr(str, "SequenceNode"))
			return NodeType::Sequence;
		else if (strstr(str, "SelectorNode"))
			return NodeType::Selector;
		else if (strstr(str, "ParallelNode"))
			return NodeType::Parallel;
		else
			return NodeType::Error;
	}
	else
		return NodeType::Error;
}

Attr *ReadFile::FindParam(std::string str,ClassData* data)
{
	std::match_results<std::string::const_iterator> result;
	std::string name;
	std::string type;
	bool valid = false;
	if (str.find("CC_SYNTHESIZE") != std::string::npos)
	{
		std::regex re(".*CC_SYNTHESIZE\\( *([a-zA-Z:]+) *,.*, *([a-zA-Z]+) *\\);");
		valid = std::regex_match(str, result, re);
		name = result[2].str();
		type = result[1].str();
	}
	else if (str.find("CC_PROPERTY") != std::string::npos)
	{
		std::regex re(".*CC_PROPERTY\\( *([a-zA-Z:]+) *,.*, *([a-zA-Z]+) *\\);");
		valid = std::regex_match(str, result, re);
		name = result[2].str();
		type = result[1].str();
	}
	else if (str.find("set") != std::string::npos)
	{
		std::regex re(".* +set([a-zA-Z]+)\\([^, ]* *([a-zA-Z:^ ]+) +[^,]*\\);?");
		valid = std::regex_match(str, result, re);
		name = result[1].str();
		type = result[2].str();
	}
	else
		return nullptr;
	if (valid)
	{
		auto attr = new Attr();
		if (strstr(type.c_str(), "string"))
		{
			attr->type = AttrType::string;
		}
		else if (strstr(type.c_str(), "bool"))
		{
			attr->type = AttrType::boolean;
		}
		else
		{
			attr->type = AttrType::number;
		}
		attr->name = name;
		return attr;
	}
	return nullptr;
}

ReadFile::~ReadFile()
{
}
