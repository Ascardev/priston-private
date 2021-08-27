int SetQuestBoard()
{
	char	szTemp[512];
	DWORD	dwQCode;
	int		cnt,mcnt;
	sQUEST_CHANGEJOB3 *lpQuest_ChangeJob3;
	char	*lpTitle , *lpMission;
	int		qCnt;


	InterfaceParty.quest_Progress_Clear();
	InterfaceParty.quest_End_Clear();

	dwQCode = sinSaveQuest(szTemp);

	switch( dwQCode )
	{
	case SIN_QUEST_CODE_CHANGEJOB:
		InterfaceParty.quest_Progress_Set("Rank Up #1","ChangeJob1a.Msg");
		break;
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_M:
		InterfaceParty.quest_Progress_Set("Rank Up #1","ChangeJob2a.Msg");
		break;
	case SIN_QUEST_CODE_CHANGEJOB2_NPC_D:
		InterfaceParty.quest_Progress_Set("Rank Up #1","ChangeJob3a.Msg");
		break;
	case SIN_QUEST_CODE_CHANGEJOB3:
		lpQuest_ChangeJob3 = (sQUEST_CHANGEJOB3 *)szTemp;
		lpTitle = "";
		lpMission = lpTitle;
		cnt = 0;
		switch(lpCurPlayer->sCharacterData.JOB_CODE)
		{
		case JOBCODE_MECHANICIAN:
		case JOBCODE_FIGHTER:
		case JOBCODE_PIKEMAN:
		case JOBCODE_KNIGHT:
			cnt = 5;
			break;
		case JOBCODE_ARCHER:
		case JOBCODE_ATALANTA:
		case JOBCODE_ASSASSIN:
			cnt = 8;
			break;
		case JOBCODE_MAGICIAN:
		case JOBCODE_PRIESTESS:
		case JOBCODE_SHAMAN:
			cnt = 11;
			break;
		}

		if (cnt)
		{
			qCnt = 0;

			if (lpQuest_ChangeJob3->State==3)
			{
				if (lpQuest_ChangeJob3->Monster[0]<=1)
					qCnt = 1;
				if (lpQuest_ChangeJob3->Monster[0]==2)
					qCnt = 2;
				if (lpQuest_ChangeJob3->Monster[0]==3)
					qCnt = 3;
				if (lpQuest_ChangeJob3->Monster[0]==4)
					qCnt = 4;
			}

			if (lpQuest_ChangeJob3->State==4)
				qCnt = 4;

			if (lpQuest_ChangeJob3->State==5)
				qCnt = 5;

			lpTitle		= mgQuestName[cnt][0]; 
			lpMission	= mgQuestName[cnt][2];
			InterfaceParty.quest_Progress_Set(lpTitle,lpMission);

			if (qCnt>=1)
			{
				lpTitle		= mgQuestName[cnt][1]; 
				lpMission	= mgQuestName[cnt][3];
				InterfaceParty.quest_Progress_Set(lpTitle,lpMission);
			}
			if (qCnt>=2)
			{
				lpTitle		= mgQuestName[cnt+1][0]; 
				lpMission	= mgQuestName[cnt+1][2];
				InterfaceParty.quest_Progress_Set(lpTitle,lpMission);
			}
			if (qCnt>=3)
			{
				lpTitle		= mgQuestName[cnt+1][1]; 
				lpMission	= mgQuestName[cnt+1][3];
				InterfaceParty.quest_Progress_Set(lpTitle,lpMission);
			}
			if (qCnt>=5)
			{
				lpTitle		= mgQuestName[cnt+2][0]; 
				lpMission	= mgQuestName[cnt+2][2];
				InterfaceParty.quest_Progress_Set(lpTitle,lpMission);
			}
		}
		break;
	case SIN_QUEST_CODE_LEVEL30:
		InterfaceParty.quest_Progress_Set("For Her"		,"LevelQuest\\Quest30.Msg");
		break;

	case SIN_QUEST_CODE_LEVEL55:
		InterfaceParty.quest_Progress_Set("The Cave"		,"LevelQuest\\Quest55.Msg");
		break;

	case SIN_QUEST_CODE_LEVEL55_2:
		InterfaceParty.quest_Progress_Set("The Cave"		,"LevelQuest\\Quest55_2.Msg");
		break;

	case SIN_QUEST_CODE_LEVEL70:
		InterfaceParty.quest_Progress_Set("Helping Michelle"	,"LevelQuest\\Quest70.Msg");
		break;

	case SIN_QUEST_CODE_LEVEL80:
		InterfaceParty.quest_Progress_Set("Enclosed Fury"	,"LevelQuest\\Quest80.Msg");
		break;

	case SIN_QUEST_CODE_LEVEL85:
		InterfaceParty.quest_Progress_Set("Tears of Khalia","LevelQuest\\Quest85.Msg");
		break;

	case SIN_QUEST_CODE_LEVEL90:
		InterfaceParty.quest_Progress_Set("Village of Eura"	,"LevelQuest\\Quest90.Msg");
		break;

	case SIN_QUEST_CODE_LEVEL80_2:
		lpQuest_ChangeJob3 = (sQUEST_CHANGEJOB3 *)szTemp;

		switch(lpQuest_ChangeJob3->State)
		{
		case 1:
			InterfaceParty.quest_Progress_Set("Test of Kingdom","LevelQuest\\Quest_7State_1.msg");
			break;
		case 2:
			InterfaceParty.quest_Progress_Set("Test of Kingdom","LevelQuest\\Quest_7State_2.msg");
			break;
		case 3:
		case 4:
			InterfaceParty.quest_Progress_Set("Test of Kingdom","LevelQuest\\Quest_7State_3.msg");
			break;
		}
		break;
	case SIN_QUEST_CODE_LEVEL90_2:
		lpQuest_ChangeJob3 = (sQUEST_CHANGEJOB3 *)szTemp;
		switch(lpQuest_ChangeJob3->State)
		{
		case 1:
			InterfaceParty.quest_Progress_Set("Bitter Ordeal"		,"LevelQuest\\Quest_10State_1.msg");
			break;
		case 2:
			switch(lpQuest_ChangeJob3->Kind)
			{
			case 13:
				InterfaceParty.quest_Progress_Set("Bitter Ordeal"	,"LevelQuest\\Quest_10State_2_1.msg");
				break;
			case 14:
				InterfaceParty.quest_Progress_Set("Bitter Ordeal"	,"LevelQuest\\Quest_10State_2_2.msg");
				break;
			case 15:
				InterfaceParty.quest_Progress_Set("Bitter Ordeal"	,"LevelQuest\\Quest_10State_2_3.msg");
				break;
			}
			lpCurPlayer->PlayCurseQuest = TRUE;
			break;
		}
		break;
	case SIN_QUEST_CODE_CHANGEJOB4:
		lpQuest_ChangeJob3 = (sQUEST_CHANGEJOB3 *)szTemp;
		switch(lpQuest_ChangeJob3->State)
		{
		case 1:
		case 2:
			InterfaceParty.quest_Progress_Set("Rank Up #2","Quest4\\ChangeJob4_1.msg");
			break;
		case 3:
		case 4:
			InterfaceParty.quest_Progress_Set("Rank Up #2","Quest4\\ChangeJob4_2.msg");
			break;
		case 5:
			switch(lpQuest_ChangeJob3->Kind)
			{
			case MONSTER_SOLID_SNAIL:
				InterfaceParty.quest_Progress_Set("Rank Up #2","Quest4\\ChangeJob4_3_1.msg");
				break;
			case MONSTER_ILLUSION_KNIGHT:
				InterfaceParty.quest_Progress_Set("Rank Up #2","Quest4\\ChangeJob4_3_2.msg");
				break;
			case MONSTER_AVELRISK_LOAD:
				InterfaceParty.quest_Progress_Set("Rank Up #2","Quest4\\ChangeJob4_3_3.msg");
				break;
			case MONSTER_DUSK:
				InterfaceParty.quest_Progress_Set("Rank Up #2","Quest4\\ChangeJob4_3_4.msg");
				break;
			case MONSTER_CHAIN_GOLEM:
				InterfaceParty.quest_Progress_Set("Rank Up #2","Quest4\\ChangeJob4_3_5.msg");
				break;
			case MONSTER_SADNESS:
				InterfaceParty.quest_Progress_Set("Rank Up #2","Quest4\\ChangeJob4_3_6.msg");
				break;
			}
			break;
		case 6:
		case 7:
		case 8:
			InterfaceParty.quest_Progress_Set("Rank Up #2", "Quest4\\ChangeJob4_4.msg");
			break;
		}
		break;
	case HAQUEST_CODE_ELEMENTARY_A:
		if (GetRace(lpCurPlayer->sCharacterData.JOB_CODE) == BROOD_CODE_TEMPSKRON)
			InterfaceParty.quest_Progress_Set("Lollypop","HaQuest\\Quest_Element_T_A.msg");
		else
			InterfaceParty.quest_Progress_Set("Lollypop","HaQuest\\Quest_Element_M_A.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_B:
		if (GetRace(lpCurPlayer->sCharacterData.JOB_CODE) == BROOD_CODE_TEMPSKRON)
			InterfaceParty.quest_Progress_Set("Plastic Hammer","HaQuest\\Quest_Element_T_B.msg");
		else
			InterfaceParty.quest_Progress_Set("Plastic Hammer","HaQuest\\Quest_Element_M_B.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_C:
		InterfaceParty.quest_Progress_Set("Watch Out! Hot Cake!","HaQuest\\Quest_Element_C.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_D:
		InterfaceParty.quest_Progress_Set("Trust of the Town","HaQuest\\Quest_Element_D.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_E:
		InterfaceParty.quest_Progress_Set("Defend the Camp","HaQuest\\Quest_Element_E.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_F:
		InterfaceParty.quest_Progress_Set("For Him","HaQuest\\Quest_Element_F.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_G:
		InterfaceParty.quest_Progress_Set("A Bloody Task","HaQuest\\Quest_Element_G.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_H:
		InterfaceParty.quest_Progress_Set("Food Bandits","HaQuest\\Quest_Element_H.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_I:
		InterfaceParty.quest_Progress_Set("Know your Enemy","HaQuest\\Quest_Element_I.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_J:
		InterfaceParty.quest_Progress_Set("Templers Wish","HaQuest\\Quest_Element_J.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_K:
		InterfaceParty.quest_Progress_Set("Survive or Die","HaQuest\\Quest_Element_K.msg");
		break;
	case HAQUEST_CODE_ELEMENTARY_L:
		InterfaceParty.quest_Progress_Set("Horn of Babel","HaQuest\\Quest_Element_L.msg");
		break;
	case HAQUEST_CODE_FURYOFPHANTOM:
		switch(chaQuest.sHaQuest100LV.State)
		{
		case 1:
		case 2:
		case 3:
			InterfaceParty.quest_Progress_Set("Fury's Phantasma[1]","HaQuest\\Quest_100State_1.msg");				
			break;
		case 4:
			InterfaceParty.quest_Progress_Set("Fury's Phantasma[2]","HaQuest\\Quest_100State_2.msg");				
			break;
		case 7:
		case 5:
		case 6:
		case 8:
			InterfaceParty.quest_Progress_Set("Fury's Phantasma[3]","HaQuest\\Quest_100State_3.msg");				
			break;
		case 9:
		case 10:
			InterfaceParty.quest_Progress_Set("Fury's Phantasma[4]","HaQuest\\Quest_100State_4.msg");				
			break;
		case 11:
		case 12:
			InterfaceParty.quest_Progress_Set("Fury's Phantasma[5]","HaQuest\\Quest_100State_5.msg");				
			break;
		}
		break;
	}

	// 任务完成
	for(cnt=RecordLastQuestInfo.LastQuestCount-1;cnt>=RecordLastQuestInfo.LastQuestCount - LAST_QUEST_MAX;cnt--)
	{
		if (cnt<0)
			break;

		mcnt = cnt & LAST_QUEST_MASK;
		switch( RecordLastQuestInfo.wLastQuest[mcnt])
		{
		case SIN_QUEST_CODE_CHANGEJOB:
		case SIN_QUEST_CODE_CHANGEJOB2_NPC_M:
		case SIN_QUEST_CODE_CHANGEJOB2_NPC_D:
			InterfaceParty.quest_End_Set("Rank Up #1","ChangeJob1b.Msg");
			break;
		case SIN_QUEST_CODE_CHANGEJOB3:
			InterfaceParty.quest_End_Set("Rank Up #1","Quest3\\ChangeJob3-4.msg");
			break;
		case SIN_QUEST_CODE_LEVEL30:
			InterfaceParty.quest_End_Set("For Her","LevelQuest\\Quest30a.Msg");
			break;
		case SIN_QUEST_CODE_LEVEL55:
			InterfaceParty.quest_End_Set("The Cave","LevelQuest\\Quest55a.Msg");
			break;
		case SIN_QUEST_CODE_LEVEL55_2:
			InterfaceParty.quest_End_Set("The Cave","LevelQuest\\Quest55a.Msg");
			break;
		case SIN_QUEST_CODE_LEVEL70:
			InterfaceParty.quest_End_Set("Helping Michelle","LevelQuest\\Quest70a.Msg");
			break;
		case SIN_QUEST_CODE_LEVEL80:
			InterfaceParty.quest_End_Set("Enclosed Fury","LevelQuest\\Quest80a.Msg");
			break;
		case SIN_QUEST_CODE_LEVEL85:
			InterfaceParty.quest_End_Set("Tears of Khalia","LevelQuest\\Quest85a.Msg");
			break;
		case SIN_QUEST_CODE_LEVEL90:
			InterfaceParty.quest_End_Set("Village of Eura","LevelQuest\\Quest90a.Msg");
			break;
		case SIN_QUEST_CODE_LEVEL80_2:
			InterfaceParty.quest_End_Set("Test of Kingdom","LevelQuest\\Quest_7State_end.msg");
			break;
		case SIN_QUEST_CODE_LEVEL90_2:
			InterfaceParty.quest_End_Set("Bitter Ordeal","LevelQuest\\Quest_10State_end.msg");
			lpCurPlayer->PlayCurseQuest = 0;
			break;
		case SIN_QUEST_CODE_CHANGEJOB4:
			InterfaceParty.quest_End_Set("Rank Up #3","Quest4\\ChangeJob4_5.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_A:
			InterfaceParty.quest_End_Set("Lollypop","HaQuest\\Quest_Element_End_A.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_B:
			InterfaceParty.quest_End_Set("Plastic Hammer","HaQuest\\Quest_Element_End_B.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_C:
			InterfaceParty.quest_End_Set("Test of Bravery","HaQuest\\Quest_Element_End_C.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_D:
			InterfaceParty.quest_End_Set("Watch Out! Hot Cake!","HaQuest\\Quest_Element_End_D.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_E:
			InterfaceParty.quest_End_Set("Defend the Camp","HaQuest\\Quest_Element_End_E.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_F:
			InterfaceParty.quest_End_Set("For Him","HaQuest\\Quest_Element_End_F.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_G:
			InterfaceParty.quest_End_Set("A Bloody Task","HaQuest\\Quest_Element_End_G.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_H:
			InterfaceParty.quest_End_Set("Food Bandits","HaQuest\\Quest_Element_End_H.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_I:
			InterfaceParty.quest_End_Set("Know your Enemy","HaQuest\\Quest_Element_End_I.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_J:
			InterfaceParty.quest_End_Set("Templers Wish","HaQuest\\Quest_Element_End_J.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_K:
			InterfaceParty.quest_End_Set("Survive or Die","HaQuest\\Quest_Element_End_K.msg");
			break;
		case HAQUEST_CODE_ELEMENTARY_L:
			InterfaceParty.quest_End_Set("Horn of Babel","HaQuest\\Quest_Element_End_L.msg");
			break;
		case HAQUEST_CODE_FURYOFPHANTOM:
			InterfaceParty.quest_End_Set("Fury's Phantasma","HaQuest\\Quest_100State_6.msg");				
			break;
		}
	}
	return TRUE;
}