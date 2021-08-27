#pragma once

#define MAP_MAX					64
#define NUM_MAPS				61
#define MAX_BORDERMAP			12
#define MAX_AMBIENTMAP			80
#define MAX_OBJECTMAP			50
#define MAX_SPAWNMAP			8		
#define MAX_SPAWNFLAGS			200
#define MAX_NPCINMAP			100
#define MAX_MONSTERINMAP		50
#define MAX_BOSSINMAP			16
#define MAX_BOSSHOURS			32
#define MAX_LOOT				1024
#define MAX_ALIVEMONSTERS		1024
#define MAPLEVEL				GetMapLevel

enum EMapID : int
{
	MAPID_Invalid				= -1,
	MAPID_AcasiaForest			= 0,
	MAPID_BambooForest			= 1,
	MAPID_GardenOfFreedom		= 2,
	MAPID_RicartenTown			= 3,
	MAPID_RefugeOfTheAncients	= 4,
	MAPID_CastleOfTheLost		= 5,
	MAPID_RuinenVillage			= 6,
	MAPID_CursedLand			= 7,
	MAPID_ForgottenLand			= 8,
	MAPID_NaviskoTown			= 9,
	MAPID_Oasis					= 10,
	MAPID_AncientsBattlefield	= 11,
	MAPID_ForbiddenLand			= 12,
	MAPID_AncientPrisonF1		= 13,
	MAPID_AncientPrisonF2		= 14,
	MAPID_AncientPrisonF3		= 15,
	MAPID_ChessRoom				= 16,
	MAPID_ForestOfSpirits		= 17,
	MAPID_LandOfDusk			= 18,
	MAPID_ValleyOfTranquility	= 19,
	MAPID_RoadToTheWind			= 20,
	MAPID_PhillaiTown			= 21,
	MAPID_CursedTempleF1		= 22,
	MAPID_CursedTempleF2		= 23,
	MAPID_MushroomCave			= 24,
	MAPID_BeehiveCave			= 25,
	MAPID_DarkSanctuary			= 26,
	MAPID_RailwayOfChaos		= 27,
	MAPID_HeartOfPerum			= 28,
	MAPID_Eura					= 29,
	MAPID_Bellatra				= 30,
	MAPID_GallubiaValley		= 31,
	MAPID_QuestArena			= 32,
	MAPID_BlessCastle			= 33,
	MAPID_GreedyLake			= 34,
	MAPID_FrozenSanctuary		= 35,
	MAPID_KelvezuLair			= 36,
	MAPID_LandOfChaos			= 37,
	MAPID_LostTemple			= 38,
	MAPID_GhostCastle			= 39,
	MAPID_EndlessTowerF1		= 40,
	MAPID_EndlessTowerF2		= 41,
	MAPID_CursedTempleF3		= 42,
	MAPID_EndlessTowerF3		= 43,
	MAPID_IceMineF1				= 44,
	MAPID_Atlantis				= 45,
	MAPID_MysteryForest1		= 46,
	MAPID_MysteryForest2		= 47,
	MAPID_MysteryForest3		= 48,
	MAPID_BattleTown			= 49,
	MAPID_MysteryDesert3		= 50,
	MAPID_MysteryDesert2		= 51,
	MAPID_MysteryDesert1		= 52,
	MAPID_ForgottenTempleF1		= 53,
	MAPID_ForgottenTempleF2		= 54,
	MAPID_AncientDungeonF1		= 55,
	MAPID_AncientDungeonF2		= 56,
	MAPID_AncientDungeonF3		= 57,
	MAPID_AncientWeapon			= 58,
	MAPID_AbyssSea				= 59,
	MAPID_T5QuestArena			= 60,
	MAPID_SecretLaboratory		= 61,
};

static const char * pszaMapsName[]
{
	"Acasia Forest",						//0   
	"Bamboo Forest",						//1   
	"Garden of Freedom",					//2   
	"Ricarten Town",						//3   
	"Refuge of the Ancients",				//4   
	"Castle of the Lost",					//5   
	"Ruinen Village",						//6   
	"Cursed Land",							//7   
	"Forgotten Land",						//8   
	"Navisko Town",							//9   
	"Oasis",								//10   
	"Battlefield of the Ancients",			//11   
	"Forbidden Land",						//12   
	"Ancient Prison 1F",					//13   
	"Ancient Prison 2F",					//14   
	"Ancient Prison 3F",					//15   
	"Checker (GM) Room",					//16   
	"Forest of Spirits",					//17   
	"Land of Dusk",							//18   
	"Valley of Tranquility",				//19   
	"Road to the Wind",						//20   
	"Pillia Town",							//21   
	"Cursed Temple 1F",						//22   
	"Cursed Temple 2F",						//23   
	"Cave of Mushrooms",					//24   
	"Cave of Beehive",						//25   
	"Sanctuary of Darkness",				//26   
	"Railway of Chaos",						//27   
	"Heart of Perum",						//28   
	"Eura",									//29   
	"Bellatra Celestial",					//30   
	"Gallubia Valley",						//31   
	"Tier 4 Arena",							//32   
	"Bless Castle",							//33   
	"Greedy Lake",							//34   
	"Frozen Temple",						//35   
	"Fire Map",								//36   
	"Lost Island",							//37   
	"Lost Temple",							//38   
	"GM Test Map",							//39  
	"Endless Tower 1F",						//40
	"Endless Tower 2F",						//41
	"Cursed Temple 3F",						//42
	"Endless Tower 3F",						//43
	"Ice Mine 1F",							//44
	"Atlantis Town",						//45
	"Mystery Forest 1",						//46
	"Mystery Forest 2",						//47
	"Mystery Forest 3",						//48
	"Battle Town",							//49
	"Mystery Desert 3",						//50
	"Mystery Desert 2",						//51
	"Mystery Desert 1",						//52
	"Forgotten Temple 1",					//53
	"Forgotten Temple 2",					//54
	"Ancient Dungeon 1",					//55
	"Ancient Dungeon 2",					//56
	"Ancient Dungeon 3",					//57
	"Anciient Weapon",						//58
	"Abyss of the Sea",						//59
	"T5 Quest Arena",						//60
	"Secret Laboratory",					//61
};

static const int iaMapsLevel[61 + 1]
{
	1,										//0
	1,										//1
	1,										//2
	1,										//3
	1,										//4
	1,										//5
	1,                                      //6
	1,                                      //7
	1,                                      //8
	1,                                      //9
	1,                                      //10
	55,                                     //11
	55,                                     //12
	40,                                     //13
	50,                                     //14
	60,                                     //15
	1,                                      //16
	1,                                      //17
	1,                                      //18
	1,                                      //19
	1,                                      //20
	1,                                      //21
	70,                                     //22
	75,                                     //23
	55,                                     //24
	55,                                     //25
	65,                                     //26
	80,                                     //27
	85,                                     //28
	90,                                     //29
	1,                                      //30
	90,                                     //31
	1,                                      //32
	80,                                     //33
	70,										//34
	95,                                     //35
	100,									//36
	100,									//37
	140,									//38
	1,                                      //39
	140,									//40
	140,									//41
	120,									//42
	180,									//43
	120,									//44 (128 old)
	1,                                      //45
	1,                                      //46
	1,                                      //47
	1,                                      //48
	105,									//49
	105,									//50
	100,									//51
	90,                                     //52
	110,									//53
	115,									//54
	120,									//55
	125,									//56
	140,									//57
	140,									//58
	125,									//59
	100,									//60
	128,									//61
};

enum EMapType : UINT
{
	MAPTYPE_None		= 0x000,
	MAPTYPE_Town		= 0x100,
	MAPTYPE_Forest		= 0x200,
	MAPTYPE_Desert		= 0x300,
	MAPTYPE_Wasteland	= 0x400,
	MAPTYPE_Dungeon		= 0x500,
	MAPTYPE_Iron		= 0x600,
	MAPTYPE_Unused_1	= 0x700,
	MAPTYPE_ChessRoom	= 0x800,
	MAPTYPE_Ice			= 0x900,
	MAPTYPE_BlessCastle = 0xA00,
	MAPTYPE_Distorted	= 0xB00,
	MAPTYPE_BattleTown	= 0xC00
};

enum EMapSky : int
{
	MAPSKY_None					= -1,
	MAPSKY_Rain					= 0,
	MAPSKY_Forest_Morning		= 1,
	MAPSKY_Forest_Noon			= 2,
	MAPSKY_Forest_Night			= 3,
	MAPSKY_Desert_Morning		= 4,
	MAPSKY_Desert_Noon			= 5,
	MAPSKY_Desert_Night			= 6,
	MAPSKY_Wasteland_Morning1	= 7,
	MAPSKY_Wasteland_Morning2	= 8,
	MAPSKY_Wasteland_Noon		= 9,
	MAPSKY_Wasteland_Night		= 10,
	MAPSKY_ForFAll_Morning		= 11,
	MAPSKY_ForFAll_Noon			= 12,
	MAPSKY_ForFAll_Night		= 13,
	MAPSKY_Iron_Morning			= 14,
	MAPSKY_Iron_Noon			= 15,
	MAPSKY_Iron_Night			= 16,
	MAPSKY_Iron_Aurora			= 17,
	MAPSKY_Iron_BOSS			= 18,
	MAPSKY_ICE1_Morning			= 19,
	MAPSKY_ICE1_Noon			= 20,
	MAPSKY_ICE1_Night			= 21,
	MAPSKY_ICE2_Morning			= 22,
	MAPSKY_ICE2_Noon			= 23,
	MAPSKY_ICE2_Night			= 24,
	MAPSKY_Lost1_Morning		= 25,
	MAPSKY_Lost1_Noon			= 26,
	MAPSKY_Lost1_Night			= 27,
	MAPSKY_Lost2_Morning		= 28,
	MAPSKY_Lost2_Noon			= 29,
	MAPSKY_Lost2_Night			= 30,
	MAPSKY_Battle_Event			= 31,
	MAPSKY_Battle_Moon			= 32,
	MAPSKY_Battle_Sun			= 33,
	MAPSKY_Battle_None			= 34,
};

enum ETeleportType : unsigned int
{
	TELEPORTTPE_Direct		= 0,
	TELEPORTTYPE_Warp		= 1,
	TELEPORTTYPE_WarpGate	= 2,
};

class BaseMap;

struct MapBorder
{
	int							iX;
	int							iZ;
	int							iY;
	BaseMap						* pcMap;
};

struct Teleport
{
	int							iX;
	int							iZ;
	int							iY;
	int							iHeight;
	int							iSize;
	MapBorder					saOutFieldBorder[MAX_BORDERMAP];
	int							iOutFieldCount;
	int							iLevel;
	int							iEffect;
};

struct MapPosition
{
	int							iX;
	int							iY;
	int							iZ;
	int							iRound;
	int							iNum;
};

struct FlatMap
{
	Point3D						sPosition;
	int							iLeftX;
	int							iRightX;
};

class BaseMap
{
public:
	char						szStageFilePath[64];
	char						szMiniMapFilePath[64];
	char						szMiniMapNameFilePath[64];

	EMapType					iMapType;
	int							iaSky[3];
	EBackgroundMusicID			iBackgroundMusicID;

	BOOL						bNightSpawn;

	int							iBorderCount;
	MapBorder					saFieldBorder[MAX_BORDERMAP];

	int							iWarpGateCount;
	int							iWarpGateCurrent;
	Teleport					saWarpGate[MAX_BORDERMAP];
	Point3D						sWarpGatePosition;

	MapPosition					saAmbientPosition[MAX_AMBIENTMAP];
	int							iAmbientCount;

	int							iLevel;
	int							iSight;

	char						szaObjectName[MAX_OBJECTMAP][64];
	DWORD						dwaObjectBip[MAX_OBJECTMAP];
	int							iObjectCount;

	Point3D						sPositionCenter;

	EMapID						iMapID;
	BOOL						bPvp;

	Point3D						saSpawnPoint[MAX_SPAWNMAP];
	int							iSpawnCount;

	FlatMap						sActionCamera;

public:
	int							GetID() { return iMapID; }

	void						SetID(EMapID i) { iMapID = i; }
	void						SetFileName(char * pszName, char * pszTitle);
	void						SetType(EMapType i) { iMapType = i; }
	void						SetSky(int iMorning, int iEvening, int iNight) { iaSky[0] = iMorning; iaSky[1] = iEvening; iaSky[2] = iNight; }
	void						SetBackgroundMusicID(EBackgroundMusicID i) { iBackgroundMusicID = i; }
	void						SetLevelRequirement(int i) { iLevel = i; }
	void						SetNightSpawn(BOOL b) { bNightSpawn = b; }
	void						SetCenter(int iCX, int iCZ) { sPositionCenter.iX = iCX << 8; sPositionCenter.iZ = iCZ << 8; }
	void						AddSpawn(int iX, int iZ) { saSpawnPoint[iSpawnCount].iX = iX << 8; saSpawnPoint[iSpawnCount].iZ = iZ << 8; iSpawnCount++; }
	void						AddBorder(class BaseMap * pcMap, int iX, int iZ, int iY = 0);
	void						AddTeleport1(int iX, int iZ, int iY, int iSize, int iHeight, class BaseMap * pcMap, int iXMap, int iZMap, int iYMap, int iLevel = 1, int iWarpType = 0);
	void						AddTeleport2(int iX, int iZ, int iY, int iSize, int iHeight, class BaseMap * pcMap, int iXMap, int iZMap, int iYMap, int iXMap2, int iZMap2, int iYMap2, int iLevel = 1, int iWarpType = 0);
	void						AddSound(int iX, int iY, int iZ, int iRound, int iCode);
	void						AddStaticModel(char * pszName, int iAnimationBip = 0);
	void						AddModelEx(char * pszFormat, ...);
	void						SetCamera(int iX, int iY, int iZ, int iLeftX, int iRightX);

	Point3D						& GetCenter() { return sPositionCenter; }
	Point3D						GetNearPostion(int iX, int iZ);
	Teleport					* GetWarpGate(Point3D sPosition);
	BaseMap						* GetBorderMap(BaseMap * pcMap, Point3D sPosition);

	BOOL						IsStartPoint(int iX, int iZ);
	void						SetPVP(BOOL b) { bPvp = b; }

	void						PlayAmbient();
};

static int GetMapLevel(int i) { return iaMapsLevel[i]; };

struct CharacterData;

struct MapMonster
{
	char					szMonsterName[32];
	int						iSpawnRate;

	CharacterData			*psCharacter;
	int						iSpawnRateCum;
};

struct BossMonster
{
	CharacterData		*pcdBoss;
	CharacterData		*pcdMinion;
	int					iMinions;
	char				caBossHour[MAX_BOSSHOURS];
	int					iBossHours;
};
struct SpawnFlag
{
	int					bActive;
	int					iID;
	char				szName[32];
	int					iX;
	int					iZ;
};

struct SpawnSetting
{
	MapMonster	saMonster[MAX_MONSTERINMAP];

	int			iTotalMonsterSpawnRate;
	int			iTotalMonsters;
	int			iSpawnMaxMonsters;
	int			iSpawnIntervalMin;
	int			iSpawnMonsters;
	int			iSpawnIntervalMax;

	BossMonster	saBoss[MAX_BOSSINMAP];
	int			iTotalBosses;
};

struct PacketBossTimeUpdate : Packet
{
	char				szBossName[32];
	DWORD				dwTime;
	int					iMapID;

	PacketBossTimeUpdate() {};
	PacketBossTimeUpdate(int _iMapID) { iMapID = _iMapID; };

	~PacketBossTimeUpdate() {};
};

class Map
{
public:
	class smSTAGE3D		* pcStage = nullptr;
	BaseMap				* pcBaseMap = nullptr;
	char				szStartPointFile[64];
	char				szCharFixedFile[64];
	char				szCharMonsterFile[64];
	SpawnFlag			saSpawnFlag[MAX_SPAWNFLAGS];
	BOOL				baSpawnFlagActive[MAX_SPAWNFLAGS];
	int					iaSpawnMonsterActive[MAX_SPAWNFLAGS];
	int					iNumActiveSpawns;
	int					iLastActiveSpawn;
	DWORD				dwaTimeLastMonsterSpawned[MAX_SPAWNFLAGS];
	int					iNumSpawnFlag;
	int					iNumActiveSpawnFlag;
	MapLoot				saLoot[MAX_LOOT];
	PacketUnitInfo		saNPC[100];
	SpawnSetting		sSpawnSetting;
	int					uCounter;
	BOOL				bNight;
	Unit				* pcaUnitData[MAX_ALIVEMONSTERS];
	int					iNumAliveUnitData;
	int					iNumUsingUnit;
	BOOL				bForceCreateMonster;
	int					iState;
	Point3D				sMonsterPosition;

	Map();

	void Load(const char *pszFile);
	void Free();
};