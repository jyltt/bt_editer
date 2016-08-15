// author: wuming
#include "tip_layer.h"
#include "editor-support/cocostudio/CocoStudio.h"

using namespace cocostudio;

bool TipLayer::init()
{
	if (!Layer::init())
		return false;

	auto _ui = CSLoader::createNode("tip_layer.csb");
	addChild(_ui);

	m_layBk = (ui::Layout *)_ui->getChildByName("message");
	m_layBk->addClickEventListener(CC_CALLBACK_1(TipLayer::onClickBackground, this));
	m_labDes = (ui::Text *)m_layBk->getChildByName("text");
	m_btnCancel = (ui::Button *)_ui->getChildByName("btn_cancel");
	m_btnCancel->addClickEventListener(CC_CALLBACK_1(TipLayer::onCancel,this));
	m_btnSure = (ui::Button *)_ui->getChildByName("btn_sure");
	m_btnSure->addClickEventListener(CC_CALLBACK_1(TipLayer::onSure,this));
	setVisible(false);

	return true;
}

void TipLayer::ShowDlg(std::string des)
{
	ShowDlg(des, nullptr, nullptr);
}

void TipLayer::ShowDlg(std::string des,std::function<void()> func_sure,std::function<void()> func_cancel )
{
	m_labDes->setString(des);
	m_funcSure = func_sure;
	m_funcCancel = func_cancel;
	if (m_funcSure)
	{
		m_btnSure->setVisible(true);
		m_btnCancel->setVisible(true);
	}
	else
	{
		m_btnSure->setVisible(false);
		m_btnCancel->setVisible(false);
	}
	setVisible(true);
}

void TipLayer::onClickBackground(Ref* pSender)
{
	if (m_funcSure == nullptr)
	{
		HideDlg();
	}
}

void TipLayer::onCancel(Ref* pSender)
{
	if (m_funcCancel)
	{
		m_funcCancel();
	}
	HideDlg();
}

void TipLayer::onSure(Ref* pSender)
{
	if (m_funcSure)
	{
		m_funcSure();
	}
	HideDlg();
}

void TipLayer::HideDlg()
{
	setVisible(false);
}
