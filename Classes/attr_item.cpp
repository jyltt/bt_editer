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
	m_Attr->str = m_Value->getString();
}

void AttrItem::UpdateInfo()
{
	m_Text->setString(m_Attr->name);
	m_Value->setString(m_Attr->str);
}

AttrItem::~AttrItem()
{

}