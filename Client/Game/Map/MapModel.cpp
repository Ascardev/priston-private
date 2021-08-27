#include "StdAfx.h"
#include "MapModel.h"

namespace MAP
{
	Model::Model() : Info()
	{

	}
	Model::Model(EMapID eID, const char *pszName) : Info(eID, pszName)
	{
		m_pTerrain = nullptr;
	}
	Model::~Model()
	{
		DELET(m_pTerrain);
	}
	void Model::Load()
	{
		DELET(m_pTerrain);

		m_pTerrain = new smSTAGE3D;

		AddLoaderStage(m_pTerrain, (char *)m_strName.c_str());

		for (auto v : m_vElementModel)
		{
			auto pszName = (char *)v.m_strFileName.c_str();

			if (v.m_bBip)
				m_pTerrain->AddObjectFile(pszName, pszName);
			else
				m_pTerrain->AddObjectFile(pszName);
		}

		m_pTerrain->ReadTextures();
	}
	void Model::Render(Point3D sPosition, Point3D sAngle)
	{
		if (m_pTerrain)
		{
			m_pTerrain->SetDynLight(sPosition, DarkLevel);

			if (DarkLevel > 0 && m_eMapType == MAPTYPE_Town)
			{
				auto sColor = cpRender->GetColor();

				cpRender->m_sColor = sColor >> 1;

				BOOL bRet = FALSE;

				if (cpRender->GetLightRange() == DarkLightRange)
				{
					cpRender->SetLightRange(0);
					bRet = TRUE;
				}

				m_pTerrain->RenderTerrain(sPosition, sAngle);

				cpRender->m_sColor = sColor;

				bRet ? cpRender->SetLightRange(DarkLightRange) : 0;
			}
			else
				m_pTerrain->RenderTerrain(sPosition, sAngle);
		}
	}
	void Model::Update()
	{
		// µÆ¹â
		if (m_eMapType != MAPTYPE_ChessRoom && (dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_DARKNESS || m_eMapType == MAPTYPE_Dungeon))
		{
			m_pTerrain->SetNightTime(TRUE);
		}
		else
		{
			m_pTerrain->SetNightTime(FALSE);
		}

		// Ìì¿Õ
		if (m_iMode == 0)
		{
			EMapSky eSky = MAPSKY_None;

			if (dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_NIGHT)
			{
				eSky = m_eSkyNight;
			}
			else if (dwGameHour >= GAME_HOUR_DAY && dwGameHour < GAME_HOUR_GLOW)
			{
				eSky = m_eSkyMoon;
			}
			else
			{
				eSky = m_eSkySoon;
			}

			if (eSky != MAPSKY_None)
				SKYHANDLE->Open(eSky);
		}
		
		//ÒôÐ§
		if (m_iMode == 0)
		{
			if (m_eMapType == MAPTYPE_Wasteland)
			{
				esPlayEffectBgm(3);
			}
			else if (m_eMapType == MAPTYPE_Desert)
			{
				esPlayEffectBgm(4);
			}
			else if (m_eMapType == MAPTYPE_Dungeon)
			{
				if (m_eID == MAPID_AncientPrisonF1 || m_eID == MAPID_AncientPrisonF2 || m_eID == MAPID_AncientPrisonF3)
				{
					esPlayEffectBgm(5);
				}
				else if (m_eID == MAPID_CursedTempleF1 || m_eID == MAPID_CursedTempleF2)
				{
					esPlayEffectBgm(6);
				}
				else if (m_eID == MAPID_MushroomCave || m_eID == MAPID_BeehiveCave)
				{
					esPlayEffectBgm(7);
				}
			}
				
			
			switch (m_eMapType)
			{
			case MAPTYPE_Wasteland:
				esPlayEffectBgm(3);
				break;
			case MAPTYPE_Desert:
				esPlayEffectBgm(4);
				break;
			case MAPTYPE_Dungeon:
				switch (pcMap->GetID())
				{
				case MAPID_AncientPrisonF1:
				case MAPID_AncientPrisonF2:
				case MAPID_AncientPrisonF3:
				case MAPID_QuestArena:
					esPlayEffectBgm(5);
					break;
				case MAPID_CursedTempleF1:
				case MAPID_CursedTempleF2:
					esPlayEffectBgm(6);
					break;
				case MAPID_MushroomCave:
				case MAPID_BeehiveCave:
					esPlayEffectBgm(7);
					break;
				case MAPID_DarkSanctuary:
					esPlayEffectBgm(8);
					break;
				}
				break;
			case MAPTYPE_Forest:
				if (dwGameHour < GAME_HOUR_DAY || dwGameHour >= GAME_HOUR_DARKNESS)
					esPlayEffectBgm(2);
				else
					esPlayEffectBgm(1);
				break;

			case MAPTYPE_Town:
				esPlayEffectBgm(0);
				break;

			case MAPTYPE_ChessRoom:
				esPlayEffectBgm(-1);
				break;

			case MAPTYPE_Iron:
				esPlayEffectBgm(9);
				break;

			case MAPTYPE_Ice:
				esPlayEffectBgm(12);
				break;
			}
		}
	}
}