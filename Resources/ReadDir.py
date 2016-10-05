import os
import re
import FileRead
import FormatStr

class GetDir:
	def __init__(self):
		self.filedir = {};  # {'filename': ReadFile,}

	def Open(self, dirPath):
		self.dirPath = dirPath
		func = lambda arg,dirname,names: self._Dirwalk(arg,dirname,names);
		os.path.walk(dirPath, func ,0);

	def _Dirwalk(self, arg, dirname, names):
		for name in names:
			path = os.path.join(dirname,name)
			if not os.path.isdir(path) and os.path.splitext(path)[1]==".xml":
				self.filedir[name] = FileRead.FileRead(path);


	def WriteFile(self, file_name):
		file_object = open(file_name, 'wb');
		try:
			file_object.write('#include "bt_list.h"\n\n');
			file_object.write('BTList::BTList()\n');
			file_object.write('{\n');
			for name in self.filedir:
				print "write File:"+name;
				key = os.path.splitext(name)[0];
				node = self.filedir[name].GetRootNode();
				node_type = self.filedir[name].IsSkill();
				if node_type:
					file_object.write('\tm_SkillList["'+key+'"] = \n');
					file_object.write('\t\t[]()->SkillParallelNode*{\n');
					strInfo = FormatStr.FormatStrs(node);
					file_object.write(strInfo);
					file_object.write("\t\t\treturn "+ node["className"] + node["uuid"] +";\n");
					file_object.write("\t\t};\n\n");
				else:
					file_object.write('\tm_BtList["'+key+'"] = \n');
					file_object.write('\t\t[]()->BtParallelNode*{\n');
					strInfo = FormatStr.FormatStrs(node);
					file_object.write(strInfo);
					file_object.write("\t\t\treturn "+ node["className"] + node["uuid"] +";\n");
					file_object.write("\t\t};\n\n");
			file_object.write('}\n');
		finally:
			file_object.close();
