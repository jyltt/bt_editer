#ifndef BEHAVIAC_TREE_H_
#define BEHAVIAC_TREE_H_

#include "bt_enum.h"
#include "bt_selector_node.h"
#include "bt_sequence_node.h"
#include "bt_parallel_node.h"
#include "bt_action_node.h"
#include "bt_condition_node.h"

class BtBaseNode;
class BtCompositeNode;


namespace BT_Factory
{
	std::string getUniqueName(std::string name);
	void PushAbortNode(BtBaseNode*node,int id);
	int ChackAbortNode();
	void ClearAbortNode();
};
#define BT_Create(_class_,_name_) new _class_(BT_Factory::getUniqueName(_name_));

#endif