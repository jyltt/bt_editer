#include "bt_list.h"

BTList::BTList()
{
	m_SkillList["shengguxiaowu"] = 
		[]()->SkillParallelNode*{
			auto SkillParallelNode0 = BT_Create(SkillParallelNode, "SkillParallelNode");
			SkillParallelNode0->setAbortType(EBTAbortType::none);
			auto FL_ChoosePlayer1 = BT_Create(FL_ChoosePlayer, "FL_ChoosePlayer");
			FL_ChoosePlayer1->setChosePerson(EChosePerson::Friend);
			SkillParallelNode0->AddChild(FL_ChoosePlayer1);
			auto FL_GetHandcard5 = BT_Create(FL_GetHandcard, "FL_GetHandcard");
			FL_GetHandcard5->setCardAccessType(ECardAccessType::AssignCard);
			FL_GetHandcard5->setStorageLocation(EStorageLocation::All);
			SkillParallelNode0->AddChild(FL_GetHandcard5);
			auto FL_ChoosePlayer3 = BT_Create(FL_ChoosePlayer, "FL_ChoosePlayer");
			FL_ChoosePlayer3->setChosePerson(EChosePerson::Enemy);
			SkillParallelNode0->AddChild(FL_ChoosePlayer3);
			auto FL_GetHandcard6 = BT_Create(FL_GetHandcard, "FL_GetHandcard");
			FL_GetHandcard6->setCardAccessType(ECardAccessType::AssignCard);
			FL_GetHandcard6->setStorageLocation(EStorageLocation::All);
			SkillParallelNode0->AddChild(FL_GetHandcard6);
			return SkillParallelNode0;
		};

	m_BtList["btTree"] = 
		[]()->BtParallelNode*{
			auto BtParallelNode1 = BT_Create(BtParallelNode, "BtParallelNode");
			BtParallelNode1->setAbortType(EBTAbortType::none);
			auto BtSequenceNode2 = BT_Create(BtSequenceNode, "BtSequenceNode");
			BtSequenceNode2->setAbortType(EBTAbortType::none);
			BtParallelNode1->AddChild(BtSequenceNode2);
			auto FL_BeginRound3 = BT_Create(FL_BeginRound, "FL_BeginRound");
			BtSequenceNode2->AddChild(FL_BeginRound3);
			auto BtSequenceNode4 = BT_Create(BtSequenceNode, "BtSequenceNode");
			BtSequenceNode4->setAbortType(EBTAbortType::none);
			BtParallelNode1->AddChild(BtSequenceNode4);
			auto FL_EvnetCond7 = BT_Create(FL_EvnetCond, "FL_EvnetCond");
			BtSequenceNode4->AddChild(FL_EvnetCond7);
			auto FL_Evnet8 = BT_Create(FL_Evnet, "FL_Evnet");
			BtSequenceNode4->AddChild(FL_Evnet8);
			auto BtSequenceNode7 = BT_Create(BtSequenceNode, "BtSequenceNode");
			BtSequenceNode7->setAbortType(EBTAbortType::self);
			BtParallelNode1->AddChild(BtSequenceNode7);
			auto BtInverterNode8 = BT_Create(BtInverterNode, "BtInverterNode");
			BtSequenceNode7->AddChild(BtInverterNode8);
			auto FL_IsFlag10 = BT_Create(FL_IsFlag, "FL_IsFlag");
			FL_IsFlag10->setFlag("over_drawcard");
			FL_IsFlag10->setDefValue(1);
			BtInverterNode8->AddChild(FL_IsFlag10);
			auto FL_DrawCard9 = BT_Create(FL_DrawCard, "FL_DrawCard");
			BtSequenceNode7->AddChild(FL_DrawCard9);
			auto FL_Running18 = BT_Create(FL_Running, "FL_Running");
			BtSequenceNode7->AddChild(FL_Running18);
			auto BtSequenceNode11 = BT_Create(BtSequenceNode, "BtSequenceNode");
			BtSequenceNode11->setAbortType(EBTAbortType::none);
			BtParallelNode1->AddChild(BtSequenceNode11);
			auto FL_MonsterCond13 = BT_Create(FL_MonsterCond, "FL_MonsterCond");
			BtSequenceNode11->AddChild(FL_MonsterCond13);
			auto FL_MonsterFightBt12 = BT_Create(FL_MonsterFightBt, "FL_MonsterFightBt");
			BtSequenceNode11->AddChild(FL_MonsterFightBt12);
			auto BtSequenceNode14 = BT_Create(BtSequenceNode, "BtSequenceNode");
			BtSequenceNode14->setAbortType(EBTAbortType::none);
			BtParallelNode1->AddChild(BtSequenceNode14);
			auto FL_GetOneHandCard15 = BT_Create(FL_GetOneHandCard, "FL_GetOneHandCard");
			BtSequenceNode14->AddChild(FL_GetOneHandCard15);
			auto FL_IsFlag16 = BT_Create(FL_IsFlag, "FL_IsFlag");
			FL_IsFlag16->setFlag("fight_monster");
			FL_IsFlag16->setDefValue(1);
			BtSequenceNode14->AddChild(FL_IsFlag16);
			auto FL_GetOneHandCard17 = BT_Create(FL_GetOneHandCard, "FL_GetOneHandCard");
			BtSequenceNode14->AddChild(FL_GetOneHandCard17);
			auto BtSequenceNode19 = BT_Create(BtSequenceNode, "BtSequenceNode");
			BtSequenceNode19->setAbortType(EBTAbortType::none);
			BtParallelNode1->AddChild(BtSequenceNode19);
			auto FL_CheckPlayerHandcardNum20 = BT_Create(FL_CheckPlayerHandcardNum, "FL_CheckPlayerHandcardNum");
			BtSequenceNode19->AddChild(FL_CheckPlayerHandcardNum20);
			auto FL_Discard21 = BT_Create(FL_Discard, "FL_Discard");
			BtSequenceNode19->AddChild(FL_Discard21);
			auto FL_Running22 = BT_Create(FL_Running, "FL_Running");
			BtSequenceNode19->AddChild(FL_Running22);
			return BtParallelNode1;
		};

}
