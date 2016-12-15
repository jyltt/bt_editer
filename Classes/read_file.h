#ifndef READ_FILE_H_
#define READ_FILE_H_

#include <vector>
#include <map>
#include "Singleton.h"

enum class NodeType;
struct ClassData;
struct FileList;
struct Attr;

class ReadFile
{
	Singleton(ReadFile);
public:
	enum EClassFuncType {synthesize,property,set,none=-1};
	void OpenDoc(const std::string &filepath,FileList *doc);
protected:
	void ParsingFile(const std::string &path);
	const std::string FindClass(const std::string &str);
	const std::string FindEnum(const std::string &str);
	NodeType FindClassType(const std::string &str, const std::string &class_name);
	Attr *FindParam(const std::string &str,ClassData* data);
	void SetBraceNum(const std::string &buff);
	void ReadClass(const std::string &buff,std::ifstream &file, const std::string &path);
	void ReadEnum(const std::string &buff,std::ifstream &file);
private:
	int m_nbraceNum = 0;
};
#endif // !READ_FILE_H_