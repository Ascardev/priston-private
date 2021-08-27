#pragma once

enum ESceneType : unsigned int
{
	SCENETYPE_Town = 0x100,
	SCENETYPE_Forest = 0x200,
	SCENETYPE_Desert = 0x300,
	SCENETYPE_Wasteland = 0x400,
	SCENETYPE_Dungeon = 0x500,
	SCENETYPE_Iron = 0x600,
	SCENETYPE_Unused_1 = 0x700,
	SCENETYPE_ChessRoom = 0x800,
	SCENETYPE_Ice = 0x900,
	SCENETYPE_BlessCastle = 0xA00,
	SCENETYPE_Distorted = 0xB00,
	SCENETYPE_BattleTown = 0xC00
};

namespace SCENE
{
	class MapInfo : public Element
	{
		struct Position
		{
			int iX;
			int iY;
			int iZ;

			Position() : iX(0), iY(0), iZ(0) {}
			Position(int _iX, int _iZ, int _iY = 0) : iX(_iX), iY(_iY), iZ(_iZ) {}
		};
		struct Border
		{
			MapInfo *pMap;
			int iX;
			int iY;
			int iZ;

			Border() : pMap(NULL), iX(0), iY(0), iZ(0) {}
			Border(MapInfo *_pMap, int _iX, int _iZ, int _iY = 0) : pMap(_pMap), iX(_iX), iY(_iY), iZ(_iZ) {}
		};
		struct WarpGate
		{
			MapInfo *pMap;
			int iX;
			int iY;
			int iZ;
			int iWidth;
			int iHeight;
			int iEffect;

			std::vector<WarpGate> vWarpGate;

			WarpGate() : pMap(NULL),iX(0), iY(0), iZ(0), iWidth(0), iHeight(0),iEffect(0) {}
			WarpGate(MapInfo *_pMap, int _iX, int _iZ, int _iY, int _iWidth, int _iHeight) : pMap(_pMap), iX(_iX), iY(_iY), iZ(_iZ), iWidth(_iWidth), iHeight(_iHeight) {}
			WarpGate(MapInfo *_pMap, int _iX, int _iZ, int _iY, int _iEffect) : pMap(_pMap), iX(_iX), iY(_iY), iZ(_iZ), iEffect(_iEffect) {}

			void Add(MapInfo *_pMap, int _iX, int _iZ, int _iY, int _iEffect = 0) { iEffect = _iEffect; vWarpGate.push_back(WarpGate(_pMap, _iX << 8, _iZ << 8, _iY << 8, _iEffect)); }
		};
		struct Sound
		{
			int iX;
			int iY;
			int iZ;
			int iRound;
			int iSound;

			Sound() : iX(0), iY(0), iZ(0), iRound(0), iSound(0) {}
			Sound(int _iX, int _iY, int _iZ, int _iRound, int _iSound) : iX(_iX), iY(_iY), iZ(_iZ), iRound(_iRound), iSound(_iSound) {}
		};
	public:
		MapInfo();
		MapInfo(EMapID eID, const char *pszName) { m_eID = eID, m_strName = pszName; }
		virtual ~MapInfo();

		void SetMapFileName(const char *pszName, const char *pszTitle);
		void SetSky(ESceneSky eMoon, ESceneSky eNoon, ESceneSky eNight);
		void SetType(EMapType eType);

		void AddSpawn(int iX, int iZ);
		void AddBorder(MapInfo *_pcMap, int iX, int iZ);
		WarpGate* AddWarpGate(int iX, int iZ, int iY, int iWidth, int iHeight);
		void AddSound(int iX, int iY, int iZ, int iRound, int iSound);
	private:
		EMapID m_eID = MAPID_Invalid;
		int m_iLevel = 1;
		EMapType m_eType = MAPTYPE_Town;
		std::string m_strName;
		std::string m_strMapName;
		std::string m_strTitleName;
		ESceneSky m_eMorning = SCENESKY_None;
		ESceneSky m_eNoon = SCENESKY_None;
		ESceneSky m_eNight = SCENESKY_None;
		std::vector<Position> m_vPosition;
		std::vector<Border> m_vBorder;
		std::vector<WarpGate> m_vWarpGate;
		std::vector<Sound> m_vSound;
	};
}
