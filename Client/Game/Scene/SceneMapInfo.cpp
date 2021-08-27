#include "StdAfx.h"
#include "SceneMapInfo.h"

namespace SCENE
{
	MapInfo::MapInfo() : Element()
	{

	}
	MapInfo::~MapInfo()
	{

	}
	void MapInfo::SetMapFileName(const char *pszName, const char *pszTitle)
	{
		m_strMapName = pszName; m_strTitleName = pszTitle;
	}
	void MapInfo::SetSky(ESceneSky eMoon, ESceneSky eNoon, ESceneSky eNight)
	{
		m_eMorning = eMoon; m_eNoon = eNoon; m_eNight = eNight;
	}
	void MapInfo::SetType(EMapType eType)
	{
		m_eType = eType;
	}
	void MapInfo::AddSpawn(int iX, int iZ)
	{
		m_vPosition.push_back(Position(iX << 8, iZ << 8, 0));
	}
	void MapInfo::AddBorder(MapInfo *pMap, int iX, int iZ)
	{
		this->m_vBorder.push_back(Border(pMap,iX << 8, iZ << 8, 0));
		pMap->m_vBorder.push_back(Border(this,iX << 8, iZ << 8, 0));
	}
	MapInfo::WarpGate* MapInfo::AddWarpGate(int iX, int iZ, int iY, int iWidth, int iHeight)
	{
		m_vWarpGate.push_back(WarpGate(this, iX << 8, iZ << 8, iY << 8, iWidth, iHeight));

		return &m_vWarpGate[m_vWarpGate.size() - 1];
	}
	void MapInfo::AddSound(int iX, int iY, int iZ, int iRound, int iSound)
	{
		m_vSound.push_back(Sound(iX << 8, iY << 8, iZ << 8, iRound, iSound));
	}
}