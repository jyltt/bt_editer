#include "attr_item.h"
#include "cocostudio/CocoStudio.h"
#include <regex>
#include "struct.h"
#include "file_manager.h"

AttrItem::AttrItem()
{
	setContentSize(Size(200, 40));
    m_RootNode = CSLoader::createNode("attr_list.csb");
	addChild(m_RootNode);

	m_Text = (ui::Text*)m_RootNode->getChildByName("text");
	m_bk = (ui::Layout *)m_RootNode->getChildByName("bk");
	m_Value = (ui::TextField*)m_bk->getChildByName("value");
	m_Value->addEventListener(CC_CALLBACK_2(AttrItem::onChangeValue, this));
	m_Check = (ui::CheckBox *)m_RootNode->getChildByName("check");
	m_Check->addEventListener(CC_CALLBACK_2(AttrItem::onChangeCheckValue, this));
	m_btnEnum = (ui::Button *)m_RootNode->getChildByName("enum");
	m_btnEnum->addClickEventListener(CC_CALLBACK_1(AttrItem::onChangeEnum, this));
}

void AttrItem::SetAttr(Attr *attr)
{
	m_Attr = attr;
	UpdateInfo();
}

void AttrItem::onChangeValue(Ref *ref, ui::TextField::EventType type)
{
	auto str =  m_Value->getString();
	switch (m_Attr->type)
	{
	case AttrType::String:
		m_Attr->str = str;
		break;
	case AttrType::Number:
	{
		std::regex re("[0-9]+");
		auto valid = std::regex_match(str, re);
		if (valid)
		{
			m_Attr->str = str;
		}
		else
		{
			m_Value->setString(m_Attr->str);
		}
		break;
	}
	default:
		break;
	}
}

void AttrItem::onChangeCheckValue(Ref *ref, ui::CheckBox::EventType type)
{
	switch (type)
	{
	case cocos2d::ui::CheckBox::EventType::SELECTED:
		m_Attr->str = "true";
		break;
	case cocos2d::ui::CheckBox::EventType::UNSELECTED:
		m_Attr->str = "false";
		break;
	default:
		break;
	}
}

void AttrItem::onChangeEnum(Ref *ref)
{
	auto enumList = FileManager::getSingleton().GetEnumData(m_Attr->strType);
	std::string str;
	bool isFind = false;
	CC_ASSERT(enumList);
	for (auto value:enumList->value)
	{
		if (str.empty())
			str = value.first;
		if (isFind)
		{
			str = value.first;
			break;
		}
		if (value.first==m_Attr->str)
			isFind = true;
	}
	m_Attr->str = str;
	m_btnEnum->setTitleText(str);
}

void AttrItem::UpdateInfo()
{
	m_Text->setString(m_Attr->name);
	switch (m_Attr->type)
	{
	case AttrType::String:
		m_bk->setVisible(true);
		m_Check->setVisible(false);
		m_btnEnum->setVisible(false);
		m_Value->setString(m_Attr->str);
		break;
	case AttrType::Number:
		m_bk->setVisible(true);
		m_Check->setVisible(false);
		m_btnEnum->setVisible(false);
		m_Value->setString(m_Attr->str);
		break;
	case AttrType::Boolean:
		m_bk->setVisible(false);
		m_Check->setVisible(true);
		m_btnEnum->setVisible(false);
		if (m_Attr->str == "true")
			m_Check->setSelectedState(true);
		else
			m_Check->setSelectedState(false);
		break;
	case AttrType::Enum:
		m_bk->setVisible(false);
		m_Check->setVisible(false);
		m_btnEnum->setVisible(true);
		m_btnEnum->setTitleText(m_Attr->str);
	default:
		break;
	}
}

AttrItem::~AttrItem()
{

}