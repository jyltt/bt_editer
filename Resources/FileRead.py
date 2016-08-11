import os
import xml.dom.minidom

class FileRead:
	def __init__(self, path):
		self.filePath = path;
		self.xmlTree = xml.dom.minidom.parse(path);
		self.root = self.xmlTree.documentElement
		self.rootNode = self.ReadXml(self.root);

	def ReadXml(self,nodeInfo):
		nodeType = nodeInfo.getAttribute("type");
		return self.CreateNode(nodeInfo);

	def CreateNode(self,nodeInfo):
		node = {};
		node["className"] = nodeInfo.getAttribute("class_name");
		node["abort"] = nodeInfo.getAttribute("abort");
		node["uuid"] = nodeInfo.getAttribute("uuid");
		node["type"] = nodeInfo.getAttribute("type");
		print "className:"+node["className"]+" abort:"+node["abort"]+" uuid:"+node["uuid"];
		attrList = nodeInfo.getElementsByTagName('attr');
		node["attr"] = [];
		for child in attrList[0].childNodes:
			if child.nodeType == child.ELEMENT_NODE:
				node["attr"].append(self.GetAttrByNode(child));

		children = nodeInfo.getElementsByTagName('child');
		node["children"] = [];
		for child in children[0].childNodes:
			if child.nodeType == child.ELEMENT_NODE:
				node["children"].append(self.ReadXml(child));
		return node;

	def GetAttrByNode(self,node):
		attr = {};
		attr["name"] = node.getAttribute("attr_name");
		attr["value"] = node.getAttribute("attr_value");
		attr["type"] = node.getAttribute("attr_type");
		return attr;

	def GetRootNode(self):
		return self.rootNode;
