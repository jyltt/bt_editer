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
void ReadFile::OpenDoc(const std::string &filepath,FileList *doc)
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
				ParsingFile(path);
            }
        }
    }
    closedir(dir);
}
#else
void ReadFile::OpenDoc(const std::string &filepath,FileList *doc)
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
					ParsingFile(path);
				}
			}
		}
	}
	_findclose(lf);
}
#endif

void ReadFile::ParsingFile(const std::string &path)
{
	char buff[1000];
	std::ifstream file(path);
	while(file)
	{
		file.getline(buff, 1000);
		SetBraceNum(buff);
		auto str = FindClass(buff);
		if (!str.empty())
		{
			ReadClass(str, file, path);
		}
		str = FindEnum(buff);
		if (!str.empty())
		{
			ReadEnum(str, file);
		}
	}
	file.close();
}

void ReadFile::ReadClass(const std::string &str,std::ifstream &file,const std::string &path)
{
	char buff[1000];
	auto break_num = m_nbraceNum;
	file.getline(buff, 1000);
	SetBraceNum(buff);
	auto type = FindClassType(buff, str);
	if (type == NodeType::Error)
		return;

	auto data = new ClassData();
	auto fileName = Tools::FormPathToName(path);
	data->filePath = path.substr(3, path.npos);
	data->className = str;
	data->type = type;
	bool isPublic = false;

	while (file)
	{
		file.getline(buff, 1000);
		SetBraceNum(buff);
		if (m_nbraceNum == break_num)
			break;
		if (strstr(buff, "public:"))
			isPublic = true;
		else if (strstr(buff, "private:") || strstr(buff, "protected:"))
			isPublic = false;
		if (isPublic)
		{
			auto new_attr = FindParam(buff, data);
			if (new_attr)
			{
				if (data->attrList.find(new_attr->name) != data->attrList.end())
				{
					delete new_attr;
					new_attr = nullptr;
				}
				else
					data->attrList[new_attr->name] = new_attr;
			}
		}

	}
	FileManager::getSingleton().AddClassData(fileName, data);
}

void ReadFile::ReadEnum(const std::string &str, std::ifstream &file)
{
	char buff[1000];
	auto break_num = m_nbraceNum;
	auto enum_data = new EnumData();
	enum_data->name = str;
	while (file)
	{
		file.getline(buff, 1000);
		SetBraceNum(buff);
		if (m_nbraceNum == break_num)
			break;
		// TODO: 
		std::regex re("\\s(\\w+)\\W*(=\\W*([0-9]+))*,?");
		std::match_results<std::string::const_iterator> result;
		std::string str = buff;
		bool valid = std::regex_match(str, result, re);
		if (valid)
		{
			auto enum_type = result[1].str();
			auto enum_value = result[3].str();
			enum_data->PushValue(enum_type, enum_value);
		}
	}
	FileManager::getSingleton().AddEnumData(enum_data);
}

const std::string ReadFile::FindClass(const std::string &buff)
{
	std::regex re("class +([^ :]+) *:*");
	std::match_results<std::string::const_iterator> result;
	bool valid = std::regex_match(buff, result, re);
	if (valid)
		return result[1].str();
	else
		return "";
}

const std::string ReadFile::FindEnum(const std::string &buff)
{
	std::regex re("enum +(class)? *(\\w+) *\\{*");
	std::match_results<std::string::const_iterator> result;
	bool valid = std::regex_match(buff, result, re);
	if (valid)
		return result[2].str();
	else
		return "";
}

NodeType ReadFile::FindClassType(const std::string &str, const std::string &class_name)
{
	if (str.find("BtCompositeNode") != str.npos)
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
	else if (str.find("ActionNode") != str.npos)
		return NodeType::Action;
	else if (str.find("ConditionNode") != str.npos)
		return NodeType::Condition;
	else if (str.find("DecorateNode") != str.npos)
		return NodeType::Decorate;
	else if (str.find("SequenceNode") != str.npos)
		return NodeType::Sequence;
	else if (str.find("SelectorNode") != str.npos)
		return NodeType::Selector;
	else if (str.find("ParallelNode") != str.npos)
		return NodeType::Parallel;
	else
		return NodeType::Error;
}

Attr *ReadFile::FindParam(const std::string &str,ClassData* data)
{
	std::match_results<std::string::const_iterator> result;
	std::string name;
	std::string type;
	EClassFuncType eType = EClassFuncType::none;
	std::vector<std::string> re_str = 
	{
		"\\W*CC_SYNTHESIZE\\( *([\\w:]+) *,.*, *(\\w+) *\\);?",
		"\\W*CC_PROPERTY\\( *([\\w:]+) *,.*, *(\\w+) *\\);?",
		".* +set([\\w]+)\\(\\w* *([\\w:^ ]+) +[^,]*\\);?",
	};
	for (int i=0;i<re_str.size();i++)
	{
		if (std::regex_match(str, result, std::regex(re_str[i])))
		{
			eType = (EClassFuncType)i;
		}
	}
	switch (eType)
	{
	case ReadFile::EClassFuncType::synthesize:
		name = result[2].str();
		type = result[1].str();
		break;
	case ReadFile::EClassFuncType::property:
		name = result[2].str();
		type = result[1].str();
		break;
	case ReadFile::EClassFuncType::set:
		name = result[1].str();
		type = result[2].str();
		break;
	default:
		return nullptr;
	}
	auto attr = new Attr();
	if (strstr(type.c_str(), "string"))
	{
		attr->type = AttrType::String;
	}
	else if (strstr(type.c_str(), "bool"))
	{
		attr->type = AttrType::Boolean;
	}
	else
	{
		std::regex re("e|E[A-Z][A-Za-z0-9_]*");
		std::match_results<std::string::const_iterator> result;
		bool valid = std::regex_match(type, result, re);
		if (valid)
			attr->type = AttrType::Enum;
		else
			attr->type = AttrType::Number;
	}
	attr->name = name;
	attr->strType = type;
	return attr;
}

void ReadFile::SetBraceNum(const std::string &buff)
{
	if (buff.find("{") != std::string::npos)
		++m_nbraceNum;
	if (buff.find("}") != std::string::npos)
		--m_nbraceNum;
}

ReadFile::~ReadFile()
{
}
