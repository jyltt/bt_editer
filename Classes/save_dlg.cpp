// author: wuming
#include "save_dlg.h"
#include "editor-support/cocostudio/CocoStudio.h"
#include "bt_node_manager.h"
#include "xml_file.h"
#include "tip_layer.h"

using namespace cocostudio;

bool SaveDlg::init()
{
	if (!Layer::init())
		return false;

	auto _root = CSLoader::createNode("save_dlg.csb");
	addChild(_root);

	auto _ui = (ui::Layout*)_root->getChildByName("Panel_1");
	auto _panel = (ui::Layout*)_ui->getChildByName("bk");
	m_labSaveName = (ui::TextField *)_panel->getChildByName("lab_name");
	m_btnSave = (ui::Button*)_ui->getChildByName("btn_save");
	m_btnSave->addClickEventListener(CC_CALLBACK_1(SaveDlg::onSave, this));
	m_btnCancel = (ui::Button*)_ui->getChildByName("btn_cancel");
	m_btnCancel->addClickEventListener(CC_CALLBACK_1(SaveDlg::onCancel, this));

	return true;
}

void SaveDlg::onSave(Ref* pSender)
{
	auto name = m_labSaveName->getString();
	if (name == "")
	{
		ShowDlg("请输入文件名");
	}
	else
	{
		auto root = BtNodeManager::getSingleton().getRootNode();
		auto error = XmlFile::getSingleton().WriteFile(root, name);
		if (error != 0)
		{
			char str[30] = "";
			sprintf(str, "保存失败 error id:%d", error);
			ShowDlg(str);
		}
		else
			setVisible(false);
	}
}

void SaveDlg::ShowDlg(std::string name)
{
	if (m_dlgTips == nullptr)
	{
		m_dlgTips = TipLayer::create();
		getParent()->addChild(m_dlgTips);
	}
	m_dlgTips->ShowDlg(name);
}

void SaveDlg::onCancel(Ref* pSender)
{
	setVisible(false);
}
