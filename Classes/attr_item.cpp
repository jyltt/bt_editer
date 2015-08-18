#include "attr_item.h"
#include "cocostudio/CocoStudio.h"

AttrItem::AttrItem()
{
	setContentSize(Size(200, 40));
    m_RootNode = CSLoader::createNode("attr_list.csb");
	addChild(m_RootNode);

	m_Text = (ui::Text*)m_RootNode->getChildByName("text");
	m_Value = (ui::TextField*)m_RootNode->getChildByName("value");
	m_Value->addEventListener(CC_CALLBACK_2(AttrItem::onChangeValue, this));
}

void AttrItem::SetAttr(Attr *attr)
{
	m_Attr = attr;
	UpdateInfo();
}

void AttrItem::onChangeValue(Ref *ref, ui::TextField::EventType type)
{
	switch (m_Attr->type)
	{
	case AttrType::number:
		m_Attr->number = m_Value->getString();
		break;
	case AttrType::string:
		m_Attr->str = m_Value->getString();
		break;
	default:
		break;
	}
}

void AttrItem::UpdateInfo()
{
	m_Text->setString(m_Attr->name);
	switch (m_Attr->type)
	{
	case AttrType::number:
		m_Value->setString(m_Attr->number);
		break;
	case AttrType::string:
		m_Value->setString(m_Attr->str);
		break;
	default:
		break;
	}
}

AttrItem::~AttrItem()
{

}