#include "StdAfx.h"

sQUEST_CHANGEJOB	sinQuest_ChangeJob;	//퀘스트의 전반적인 내용을 다룬다 (템스크론)
sQUEST_CHANGEJOB	sinQuest_ChangeJob2;//퀘스트의 전반적인 내용을 다룬다 (모라이온)
sQUEST_CHANGEJOB3   sinQuest_ChangeJob3;//템스크론 모라이온 3차 전직퀘스트 
sQUEST_CHANGEJOB3   sinQuest_ChangeJob4;//템스크론 모라이온 3차 전직퀘스트 


sQUEST_CHANGEJOB3   sinQuest_Level30;
sQUEST_CHANGEJOB3   sinQuest_Level55;
sQUEST_CHANGEJOB3   sinQuest_Level55_2;
sQUEST_CHANGEJOB3   sinQuest_Level70;
sQUEST_CHANGEJOB3   sinQuest_Level80;
sQUEST_CHANGEJOB3   sinQuest_Level85;
sQUEST_CHANGEJOB3   sinQuest_Level90;

sQUEST_CHANGEJOB3   sinQuest_Level80_2; //새로추가된 스텟 +7퀘스트
sQUEST_CHANGEJOB3   sinQuest_Level90_2; //새로추가된 스텟 +10퀘스트

DWORD sinQuest_levelLog = 0; //훨蛟MASK
WORD sinFruitStatus[2] = { 0 }; //벎茄橄昑

BYTE sinTempStatus[8] = { 0 }; //줄珂橄昑듐

ItemData TempQuestItem;

int Quest_Flag = 0;

int sinChangeJobButtonShow = 0; //템스크론 전업 2차전업
int sinChangeJobButtonShow2 = 0; //모라이온 전업 2차전업
int sinChangeJobButtonShow3 = 0; //템스크론 모라이온 3차전업
int sinChangeJobButtonShow4 = 0; //템스크론 모라이온 4차전업

int CheckQuestComplete = 0;		 //전업의 진행사항
int CheckQuestButtonShow1 = 0;
int CheckQuestButtonShow2 = 0;
int CheckQuestButtonShow3 = 0;

POINT QuestMessageBoxPosi2 = { 50,45 };
POINT QuestMessageBoxSize2 = { 9,10 };

//퀘스트 파일의 경로 
char *QuestFilePath[] = {
	"image\\Sinimage\\Quest\\ChangeJob1.sin",
		"image\\Sinimage\\Quest\\ChangeJob2.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_M1.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_M2.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_M3.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_D1.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_D2.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_D3.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_Success.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_M0.sin",
		"image\\Sinimage\\Quest\\ChangeJob2M_D0.sin",
		"image\\Sinimage\\Quest\\ChangeJob1.sin",
};

char *QuestFilePath3[] = {
	"image\\Sinimage\\Quest\\ChangeJob3_0.sin",
		"image\\Sinimage\\Quest\\ChangeJob3_1.sin",
		"image\\Sinimage\\Quest\\ChangeJob3_2.sin",
		"image\\Sinimage\\Quest\\ChangeJob3_3.sin",
		"image\\Sinimage\\Quest\\ChangeJob3_4.sin",
		"image\\Sinimage\\Quest\\ChangeJob3_5.sin",
};


char *WingQuestFilePath_a[] = {
	"image\\Sinimage\\Quest\\M_Wing_a.sin",
		"image\\Sinimage\\Quest\\S_Wing_a.sin",
		"image\\Sinimage\\Quest\\G_Wing_a.sin",
		"image\\Sinimage\\Quest\\D_Wing_a.sin",
		"image\\Sinimage\\Quest\\K_wing_a.sin", //케이아스윙
		"image\\Sinimage\\Quest\\E_wing_a.sin", //익스트림윙 로스트 아일랜드 (성근추가)
		"image\\Sinimage\\Quest\\Puzzle.sin",   //얘는 퍼즐 ~~~ 건들지 마세염 -0-

};

char *WingQuestFilePath_b[] = {
	"image\\Sinimage\\Quest\\M_Wing_b.sin",
		"image\\Sinimage\\Quest\\S_Wing_b.sin",
		"image\\Sinimage\\Quest\\G_Wing_b.sin",
		"image\\Sinimage\\Quest\\D_Wing_b.sin",
		"image\\Sinimage\\Quest\\K_wing_b.sin", //케이아스윙
		"image\\Sinimage\\Quest\\E_wing_b.sin", //익스트림윙 로스트 아일랜드 (성근추가)
		"image\\Sinimage\\Quest\\Wing_End.sin",

};

char *WarpGateDoc[] = {
	"image\\Sinimage\\WarpGateDoc\\Default.sin",
		"image\\Sinimage\\WarpGateDoc\\Ricarten.sin",
		"image\\Sinimage\\WarpGateDoc\\Pilai.sin",
		"image\\Sinimage\\WarpGateDoc\\Forest2.sin",
		"image\\Sinimage\\WarpGateDoc\\Forest3.sin",
		"image\\Sinimage\\WarpGateDoc\\Ruinen.sin",
		"image\\Sinimage\\WarpGateDoc\\Nevisco.sin",
		"image\\Sinimage\\WarpGateDoc\\Desert4.sin",
		"image\\Sinimage\\WarpGateDoc\\yura.sin",
		"image\\Sinimage\\WarpGateDoc\\chaoticpost.sin",	//로스트 아일랜드 (성근추가)

};
char *HaWarpGateDoc[] = {
	"image\\Sinimage\\WarpGateDoc\\B_Castle.sin"
};

char *WarningInitPoint[] = {
	"image\\Sinimage\\Help\\WarnigWeight.sin",

};
char *BabelEventDoc = "image\\Sinimage\\Quest\\BaBelEvent.sin";
char *NineTailFoxDoc = "image\\Sinimage\\Quest\\NineTailFoxEvent.sin";
char *StarDustDoc = "image\\Sinimage\\Quest\\StarDust.sin";		//크리스마스수정
char *CristalEventDoc = "image\\Sinimage\\Quest\\CristalEvent.sin";//일곱가지 크리스탈의 보은

//박재원 - 수박 모아오기
char *WatermelonDoc = "image\\Sinimage\\Quest\\WatermelonEvent.sin";//수박 모아오기 이벤트
//박재원 - 호박 모아오기
char *PumpkinDoc = "image\\Sinimage\\Quest\\PumpkinEvent.sin";//호박 모아오기 이벤트
//박재원 - 별조각 모아오기
char *StarDoc = "image\\Sinimage\\Quest\\StarEvent.sin";//박재원 - 밤하늘의 소원 이벤트
//장별 - 발렌타인 초콜릿 모아오기
char *ValentineDoc = "image\\Sinimage\\Quest\\ChocolateEvent.sin"; //발렌타인 초콜릿 모아오기 이벤트
// 박재원 - 알파벳 조합 이벤트
char *PristonAlphabetDoc = "image\\Sinimage\\Quest\\Priston.sin"; // 박재원 - 알파벳 조합 이벤트
// 장별 - 캔디데이즈
char *CandydaysDoc = "image\\Sinimage\\Quest\\CandydaysEvent.sin"; // 캔디 모아오기 이벤트
// 장별 - 매지컬그린
char *MagicalGreenDoc = "image\\Sinimage\\Quest\\MagicalGreenEvent.sin";
// 장별 - 카라의 눈물
char *TearOfKaraDoc = "image\\Sinimage\\Quest\\KarasTears.sin";

// 장별 - 조사원을 찾아라
char *Findinvestigator1_1Doc = "image\\Sinimage\\Quest\\Resercher_Start.sin";
char *Findinvestigator1_2Doc = "image\\Sinimage\\Quest\\Resercher_Pass1.sin";
char *Findinvestigator1_3Doc = "image\\Sinimage\\Quest\\Resercher_Pass2.sin";
char *Findinvestigator2_1Doc = "image\\Sinimage\\Quest\\Kamiyu_Start.sin";
char *Findinvestigator2_2Doc = "image\\Sinimage\\Quest\\Kamiyu_Pass.sin";
char *Findinvestigator3_1Doc = "image\\Sinimage\\Quest\\Eto_Start.sin";
char *Findinvestigator3_2Doc = "image\\Sinimage\\Quest\\Eto_Pass.sin";

char *LevelQuest30Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest30start.sin",
		"image\\Sinimage\\Quest\\LevelQuest30Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest30end.sin",

};
char *LevelQuest55Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest55start.sin",
		"image\\Sinimage\\Quest\\LevelQuest55Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest55end.sin",

};

char *LevelQuest55_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest55-2start.sin",
		"image\\Sinimage\\Quest\\LevelQuest55-2Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest55-2end.sin",

};

char *LevelQuest70Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest70start.sin",
		"image\\Sinimage\\Quest\\LevelQuest70Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest70end.sin",

};
char *LevelQuest80Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest80start.sin",
		"image\\Sinimage\\Quest\\LevelQuest80Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest80end.sin",

};
char *LevelQuest85Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest85start.sin",
		"image\\Sinimage\\Quest\\LevelQuest85Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest85Path2.sin",
		"image\\Sinimage\\Quest\\LevelQuest85end.sin",

};
char *LevelQuest90Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest90start.sin",
		"image\\Sinimage\\Quest\\LevelQuest90Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest90end.sin",

};

char *LevelQuest80_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest80_2start.sin",
		"image\\Sinimage\\Quest\\LevelQuest80_2start2.sin",
		"image\\Sinimage\\Quest\\LevelQuest80_2Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest80_2Path2.sin",
		"image\\Sinimage\\Quest\\LevelQuest80_2end.sin",

};

char *LevelQuest90_2Doc[] = {
	"image\\Sinimage\\Quest\\LevelQuest90_2start.sin",
		"image\\Sinimage\\Quest\\LevelQuest90_2start2.sin",
		"image\\Sinimage\\Quest\\LevelQuest90_2Path.sin",
		"image\\Sinimage\\Quest\\LevelQuest90_2Path2.sin",
		"image\\Sinimage\\Quest\\LevelQuest90_2end.sin",

};

char *QuestFilePath4[] = {
	"image\\Sinimage\\Quest\\ChangeJob4_1Start.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_1Path.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_2Start.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_2Path.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_3Start.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_3Path.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_4Start.sin",
		"image\\Sinimage\\Quest\\ChangeJob4_4End.sin",

};

int  QuestMonsterCount[] = { 30,40,50,25,35,45,50,70,100 };

int SetChangeJob3QuestItem(Item *pItem, int Down)
{
	int Temp = 0;
	float fTemp = 0;
	if (pItem->sAgeLevel > 3)
		return FALSE;

	switch (pItem->sItemID.ToItemType())
	{
	case sinWA1:
	case sinWC1:
	case sinWP1:
	case sinWS2:
	case sinWD1:
		if (Down)
		{

		}
		else
		{
			if (pItem->sAgeLevel)
			{
				pItem->fAddHP += 4;
				Temp = GetRandomPos(1, 2);
				pItem->sDamage.sMin += Temp;
				pItem->sDamage.sMax += Temp;
				Temp = GetRandomPos(10, 15);
				pItem->iAttackRating += Temp;
				pItem->eMixEffect = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX | SIN_ADD_ATTACK_RATE | SIN_ADD_LIFE;
			}
			pItem->bMaturing = pItem->sAgeLevel;
			pItem->sMatureBar.sMax = QuestMonsterCount[pItem->bMaturing];
			pItem->sAgeLevel++;

		}
		break;
	case sinWS1:
	case sinWT1:
		if (Down)
		{

		}
		else
		{
			if (pItem->sAgeLevel)
			{
				pItem->fAddHP += 4;
				Temp = GetRandomPos(1, 2);
				pItem->sDamage.sMin += Temp;
				pItem->sDamage.sMax += Temp;
				Temp = GetRandomPos(10, 15);
				pItem->iAttackRating += Temp;
				pItem->eMixEffect = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX | SIN_ADD_ATTACK_RATE | SIN_ADD_LIFE;
			}

			pItem->bMaturing = 3 + pItem->sAgeLevel;
			pItem->sMatureBar.sMax = QuestMonsterCount[pItem->bMaturing];
			pItem->sAgeLevel++;

		}
		break;
	case sinWM1:
	case sinWN1:
		if (Down)
		{

		}
		else
		{
			if (pItem->sAgeLevel)
			{
				pItem->fAddHP += 4;
				Temp = GetRandomPos(1, 2);
				pItem->sDamage.sMin += Temp;
				pItem->sDamage.sMax += Temp;
				Temp = GetRandomPos(3, 6);
				fTemp = (float)Temp / 10.0f;
				pItem->fMPRegen += fTemp;
				pItem->eMixEffect = SIN_ADD_DAMAGE_MIN | SIN_ADD_DAMAGE_MAX | SIN_ADD_MANAREGEN | SIN_ADD_LIFE;

			}
			pItem->bMaturing = 6 + pItem->sAgeLevel;
			pItem->sMatureBar.sMax = QuestMonsterCount[pItem->bMaturing];
			pItem->sAgeLevel++;

		}
		break;
	}
	pItem->sMatureBar.sMin = pItem->sMatureBar.sMax;
	ReformItem(pItem);
	return TRUE;
}

int CheckQuestItemDownFlag = 0;


void *pQuestCode[] =
{
	&sinQuest_ChangeJob,
	&sinQuest_ChangeJob2,
	&sinQuest_ChangeJob3,
	&sinQuest_Level30,
	&sinQuest_Level55,
	&sinQuest_Level55_2,
	&sinQuest_Level70,
	&sinQuest_Level80,
	&sinQuest_Level85,
	&sinQuest_Level90,
	&sinQuest_Level80_2,
	&sinQuest_Level90_2,
	&sinQuest_ChangeJob4,
	0,
};

struct QuestCodeFlag
{
	DWORD	CODE;
};

int sinChangeJob4MonCode[][2] =
{
	{MONSTER_MURPIN,MONSTER_SKELETON_KNIGHT },
	{MONSTER_HEAD_CUTTER,MONSTER_SOLID_SNAIL},
	{MONSTER_THORN_CROWLER,MONSTER_MUMMY},
	{MONSTER_DOOM_GUARD ,MONSTER_FIGON},
	{MONSTER_STONE_GIANT,MONSTER_STONE_COLEM},
	{MONSTER_IRON_GUARD,MONSTER_AVELLRIN},
};
int sinChangeJob4MonCode2[][2] =
{
	{MONSTER_AVELRISK_L,MONSTER_BEEBUL},
	{MONSTER_ILLUSION_KNIGHT,MONSTER_NIGHT_MARE },
	{MONSTER_WITCH,MONSTER_HEAVY_GOBLIN},
	{MONSTER_DAWLIN ,MONSTER_STYGIAN},
	{MONSTER_INCUBUS,MONSTER_CHAIN_GOLEM},
	{MONSTER_DARK_SPECTOR,MONSTER_METRON},
};
int sinChangeJob4MonCode3[] =
{
	MONSTER_SOLID_SNAIL,
	MONSTER_ILLUSION_KNIGHT,
	MONSTER_AVELRISK_LOAD,
	MONSTER_DUSK,
	MONSTER_CHAIN_GOLEM ,
	MONSTER_SADNESS
};

int QuestLevelTable[7] = { 60,65,70,75,80,85,200 };
char szQuestMonsterName[64];