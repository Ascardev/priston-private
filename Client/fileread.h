#ifndef	_FILEREAD_HEADER

#define	_FILEREAD_HEADER

//화면 및 캐릭터 및 파일등 기본 설정
extern smCONFIG	smConfig;

//정보 파일을 해독하여 돌려준다 (Info에저장)
smCONFIG *smConfigDecode( char *iniFile );


//모델 정보 파일을 해독하여 돌려준다 (Info에저장)
int smModelDecode( char *iniFile , smMODELINFO *Info );


//몬스터 출현 구조체
struct rsSTG_MONSTER {
	char	szMonsterName[32];			//몬스터 이름
	int		OpenPercentage;				//출현빈도

	CharacterData	*lpCharInfo;			//몬스터 정보 포인터
	int		NumOpenStart;				//출현빈도 시작 값
};

#define rsSTG_MONSTER_MAX	50
#define rsBOSS_MONSTER_MAX	16

struct sBOSS_MONSTER {
	CharacterData		*MasterMonster;			//보스급 몬스터
	CharacterData		*SlaveMonster;			//수행 몬스터
	int				SlaveCount;				//수행 몬스터 숫자
	BYTE			bOpenTime[32];			//나타나는 시간
	int				OpenTimeCount;			//시간 수
};

struct	rsSTG_MONSTER_LIST {

	rsSTG_MONSTER	rsMonster[rsSTG_MONSTER_MAX];

	int		PecetageCount;
	int		Counter;
	int		LimitMax;						//출현 제한수 / 최대치
	int		OpenInterval;					//출현 주기
	int		OpenLimit;						//직역당 최대 출현수
	DWORD	dwIntervalTime;					//출현 간격 제한시간

	sBOSS_MONSTER	sBossMonsters[rsBOSS_MONSTER_MAX];		//두목급 몬스터 세트
	int	BossMonsterCount;									//두목급 몬스터 설정 갯수

};


#define SPECIAL_JOB_RANDOM_MAX			12

struct JOBNAME_BIT {
	char *szName;
	DWORD dwBitMask;
};

extern JOBNAME_BIT BitMaskJobNames[];


//몬스터 출현 정보 파일에서 해독하여 설정한다
int DecodeOpenMonster( char *szCharFile , rsSTG_MONSTER_LIST *lpStgMonList , CharacterData *lpCharInfoList, int ListCnt );

int GetRandomPos( int Min , int Max );


// 劤돨냔뵀溝固

#define		JOB_CODE_MECHANICIAN		0x00000001
#define		JOB_CODE_FIGHTER			0x00000002
#define		JOB_CODE_PIKEMAN			0x00000003
#define		JOB_CODE_ARCHER				0x00000004
#define		JOB_CODE_ASSASSIN			0x00000009

#define		JOB_CODE_MECHANICMASTER		0x00000010
#define		JOB_CODE_WARRIOR			0x00000020
#define		JOB_CODE_COMBATANT			0x00000030
#define		JOB_CODE_HUNTERMASTER		0x00000040
#define		JOB_CODE_ROGUE				0x00000090

#define		JOB_CODE_METALLEADER		0x00000100
#define		JOB_CODE_CHAMPION			0x00000200
#define		JOB_CODE_LANCER				0x00000300
#define		JOB_CODE_DIONS_DISCIPLE		0x00000400
#define		JOB_CODE_SHADOW				0x00000900

#define		JOB_CODE_HEAVYMETAL			0x00001000
#define		JOB_CODE_IMMORTALWARRIOR	0x00002000
#define		JOB_CODE_LANCELOT			0x00003000
#define		JOB_CODE_SAGITTARION		0x00004000
#define		JOB_CODE_SHADOWWALKER		0x00009000

#define		JOB_CODE_METALRAGE			0x00010000
#define		JOB_CODE_WARLORD			0x00020000
#define		JOB_CODE_BAYIOLUNT			0x00030000
#define		JOB_CODE_ISKAR				0x00040000
#define		JOB_CODE_SHADOWMASTER		0x00090000

#define		JOB_CODE_KNIGHT				0x00000005
#define		JOB_CODE_ATALANTA			0x00000006
#define		JOB_CODE_PRIEST				0x00000007
#define		JOB_CODE_MAGICIAN			0x00000008
#define		JOB_CODE_SHAMAN				0x0000000A

#define		JOB_CODE_PALADIN			0x00000050
#define		JOB_CODE_VALKYRIE			0x00000060
#define		JOB_CODE_SAINTESS			0x00000070
#define		JOB_CODE_WIZARD				0x00000080
#define		JOB_CODE_SUMMONER			0x000000A0

#define		JOB_CODE_HOLYKNIGHT			0x00000500
#define		JOB_CODE_BRUNHILD			0x00000600
#define		JOB_CODE_BISHOP				0x00000700
#define		JOB_CODE_ROYALKNIGHT		0x00000800
#define		JOB_CODE_HIGHSUMMONER		0x00000A00

#define		JOB_CODE_SAINTKNIGHT		0x00005000
#define		JOB_CODE_VALHALLA			0x00006000
#define		JOB_CODE_CELESTIAL			0x00007000
#define		JOB_CODE_ARCHMAGE			0x00008000
#define		JOB_CODE_SOULCATCHER		0x0000A000

#define		JOB_CODE_VALIANT			0x00050000
#define		JOB_CODE_QUEEN				0x00060000
#define		JOB_CODE_ANGEL				0x00070000
#define		JOB_CODE_ELEMENTAL			0x00080000
#define		JOB_CODE_SOULMASTER			0x000A0000

#define		BROOD_CODE_TEMPSKRON			1
#define		BROOD_CODE_MORAYION				2
#define		BROOD_CODE_SOPPHETIO			4
#define		BROOD_CODE_MAN					1
#define		BROOD_CODE_WOMAN				2


struct	SKILL_DATA_CODE {
	char	*szSkillName;				//스킬 이름
	int		dwPlaySkillCode;			//스킬 코드
};

extern	SKILL_DATA_CODE	SkillDataCode[];

extern int NotItemSpecial; // 석지용 - 믹스쳐 리셋

#endif
