#include "StdAfx.h"


char *haQuestFilePathA[] = {
	"image\\Sinimage\\Quest\\haQuesttired_Astart.sin",
		"image\\Sinimage\\Quest\\haQuesttired_Apass1.sin",
		"image\\Sinimage\\Quest\\haQuesttired_Apass.sin",
		"image\\Sinimage\\Quest\\haQuesttired_Aend.sin",
};
char *haQuestFilePathB[] = {
	"image\\Sinimage\\Quest\\haQuestterrified_Bstart_M.sin",
		"image\\Sinimage\\Quest\\haQuestterrified_Bstart_T.sin",
		"image\\Sinimage\\Quest\\haQuestterrified_Bpass_M.sin",
		"image\\Sinimage\\Quest\\haQuestterrified_Bpass_T.sin",
		"image\\Sinimage\\Quest\\haQuestterrified_Bend.sin",
};
char *haQuestFilePathC[] = {
	"image\\Sinimage\\Quest\\haQuestcandy_Cstart_M.sin",
		"image\\Sinimage\\Quest\\haQuestcandy_Cstart_T.sin",
		"image\\Sinimage\\Quest\\haQuestcandy_Cpass.sin",
		"image\\Sinimage\\Quest\\haQuestcandy_Cend.sin",
};
char *haQuestFilePathD[] = {
	"image\\Sinimage\\Quest\\haQuestGoblin_Dstart_M.sin",
		"image\\Sinimage\\Quest\\haQuestGoblin_Dstart_T.sin",
		"image\\Sinimage\\Quest\\haQuestGoblin_Dpass_M.sin",
		"image\\Sinimage\\Quest\\haQuestGoblin_Dpass_T.sin",
		"image\\Sinimage\\Quest\\haQuestGoblin_Dend.sin",
};
char *haQuestFilePathE[] = {
	"image\\Sinimage\\Quest\\haQuestundead_Estart_M.sin",
		"image\\Sinimage\\Quest\\haQuestundead_Estart_T.sin",
		"image\\Sinimage\\Quest\\haQuestundead_Epass_M.sin",
		"image\\Sinimage\\Quest\\haQuestundead_Epass_T.sin",
		"image\\Sinimage\\Quest\\haQuestundead_Eend.sin",
};
char *haQuestFilePathF[] = {
	"image\\Sinimage\\Quest\\haQuestcyclops_Fstart.sin",
		"image\\Sinimage\\Quest\\haQuestcyclops_Fpass.sin",
		"image\\Sinimage\\Quest\\haQuestcyclops_Fend.sin",
};
char *haQuestFilePathG[] = {
	"image\\Sinimage\\Quest\\haQuesthammer_Gstart.sin",
		"image\\Sinimage\\Quest\\haQuesthammer_Gpass.sin",
		"image\\Sinimage\\Quest\\haQuesthammer_Gend.sin",
};
char *haQuestLevelOver = {
	"image\\Sinimage\\Quest\\haQuestLevel_Over.sin",
};

/*----------------------------------------------------------------------------*
*							傈开 函荐
*-----------------------------------------------------------------------------*/
DWORD haElementaryQuestLog = 0; //檬焊 譬配府倔 涅胶飘 荐青咯何

cHaQuest chaQuest;

cHaQuest::cHaQuest()
{
	iJob_Index = 0;

	bFuryQuestFlag = false;
	iFuryQuestIndex[0] = 0;
	iFuryQuestIndex[1] = 0;

}

cHaQuest::~cHaQuest()
{

}
/*----------------------------------------------------------------------------*
*							haCheckQuest
*-----------------------------------------------------------------------------*/
int cHaQuest::haQuestCheck(int CODE)
{
	for (int cnt = 0; cnt < MAX_HAQUEST_ELEMENTARY; cnt++)
	{
		if (sHaQuestElementary[cnt].CODE && sHaQuestElementary[cnt].CODE != CODE)
		{
			cMessageBox.ShowMessage(MESSAGE_QUEST_NOW_EXIT);
			return FALSE;
		}
	}
	if (sHaQuest100LV.CODE && sHaQuest100LV.CODE != CODE)
	{
		cMessageBox.ShowMessage(MESSAGE_QUEST_NOW_EXIT);
		return FALSE;
	}

	return TRUE;
}

/*----------------------------------------------------------------------------*
*							HaCheckQuestElementary
*-----------------------------------------------------------------------------*/
int cHaQuest::HaCheckQuestElementary(int npcNum, int QuestKey, int KindClan)
{
	/*if(cSinHelp.sinGetHelpShowFlag() || CheckNowQuestState(0) == FALSE)
		return FALSE;
	if(sinChar->Level > 39)
	{
		if(npcNum==0)
		{
			for(int i=0;i<8;i++)
			{
				if(chaQuest.sHaQuestElementary[i].CODE)
				{
					memset(&chaQuest.sHaQuestElementary[i],0,sizeof(sQUEST_ELEMENTARY));
					cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
					DeleteQuestItem(sinQT1|sin14);
					DeleteQuestItem(sinQT1|sin15);
					DeleteQuestItem(sinQT1|sin16);
				}
			}
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_X,QuestMessageBoxPosi2.x,QuestMessageBoxPosi2.y,QuestMessageBoxSize2.x,QuestMessageBoxSize2.y,D3DCOLOR_RGBA(0,15,128,125),haQuestLevelOver);
		}
		return FALSE;
	}
	int cnt=0;

	if(sinChar->JOB_CODE < 5)
		iJob_Index = 1;
	else
		iJob_Index = 2;

	if((QUESTBIT_ELEMENTARY_A & haElementaryQuestLog)==QUESTBIT_ELEMENTARY_A)
		cnt++;
	if((QUESTBIT_ELEMENTARY_B & haElementaryQuestLog)==QUESTBIT_ELEMENTARY_B)
		cnt++;
	if((QUESTBIT_ELEMENTARY_C & haElementaryQuestLog)==QUESTBIT_ELEMENTARY_C)
		cnt++;
	if((QUESTBIT_ELEMENTARY_D & haElementaryQuestLog)==QUESTBIT_ELEMENTARY_D)
		cnt++;
	if((QUESTBIT_ELEMENTARY_E & haElementaryQuestLog)==QUESTBIT_ELEMENTARY_E)
		cnt++;
	if((QUESTBIT_ELEMENTARY_F & haElementaryQuestLog)==QUESTBIT_ELEMENTARY_F)
		cnt++;
	if((QUESTBIT_ELEMENTARY_G & haElementaryQuestLog)==QUESTBIT_ELEMENTARY_G)
		cnt++;

	QuestKeyCode = cnt;

	KindClanIndex=0;

	if(KindClan)
		KindClanIndex = KindClan;
	if(QuestKey)
	{
		if(QuestKey != cnt+1)
			return FALSE;
	}

	switch(cnt)
	{
	case 0:
		haElementaryQuest_A(npcNum);
		break;
	case 1:
		if(npcNum==0)
			haElementaryQuest_B();
		break;
	case 2:
		haElementaryQuest_C(npcNum);
		break;
	case 3:
		haElementaryQuest_D(npcNum);
		break;
	case 4:
		haElementaryQuest_E(npcNum);
		break;
	case 5:
		if(npcNum==0)
			haElementaryQuest_F();
		break;
	case 6:
		haElementaryQuest_G(npcNum);
		break;
	}*/
	return FALSE;
}
int cHaQuest::haElementaryQuest_A(int npcNum)
{
	switch (npcNum)
	{
	case 0:
		if (CheckNowQuestState(0) == FALSE)
			return TRUE;

		if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_A) == FALSE)
			return TRUE;

		if ((QUESTBIT_ELEMENTARY_A & haElementaryQuestLog) == 0)
		{
			switch (sHaQuestElementary[Quest_A].State)
			{
			case 0:
				cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_A, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Astart.sin");
				return TRUE;
			case 1:
				cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_A, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Apass1.sin");
				return TRUE;
			case 2:
				cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_A, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Aend.sin");
				return TRUE;
			}
		}
		break;
	case 1:
		if (CheckNowQuestState(0) == FALSE)
			return TRUE;

		if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_A) == FALSE)
			return TRUE;

		if ((QUESTBIT_ELEMENTARY_A & haElementaryQuestLog) == 0)
		{
			switch (sHaQuestElementary[Quest_A].State)
			{
			case 1:
				if (cInvenTory.SearchItemCode(sinQT1 | sin14))
					cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_A, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Apass.sin", npcNum);
				return TRUE;
			}
		}
		break;
	}

	return FALSE;
}
// 5级任务
int cHaQuest::haElementaryQuest_B(int Race)
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_B) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 5 && (QUESTBIT_ELEMENTARY_B & haElementaryQuestLog) == 0)
	{
		switch (sHaQuestElementary[Quest_B].State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_B, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Bstart.sin");
			return TRUE;
		case 1:
			if (cInvenTory.SearchItemCode(sinQT1 | sin16) == FALSE)
				cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_B, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Bpass.sin");
			else
				cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_B, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Bend.sin");
			return TRUE;
		}
	}

	return FALSE;
}
// 10级任务
int cHaQuest::haElementaryQuest_C()
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_C) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 10 && (QUESTBIT_ELEMENTARY_C & haElementaryQuestLog) == 0)
	{
		switch (sHaQuestElementary[Quest_C].State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_C, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Cstart.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_C, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Cpass.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_C, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Cend.sin");
			return TRUE;
		}
	}

	return FALSE;
}
//15级任务
int cHaQuest::haElementaryQuest_D(int npcNum)
{
	switch (npcNum)
	{
	case 0:
		if (CheckNowQuestState(0) == FALSE)
			return TRUE;

		if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_D) == FALSE)
			return TRUE;

		if (sinChar->iLevel >= 15 && (QUESTBIT_ELEMENTARY_D & haElementaryQuestLog) == 0)
		{
			switch (sHaQuestElementary[Quest_D].State)
			{
			case 0:
				cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_D, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Dstart.sin");
				return TRUE;
			case 1:
				cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_D, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Dpass1.sin");
			case 2:
				cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_D, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Dpass.sin");
				return TRUE;
			}
		}
		break;
	case 1:
		if (CheckNowQuestState(0) == FALSE)
			return TRUE;

		if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_D) == FALSE)
			return TRUE;

		if (sinChar->iLevel >= 15 && (QUESTBIT_ELEMENTARY_D & haElementaryQuestLog) == 0)
		{
			switch (sHaQuestElementary[Quest_D].State)
			{
			case 2:
				if (cSkill.SearchContiueSkill(CHANGE_ELEMENTARY_QUEST) && cInvenTory.SearchItemCode(sinQT1 | sin15))
				{
					cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_D, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Dend.sin", npcNum);
					return TRUE;
				}
				else
					cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_D, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Dpass1.sin", npcNum);
				break;
			}
		}
		break;
	}
	return FALSE;
}
// 25级任务
int cHaQuest::haElementaryQuest_E()
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_E) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 25 && sinChar->iRank >= 1 && (QUESTBIT_ELEMENTARY_E & haElementaryQuestLog) == 0)
	{
		switch (sHaQuestElementary[Quest_E].State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_E, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Estart.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_E, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Epass.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_E, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Eend.sin");
			return TRUE;
		}
	}

	return FALSE;
}
// 35级任务
int cHaQuest::haElementaryQuest_F()
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_F) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 35 && sinChar->iRank >= 1 && (QUESTBIT_ELEMENTARY_F & haElementaryQuestLog) == 0)
	{
		switch (sHaQuestElementary[Quest_F].State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_F, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Fstart.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_F, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Fpass.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_F, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Fend.sin");
			return TRUE;
		}
	}

	return FALSE;
}
// 45级任务
int cHaQuest::haElementaryQuest_G()
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_G) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 45 && sinChar->iRank >= 2 && (QUESTBIT_ELEMENTARY_G & haElementaryQuestLog) == 0)
	{
		switch (sHaQuestElementary[Quest_G].State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_G, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Gstart.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_G, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Gpass.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_G, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Gend.sin");
			return TRUE;
		}
	}
	return FALSE;
}
int cHaQuest::haElementaryQuest_H()
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_H) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 50 && sinChar->iRank >= 2 && (QUESTBIT_ELEMENTARY_H & haElementaryQuestLog) == 0)
	{
		switch (sHaQuestElementary[Quest_H].State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_H, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Hstart.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_H, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Hpass.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_H, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Hend.sin");
			return TRUE;
		}
	}

	return FALSE;
}
int cHaQuest::haElementaryQuest_I()
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_I) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 65 && sinChar->iRank >= 3 && (QUESTBIT_ELEMENTARY_I & haElementaryQuestLog) == 0)
	{
		switch (sHaQuestElementary[Quest_I].State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_I, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Istart.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_I, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Ipass.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_I, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Iend.sin");
			return TRUE;
		}
	}
	return FALSE;
}
int cHaQuest::haElementaryQuest_J()
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_J) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 75 && sinChar->iRank >= 3 && (QUESTBIT_ELEMENTARY_J & haElementaryQuestLog) == 0)
	{
		switch (sHaQuestElementary[Quest_J].State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_J, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Jstart.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_J, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Jpass.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_J, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Jend.sin");
			return TRUE;
		}
	}
	return FALSE;
}
// 85级任务
int cHaQuest::haElementaryQuest_K()
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_K) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 85 && sinChar->iRank >= 4 && (QUESTBIT_ELEMENTARY_K & haElementaryQuestLog) == 0)
	{
		switch (sHaQuestElementary[Quest_K].State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_K, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Kstart.sin");
			return TRUE;
		case 1:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_K, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Kpass.sin");
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_K, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Kend.sin");
			return TRUE;
		}
	}
	return FALSE;
}
// 95级任务
int cHaQuest::haElementaryQuest_M()
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(HAQUEST_CODE_ELEMENTARY_L) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 95 && sinChar->iRank >= 4 && (QUESTBIT_ELEMENTARY_L & haElementaryQuestLog) == 0)
	{
		switch (sHaQuestElementary[Quest_L].State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_L, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Lstart.sin");
			return TRUE;
		case 1:
			if (cInvenTory.SearchItemCode(sinQT1 | sin19))
				cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_L, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Lend.sin");
			else
				cSinHelp.sinShowHelp(HAQUEST_CODE_ELEMENTARY_L, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), "image\\Sinimage\\Quest\\haQuesttired_Lpass.sin");
			return TRUE;
		}
	}
	return FALSE;
}
int cHaQuest::haSetQuestTimer(int Time)
{
	sSKILL TempSkill;
	int Flag;
	memset(&TempSkill, 0, sizeof(sSKILL));

	char *Path = "image\\Sinimage\\skill\\keep\\QuestTimer.tga";
	if (!MatQuestTimer)
	{
		MatQuestTimer = CreateTextureMaterial(Path, 0, 0, 0, SMMAT_BLEND_ALPHA);
		ReadTextures();
	}

	if (Time == 0)
	{
		TempSkill.UseTime = 70 * 70;
		Flag = TRUE;
	}
	else
	{
		TempSkill.UseTime = Time;
		Flag = FALSE;
	}

	TempSkill.CODE = CHANGE_ELEMENTARY_QUEST;
	TempSkill.Point = 1;
	TempSkill.MatIcon = MatQuestTimer;
	sinContinueSkillSet(&TempSkill, Flag);
	sinPlaySound(SIN_SOUND_EAT_POTION2);
	return TRUE;
}
void HaCheckQuestNpc(int NpcCount)
{
	switch (NpcCount)
	{
	case 1014:
		chaQuest.HaCheckQuestElementary(0);
		break;
	case 1015:
		chaQuest.HaCheckQuestElementary(1, 1, 1);
		break;
	case 1016:
		chaQuest.HaCheckQuestElementary(1, 1, 2);
		break;
	case 1017:
		chaQuest.HaCheckQuestElementary(1, 3, 2);
		break;
	case 1018:
		chaQuest.HaCheckQuestElementary(1, 3, 1);
		break;
	case 1019:
		chaQuest.HaCheckQuestElementary(1, 4, 1);
		break;
	case 1020:
		chaQuest.HaCheckQuestElementary(1, 4, 2);
		break;
	case 1021:
		chaQuest.HaCheckQuestElementary(1, 5);
		break;
	case 1022:
		chaQuest.HaCheckQuestElementary(1, 7);
		break;
	}
}
/*----------------------------------------------------------------------------*
*					  Main
*-----------------------------------------------------------------------------*/
void cHaQuest::init()
{
	lpQuestItemImage[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\Items\\Weapon\\itwa120.bmp");
	lpQuestItemImage[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\Items\\Weapon\\itwc120.bmp");
	lpQuestItemImage[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Items\\Weapon\\itwh121.bmp");
	lpQuestItemImage[3] = LoadDibSurfaceOffscreen("image\\Sinimage\\Items\\Weapon\\itwp121.bmp");
	lpQuestItemImage[4] = LoadDibSurfaceOffscreen("image\\Sinimage\\Items\\Weapon\\itws122.bmp");
	lpQuestItemImage[5] = LoadDibSurfaceOffscreen("image\\Sinimage\\Items\\Weapon\\itws223.bmp");
	lpQuestItemImage[6] = LoadDibSurfaceOffscreen("image\\Sinimage\\Items\\Weapon\\itwt121.bmp");
	lpQuestItemImage[7] = LoadDibSurfaceOffscreen("image\\Sinimage\\Items\\Weapon\\itwm121.bmp");
	lpQuestItemImage[8] = LoadDibSurfaceOffscreen("image\\Sinimage\\Items\\Weapon\\itwd121.bmp");
	lpQuestItemImage[9] = LoadDibSurfaceOffscreen("image\\Sinimage\\Items\\Weapon\\itwn121.bmp");

	lpQuestButtonImage[0] = LoadDibSurfaceOffscreen("image\\Sinimage\\shopall\\LeftArrow.bmp");
	lpQuestButtonImage[1] = LoadDibSurfaceOffscreen("image\\Sinimage\\shopall\\RightArrow.bmp");
	lpQuestButtonImage[2] = LoadDibSurfaceOffscreen("image\\Sinimage\\Inven\\LeftArrow.bmp");
	lpQuestButtonImage[3] = LoadDibSurfaceOffscreen("image\\Sinimage\\Inven\\RightArrow.bmp");

	memset(&cItemName, 0, sizeof(cItemName));
	sHaQuest100LV.State = 0;
	FuryBattleFlag = false;

}
int ItemButtonFlag[2] = { 0 };
/*----------------------------------------------------------------------------*
*					  Main
*-----------------------------------------------------------------------------*/
void cHaQuest::Main()
{
	if (sHaQuest100LV.State && sHaQuest100LV.State == 13)
	{
		if (pCursorPos.x > 100 && pCursorPos.x < 100 + 20 && pCursorPos.y >365 && pCursorPos.y < 365 + 20)
			ItemButtonFlag[0] = 1;
		else if (pCursorPos.x > 330 && pCursorPos.x < 330 + 20 && pCursorPos.y >365 && pCursorPos.y < 365 + 20)
			ItemButtonFlag[1] = 1;
		else
		{
			ItemButtonFlag[0] = 0;
			ItemButtonFlag[1] = 0;
		}
	}
}
/*----------------------------------------------------------------------------*
*					  Draw
*-----------------------------------------------------------------------------*/
void cHaQuest::Draw()
{
	if (bFuryQuestFlag == true)
	{
		switch (iFuryQuestIndex[1])
		{
		case 1: // 斧子
		case 3:
		case 4:
		case 5:
		case 6:
		case 8:
		case 9:
			DrawSprite(100, 130, lpQuestItemImage[iFuryQuestIndex[1] - 1], 0, 0, 44, 88);
			break;
		case 2: // 爪
			DrawSprite(100, 130, lpQuestItemImage[iFuryQuestIndex[1] - 1], 0, 0, 44, 66);
			break;
		case 7: // 标
			DrawSprite(100, 130, lpQuestItemImage[iFuryQuestIndex[1] - 1], 0, 0, 22, 88);
			break;
		case 10: // 魔晶
			DrawSprite(100, 130, lpQuestItemImage[iFuryQuestIndex[1] - 1], 0, 0, 66, 44);
			break;
		}
		if (sHaQuest100LV.State == 13)
		{
			if (ItemButtonFlag[0])
				DrawSprite(100, 365, lpQuestButtonImage[2], 0, 0, 20, 20);
			else
				DrawSprite(100, 365, lpQuestButtonImage[0], 0, 0, 20, 20);
			if (ItemButtonFlag[1])
				DrawSprite(330, 365, lpQuestButtonImage[3], 0, 0, 20, 20);
			else
				DrawSprite(330, 365, lpQuestButtonImage[1], 0, 0, 20, 20);
		}
	}
}
/*----------------------------------------------------------------------------*
*					  KeyDown
*-----------------------------------------------------------------------------*/
void cHaQuest::KeyDown()
{

}
/*----------------------------------------------------------------------------*
*					  LButtonDown
*-----------------------------------------------------------------------------*/
void cHaQuest::LButtonDown(int x, int y)
{
	if (sHaQuest100LV.State && sHaQuest100LV.State == 13)
	{
		if (ItemButtonFlag[0])
		{
			if (chaQuest.iFuryQuestIndex[1] > 1)
				chaQuest.iFuryQuestIndex[1]--;
		}
		if (ItemButtonFlag[1])
		{
			if (chaQuest.iFuryQuestIndex[1] < 10)
				chaQuest.iFuryQuestIndex[1]++;
		}
		if (bFuryQuestFlag == true)
			showFuryQuestItem();
	}
}
/*----------------------------------------------------------------------------*
*					  LButtonUp
*-----------------------------------------------------------------------------*/
void cHaQuest::LButtonUp(int x, int y)
{

}
char* haQuestFuryOfPhantom[12] =
{
	"image\\Sinimage\\Quest\\100LVQuest_1Start.sin",
	"image\\Sinimage\\Quest\\100LVQuest_2Start.sin",
	"image\\Sinimage\\Quest\\100LVQuest_2pass.sin",
	"image\\Sinimage\\Quest\\100LVQuest_3Start.sin",
	"image\\Sinimage\\Quest\\100LVQuest_3Pass.sin",
	"image\\Sinimage\\Quest\\100LVQuest_4Start.sin",
	"image\\Sinimage\\Quest\\100LVQuest_4Pass.sin",
	"image\\Sinimage\\Quest\\100LVQuest_5Start.sin",
	"image\\Sinimage\\Quest\\100LVQuest_5Pass.sin",
	"image\\Sinimage\\Quest\\100LVQuest_6Start.sin",
	"image\\Sinimage\\Quest\\100LVQuest_6Pass.sin",
	"image\\Sinimage\\Quest\\100LVQuest_7End.sin",
};
char* haQuestFuryOfPhantomItem[10] =
{
	"image\\Sinimage\\Quest\\haQuestFuryItem1.sin",
	"image\\Sinimage\\Quest\\haQuestFuryItem2.sin",
	"image\\Sinimage\\Quest\\haQuestFuryItem3.sin",
	"image\\Sinimage\\Quest\\haQuestFuryItem4.sin",
	"image\\Sinimage\\Quest\\haQuestFuryItem5.sin",
	"image\\Sinimage\\Quest\\haQuestFuryItem6.sin",
	"image\\Sinimage\\Quest\\haQuestFuryItem7.sin",
	"image\\Sinimage\\Quest\\haQuestFuryItem8.sin",
	"image\\Sinimage\\Quest\\haQuestFuryItem9.sin",
	"image\\Sinimage\\Quest\\haQuestFuryItem10.sin",
};
char* haQuestFuryOfPhantomVictory = "image\\Sinimage\\Quest\\100LVQuest_Victory.sin";

int  cHaQuest::showFuryQuest()
{
	if (CheckNowQuestState(0) == FALSE)
		return TRUE;

	if (haQuestCheck(QUESTBIT_FURYOFPHANTOM) == FALSE)
		return TRUE;

	if (sinChar->iLevel >= 100 && sinChar->iRank >= 4 && (QUESTBIT_FURYOFPHANTOM & haElementaryQuestLog) == 0)
	{
		bFuryQuestFlag = true;

		switch (sHaQuest100LV.State)
		{
		case 0:
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[0]);
			return TRUE;
		case 1:
			sHaQuest100LV.Kind = MONSTER_FERRUMHEART;
			lstrcpy(szQuestMonsterName, "Heart of Perum's Monster");
			sHaQuest100LV.Monster[0] = 0;
			sHaQuest100LV.Monster[1] = 50;
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[1]);
			haSetQuestTimer();
			SaveGameData();
			return TRUE;
		case 2:
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[2]);
			SaveGameData();
			return TRUE;
		case 3:
			cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[3]);
			return TRUE;
		case 4:
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[4]);
			return TRUE;
		case 5:
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[5]);
			return TRUE;
		case 6:
			sHaQuest100LV.Kind = MONSTER_ICE;
			lstrcpy(szQuestMonsterName, "Gallubia Valley's Monster");
			sHaQuest100LV.Monster[0] = 0;
			sHaQuest100LV.Monster[1] = 100;
			sHaQuest100LV.State = 7;
			haSetQuestTimer();
			SetQuestBoard();
			SaveGameData();
			return TRUE;
		case 7:
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[6]);
			return TRUE;
		case 8:
			cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[7]);
			SaveGameData();
			return TRUE;
		case 9:
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[8]);
			return TRUE;
		case 10:
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[9]);
			return TRUE;
		case 11:
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[10]);
			SaveGameData();
			return TRUE;
		case 12:
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[11]);
			return TRUE;
		}
	}
	return FALSE;
}
int  cHaQuest::showFuryQuestItem(int Kind)
{
	if (Kind)
		cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantom[11]);
	else
	{
		chaQuest.bFuryQuestFlag = true;
		if (iFuryQuestIndex[1])
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantomItem[iFuryQuestIndex[1] - 1]);
		else
			return FALSE;
	}
	return TRUE;
}
int  cHaQuest::RecvBattleNpcResult(int flag)
{
	if (sHaQuest100LV.State == 4 || sHaQuest100LV.State == 9 || sHaQuest100LV.State == 11)
	{
		if (flag)
		{
			FuryBattleFlag = true;
			cSinHelp.sinShowHelp(HAQUEST_CODE_FURYOFPHANTOM, QuestMessageBoxPosi2.x, QuestMessageBoxPosi2.y, QuestMessageBoxSize2.x, QuestMessageBoxSize2.y, D3DCOLOR_RGBA(0, 15, 128, 125), haQuestFuryOfPhantomVictory);
		}
		else
			cMessageBox.ShowMessage(MESSAGE_100LVBATTLELOSE);

		return true;
	}
	return false;
}
int cHaQuest::CancelQuest()
{
	if (sHaQuestElementary[Quest_A].CODE)
	{
		if (cInvenTory.SearchItemCode(sinQT1 | sin14))
			DeleteQuestItem(sinQT1 | sin14);
		ZeroMemory(&sHaQuestElementary[Quest_A], sizeof(sQUEST_ELEMENTARY));
	}
	if (sHaQuestElementary[Quest_B].CODE)
	{
		if (cInvenTory.SearchItemCode(sinQT1 | sin16))
			DeleteQuestItem(sinQT1 | sin16);
		ZeroMemory(&sHaQuestElementary[Quest_B], sizeof(sQUEST_ELEMENTARY));
		cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
	}
	if (sHaQuestElementary[Quest_C].CODE)
	{
		if (cInvenTory.SearchItemCode(sinQT1 | sin15))
			DeleteQuestItem(sinQT1 | sin15);
		ZeroMemory(&sHaQuestElementary[Quest_C], sizeof(sQUEST_ELEMENTARY));
		cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
	}
	if (sHaQuestElementary[Quest_D].CODE)
	{
		ZeroMemory(&sHaQuestElementary[Quest_D], sizeof(sQUEST_ELEMENTARY));
		cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
	}
	if (sHaQuestElementary[Quest_E].CODE)
	{
		ZeroMemory(&sHaQuestElementary[Quest_E], sizeof(sQUEST_ELEMENTARY));
		cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
	}
	if (sHaQuestElementary[Quest_F].CODE)
	{
		ZeroMemory(&sHaQuestElementary[Quest_F], sizeof(sQUEST_ELEMENTARY));
		cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
	}
	if (sHaQuestElementary[Quest_G].CODE)
	{
		ZeroMemory(&sHaQuestElementary[Quest_G], sizeof(sQUEST_ELEMENTARY));
		cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
	}
	if (sHaQuestElementary[Quest_H].CODE)
	{
		ZeroMemory(&sHaQuestElementary[Quest_H], sizeof(sQUEST_ELEMENTARY));
		cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
	}
	if (sHaQuestElementary[Quest_I].CODE)
	{
		ZeroMemory(&sHaQuestElementary[Quest_I], sizeof(sQUEST_ELEMENTARY));
		cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
	}
	if (sHaQuestElementary[Quest_J].CODE)
	{
		ZeroMemory(&sHaQuestElementary[Quest_J], sizeof(sQUEST_ELEMENTARY));
		cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
	}
	if (sHaQuestElementary[Quest_K].CODE)
	{
		if (cInvenTory.SearchItemCode(sinQT1 | sin18))
			DeleteQuestItem(sinQT1 | sin18);
		ZeroMemory(&sHaQuestElementary[Quest_K], sizeof(sQUEST_ELEMENTARY));
	}
	if (sHaQuestElementary[Quest_L].CODE)
	{
		if (cInvenTory.SearchItemCode(sinQT1 | sin19))
			DeleteQuestItem(sinQT1 | sin19);
		ZeroMemory(&sHaQuestElementary[Quest_L], sizeof(sQUEST_ELEMENTARY));
	}
	if (sHaQuest100LV.CODE)
	{
		ZeroMemory(&sHaQuest100LV, sizeof(sQUEST_ELEMENTARY));
		cSkill.CancelContinueSkill(CHANGE_ELEMENTARY_QUEST);
	}
	return TRUE;
}
