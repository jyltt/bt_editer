import os
import re

NodeType = ("Sequence","Selector","Parallel","Condition","Action","Decorate");
AbortType = ("none","self","priority","both");

def CreateLine(str):
	return "\t\t\t"+str+'\n';

def FormatStrs(node,parent=""):
	print "Format node:"+node["className"];
	type = node["type"];
	strInfo = CreateLine(NodeCreateToStr(node));
	
	if int(type) == 0:# "Sequence"
		strInfo += CreateLine(NodeAbortToStr(node));
	elif int(type) == 1:# "Selector"
		strInfo += CreateLine(NodeAbortToStr(node));
	elif int(type) == 2:# "Parallel"
		strInfo += CreateLine(NodeAbortToStr(node));
	elif int(type) == 3:# "Condition"
		strInfo += NodeAttrToStrs(node);
	elif int(type) == 4:# "Action"
		strInfo += NodeAttrToStrs(node);
	elif int(type) == 5:# "Decorate"
		strInfo += NodeAttrToStrs(node);

	if parent != "":
		strInfo += parent;
		
	strInfo += NodeChildToStrs(node);

	return strInfo;

def NodeCreateToStr(node):
	name = node["className"];
	uuid = node["uuid"];
	return 'auto '+name+uuid+' = BT_Create('+name+', "'+name+'");';

def NodeAbortToStr(node):
	name = node["className"];
	uuid = node["uuid"];
	abort = node["abort"];
	return name+uuid+"->setAbortType(EBTAbortType::"+AbortType[int(abort)]+');';

def NodeAttrToStrs(node):
	name = node["className"];
	uuid = node["uuid"];
	attrList = node["attr"];
	str = "";
	for attr in attrList:
		attrType = int(attr["type"]);
		attrName = attr["name"];
		attrValue = attr["value"];
		attrEnumStr = attr["type_str"];
		if attrValue != "":
			if attrType == 0:#number
				str += CreateLine(name+uuid+'->set'+attrName+'('+attrValue+');');
			elif attrType == 1:#string
				str += CreateLine(name+uuid+'->set'+attrName+'("'+attrValue+'");');
			elif attrType == 2:#bool
				str += CreateLine(name+uuid+'->set'+attrName+'('+attrValue+');');
			elif attrType == 3:#enum
				str += CreateLine(name+uuid+'->set'+attrName+'('+attrEnumStr+"::"+attrValue+');');
	return str;

def NodeChildToStrs(node):
	name = node["className"];
	uuid = node["uuid"];
	childList = node["children"];
	str = "";
	for child in childList:
		childName = child["className"];
		childuuid = child["uuid"];
		buff = CreateLine(name+uuid+'->AddChild('+childName+childuuid+');');
		str = str + FormatStrs(child,buff);
	return str;
