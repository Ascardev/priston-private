#pragma once

namespace MAP
{
	class Info
	{
	public:
		Info();
		Info(EMapID eID, const char *pszName);
		virtual ~Info();
		void SetTerrainFile(const char *pszFile) { m_strName = pszFile; }
		void SetMiniMapFile(const char *pszFile, const char *pszTitleFile) { m_strMap = pszFile; m_strTitle = pszTitleFile; }
		void SetType(EMapType eType) { m_eMapType = eType; }
		void SetSky(EMapSky eMoon, EMapSky eSoon, EMapSky eNight) { m_eSkyMoon = eMoon; m_eSkySoon = eSoon; m_eSkyNight = eNight; }
		void SetBackgroundMusic(EBackgroundMusicID eID){m_eBackgroundMusicID = eID;}
		void AddSpawn(int iX, int iZ);
		void AddBorder(EMapID eID, int iX, int iZ);
		ElementWarpGate *AddWarpGate(int iX, int iZ, int iY, int iWidth, int iHeight, int iType);
		void AddSound(int iX, int iY, int iZ, int iRound, int iSound);
		void AddStaticModel(const char *pszName, BOOL bBip = FALSE);
		void AddModelEx(const char *pszFormat, ...);
	private:
		EMapID m_eID = MAPID_Invalid;
		EMapType m_eMapType = MAPTYPE_Town;
		EMapSky m_eSkyMoon = MAPSKY_None;
		EMapSky m_eSkySoon = MAPSKY_None;
		EMapSky m_eSkyNight = MAPSKY_None;
		EBackgroundMusicID m_eBackgroundMusicID = BACKGROUNDMUSICID_TRIGGERED;

		std::string m_strName;
		std::string m_strMap;
		std::string m_strTitle;
		int m_iLevel = 1;

		std::vector<Element *> m_vpElements;
	};
}