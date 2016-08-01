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
	setVisible(false);

	return true;
}

void TipLayer::ShowDlg(std::string des)
{
	m_labDes->setString(des);
	setVisible(true);
}

void TipLayer::onClickBackground(Ref* pSender)
{
	HideDlg();
}

void TipLayer::HideDlg()
{
	setVisible(false);
}
