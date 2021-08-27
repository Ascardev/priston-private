#pragma once

//Size of Box of Minimap(in pixels)
#define MINIMAP_SIZE			128

//Size of Image of Minimap (0~100%)
#define MINIMAP_TEXTURE_SIZE	512
#define MINIMAP_TEXTURE_SCALE	84

#define DIST_MAP_CONNECT 0x120000
#define DISTANCE_UNIT_VIEWLIMIT			(64*64)

enum EMapID : int
{
	MAPID_Invalid = -1,
	MAPID_AcasiaForest = 0, //��֮��
	MAPID_BambooForest = 1, //��֮��
	MAPID_GardenOfFreedom = 2, // ����ͥԺ
	MAPID_RicartenTown = 3, // ����
	MAPID_RefugeOfTheAncients = 4, //����Ĺ��
	MAPID_CastleOfTheLost = 5, //����
	MAPID_RuinenVillage = 6, //�����ׯ
	MAPID_ForgottenLand = 7, //����֮��
	MAPID_CursedLand = 8, //����֮��
	MAPID_NaviskoTown = 9, // ��ά˹��
	MAPID_Oasis = 10, //����
	MAPID_AncientsBattlefield = 11, //�Ŵ�ս��
	MAPID_ForbiddenLand = 12, //��ӡ֮��
	MAPID_AncientPrisonF1 = 13, //�Ŵ�����1��
	MAPID_AncientPrisonF2 = 14, //�Ŵ�����2��
	MAPID_AncientPrisonF3 = 15, //�Ŵ�����3��
	MAPID_ChessRoom = 16, // GM����
	MAPID_ForestOfSpirits = 17, //�ƻ�����
	MAPID_LandOfDusk = 18, //����ɭ��
	MAPID_ValleyOfTranquility = 19, //��֮��
	MAPID_RoadToTheWind = 20, //��֮·
	MAPID_PhillaiTown = 21, // �ƶ���
	MAPID_CursedTempleF1 = 22, //��������1��
	MAPID_CursedTempleF2 = 23, //��������2��
	MAPID_MushroomCave = 24, //Ģ����Ѩ
	MAPID_BeehiveCave = 25, //�䷿��Ѩ
	MAPID_DarkSanctuary = 26, //�Ŵ�ʥ��
	MAPID_RailwayOfChaos = 27, //ĩ�ն���
	MAPID_HeartOfPerum = 28, //��������
	MAPID_Eura = 29, //������ׯ
	MAPID_Bellatra = 30, //��������
	MAPID_GallubiaValley = 31, //������ɽ��
	MAPID_QuestArena = 32, //�����ͼ
	MAPID_BlessCastle = 33, //ף���Ǳ�
	MAPID_GreedyLake = 34, //̰��֮��
	MAPID_FrozenSanctuary = 35, //�����
	MAPID_KelvezuLair = 36, //����ά�ն�Ѩ
	MAPID_LandOfChaos = 37, //��ʧ֮��
	MAPID_LostTemple = 38, //��ʧ����
	MAPID_GhostCastle = 39, //����Ǳ�
	MAPID_EndlessTowerF1 = 40, //�޾�֮��1��
	MAPID_EndlessTowerF2 = 41, //�޾�֮��2��
	MAPID_CursedTempleF3 = 42, //��������3��
	MAPID_EndlessTowerF3 = 43, //�޾�֮��3��
	MAPID_IceMineF1 = 44, // ���ⶴѨ1��
	MAPID_SecretLaboratory = 45, // ��ά˹�˶�Ѩ
	MAPID_AncientWeapon = 46, //��˶�Ѩ
	MAPID_ShipyardRuins = 47, //����Ĺ��
	MAPID_MysteryForest3 = 48, //Զ��֮ɭ3
	MAPID_MysteryForest2 = 49, //Զ��֮ɭ2
	MAPID_MysteryForest1 = 50, //Զ��֮ɭ1
	MAPID_Atlantis = 51, //����˹��
	MAPID_BattleTown = 52, //�Ŵ�����˹��
	MAPID_MysteryDesert3 = 53, //�þ�ɳĮ3
	MAPID_MysteryDesert2 = 54, //�þ�ɳĮ2
	MAPID_MysteryDesert1 = 55, //�þ�ɳĮ1
	MAPID_MiraRemains = 56, //�����ż�
	MAPID_T5QuestArena = 57, //���Ҷ�Ѩ
};
enum ETeleportType : unsigned int
{
	TELEPORTTPE_Direct = 0,
	TELEPORTTYPE_Warp = 1,
	TELEPORTTYPE_WarpGate = 2,
};
enum EMapType : unsigned int
{
	MAPTYPE_Town = 0x100,
	MAPTYPE_Forest = 0x200,
	MAPTYPE_Desert = 0x300,
	MAPTYPE_Wasteland = 0x400,
	MAPTYPE_Dungeon = 0x500,
	MAPTYPE_Iron = 0x600,
	MAPTYPE_Unused_1 = 0x700,
	MAPTYPE_ChessRoom = 0x800,
	MAPTYPE_Ice = 0x900,
	MAPTYPE_BlessCastle = 0xA00,
	MAPTYPE_Distorted = 0xB00,
	MAPTYPE_BattleTown = 0xC00
};

enum EMapSky
{
	MAPSKY_None,
	MAPSKY_Rain,
	MAPSKY_Forest_Morning,
	MAPSKY_Forest_Noon,
	MAPSKY_Forest_Night,
	MAPSKY_Desert_Morning,
	MAPSKY_Desert_Noon,
	MAPSKY_Desert_Night,
	MAPSKY_Wasteland_Morning1,
	MAPSKY_Wasteland_Morning2,
	MAPSKY_Wasteland_Noon,
	MAPSKY_Wasteland_Night,
	MAPSKY_ForFAll_Morning,
	MAPSKY_ForFAll_Noon,
	MAPSKY_ForFAll_Night,
	MAPSKY_Iron_Morning,
	MAPSKY_Iron_Noon,
	MAPSKY_Iron_Night,
	MAPSKY_Iron_Aurora,
	MAPSKY_Iron_BOSS,
	MAPSKY_ICE1_Morning,
	MAPSKY_ICE1_Noon,
	MAPSKY_ICE1_Night,
	MAPSKY_ICE2_Morning,
	MAPSKY_ICE2_Noon,
	MAPSKY_ICE2_Night,
	MAPSKY_Lost1_Morning,
	MAPSKY_Lost1_Noon,
	MAPSKY_Lost1_Night,
	MAPSKY_Lost2_Morning,
	MAPSKY_Lost2_Noon,
	MAPSKY_Lost2_Night,
	MAPSKY_Battle_Event,
	MAPSKY_Battle_Moon,
	MAPSKY_Battle_Sun,
	MAPSKY_Battle_None,
};

static const int iaMapsLevel[]
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

class smSTAGE3D;

namespace MAP
{
	typedef class BaseMap *LPBASEMAP;

	class BaseMap;

	struct MapBorder
	{
		int	iX = 0;
		int iZ = 0;
		int iY = 0;
		BaseMap	*pMap = NULL;
		MapBorder(BaseMap *pMap, int iX, int iZ, int iY = 0)
		{
			this->iX = iX << 8;
			this->iZ = iZ << 8;
			this->iY = iY << 8;
			this->pMap = pMap;
		}
	};

	typedef struct MapTeleport *LPMAPTELEPORT;

	struct MapTeleport
	{
		Point3D sPosition;
		int iHeight = 0;
		int iSize = 0;
		int iEffect = 0;
		BaseMap *pcMap = NULL;
		std::vector<MapTeleport> vTeleport;

		MapTeleport(BaseMap *pcMap, int iX, int iZ, int iY, int iSize, int iHeight)
		{
			this->pcMap = pcMap;
			this->sPosition = Point3D(iX << 8, iY << 8, iZ << 8);
			this->iHeight = iHeight;
			this->iSize = iSize;
		}
		MapTeleport(BaseMap *pcMap, int iX, int iZ, int iY, int iEffect)
		{
			this->pcMap = pcMap;
			this->sPosition = Point3D(iX << 8, iY << 8, iZ << 8);
			this->iEffect = iEffect;
		}
		void Add(BaseMap *pcMap, int iX, int iZ, int iY, int iEffect = 0);
		Point3D Load(BaseMap *pcMap, int iLevel, int iEffect);
	};
	struct MapSound
	{
		int iX = 0;
		int iY = 0;
		int iZ = 0;
		int	iRound = 0;
		int	iSound = 0;
		MapSound(int iX, int iY, int iZ, int iRound, int iSound)
		{
			this->iX = iX << 8;
			this->iY = iY << 8;
			this->iZ = iZ << 8;
			this->iRound = iRound;
			this->iSound = iSound;
		}
	};
	struct MapModel
	{
		std::string strObject = "";
		BOOL bBip = FALSE;
		MapModel(const char *pszStr, BOOL b = FALSE)
		{
			strObject = pszStr;
			bBip = b;
		}
	};
	typedef struct MapFlat *LPMAPFLAT;

	struct MapFlat
	{
		Point3D sPosition;
		int iLeftX;
		int iRightX;
		MapFlat() {}
		MapFlat(int iX, int iY, int iZ, int iLeftX, int iRightX)
		{
			this->sPosition = Point3D(iX, iY, iZ);
			this->iLeftX = iLeftX;
			this->iRightX = iRightX;
		}
	};

	static int GetMapLevel(int i) { return iaMapsLevel[i]; };

	class BaseMap
	{
	public:
		BaseMap();
		BaseMap(EMapID eID, const char *pszName) : m_eID(eID), m_strName(pszName), m_iLevel(GetMapLevel(eID)) {}
		virtual ~BaseMap();

		std::string GetName() { return m_strName; }

		void SetFileName(const char *pszName) { m_strFilePatch = pszName; };
		std::string GetFileName() { return m_strFilePatch; }
		void SetMinMapName(const char *pszName) { m_strMinMapFile = pszName; };
		std::string GetMinMapName() { return m_strMinMapFile; }
		void SetTitleMapName(const char *pszName) { m_strTitleFile = pszName; };
		std::string GetTitleMapName() { return m_strTitleFile; }

		void SetType(EMapType eMapType) { m_eMapType = eMapType; };
		EMapType GetType() { return m_eMapType; }

		EMapID GetID() { return m_eID; }
		int GetLevel() { return m_iLevel; };

		void SetSky(EMapSky eMorning, EMapSky eEvening, EMapSky eNight) { m_eSky[0] = eMorning; m_eSky[1] = eEvening; m_eSky[2] = eNight; }
		EMapSky GetSky(int i) { return m_eSky[i]; }

		void SetBackgroundMusicID(EBackgroundMusicID i) { m_eBackgroundMusicID = i; }
		EBackgroundMusicID GetBackgroundMusicID() { return m_eBackgroundMusicID; }

		void AddStaticModel(const char *pszFileName, BOOL bAnimation = FALSE) { m_vModel.push_back(MapModel(pszFileName, bAnimation)); }
		void AddModelEx(const char *pszFormat, ...);

		void SetCenter(int iX, int iZ) { m_sPositionCenter = Point2D(iX << 8, iZ << 8); }
		Point2D GetCenter() { return m_sPositionCenter; }

		void AddSpawn(int iX, int iZ) { m_vSpawn.push_back(Point2D(iX << 8, iZ << 8)); };

		void AddBorder(LPBASEMAP pMap, int iX, int iZ);
		LPBASEMAP GetBorder(int iX, int iZ);

		LPMAPTELEPORT AddTelePort(int iX, int iZ, int iY, int iSize, int iHeight);
		LPMAPTELEPORT GetTeleport(int iX, int iY, int iZ);
		LPMAPTELEPORT GetTeleport(int iLevel, int iEffect);

		void SetCamera(int iX, int iY, int iZ, int iLeftX, int iRightX) { m_sCamera = MapFlat(iX, iY, iZ, iLeftX, iRightX); }
		LPMAPFLAT GetCamera() { return &m_sCamera; }

		void AddSound(int iX, int iY, int iZ, int iRound, int iSound) { m_vSound.push_back(MapSound(iX, iY, iZ, iRound, iSound)); };
		void PlaySounds();

		BOOL CheckPosition(int iX, int iZ);

		Point2D GetPosition(int iX = 0, int iZ = 0);
		Point2D TranslateMap(int iX = 0, int iZ = 0);

		void LoadTerrain();
		smSTAGE3D *GetTerrain() { return m_pcTerrain; }

		void Update(Point3D sPosition);
		void SetTeleport(EMapID eID = MAPID_Invalid);

		void LoadMinMap();
		void Render2D(int iX, int iY, int iSize);
		void Render3D(Point3D sPosition, Point3D sAngle);
		void RenderTitle(int iX, int iY);

		BOOL IsMiniMap() { return (m_pcMinMap) ? TRUE : FALSE; }
	private:
		EMapID m_eID = MAPID_Invalid;
		int m_iLevel = 1;
		EMapType m_eMapType = MAPTYPE_Town;
		EMapSky m_eSky[3] = { MAPSKY_None,MAPSKY_None,MAPSKY_None };
		EBackgroundMusicID m_eBackgroundMusicID = BACKGROUNDMUSICID_TRIGGERED;
		std::string m_strName = "";
		std::string m_strFilePatch = "";
		std::string m_strMinMapFile = "";
		std::string m_strTitleFile = "";
		Point2D m_sPositionCenter;
		MapFlat	m_sCamera;
		std::vector<MapBorder> m_vBorder;
		std::vector<MapTeleport> m_vTeleport;
		std::vector<MapSound> m_vSound;
		std::vector<Point2D> m_vSpawn;
		std::vector<MapModel> m_vModel;
		smSTAGE3D *m_pcTerrain = NULL;
		DWORD m_dwDelayTime = NULL;
		LPBASEMAP m_pcMap = NULL;
		BOOL m_bHover = FALSE;
		UI::LPIMAGE m_pcMinMap = NULL;
		UI::LPIMAGE m_pcTitleMap = NULL;
	};
}