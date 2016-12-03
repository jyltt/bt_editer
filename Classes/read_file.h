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
	void OpenDoc(std::string filepath,FileList *doc);
protected:
	void ReadClass(std::string path);
	std::string FindClass(char* str);
	NodeType FindClassType(char* str,std::string class_name);
	Attr *FindParam(std::string str,ClassData* data);
private:
};
#endif // !READ_FILE_H_