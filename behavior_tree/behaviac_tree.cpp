#include "behaviac_tree.h"
#include <map>

namespace BT_Factory
{
	std::map<std::string, int> name_list;
	std::string getUniqueName(std::string name)
	{
		// ·ÀÖ¹ÖØÃû
		if (name_list[name] != 0)
		{
			name_list[name]++;
			name = name + std::to_string(name_list[name]);
		}
		name_list[name]++;
		/////////////end
		return name;
	}
};