#include "StdAfx.h"
#include "MapBase.h"

namespace MAP
{
	/*BaseMap::BaseMap()
	{

	}
	BaseMap::~BaseMap()
	{
		DELET(m_pcTerrain);
	}
	void BaseMap::AddModelEx(const char *pszFormat, ...)
	{
		va_list vl;

		char szBuf[256] = { 0 };

		va_start(vl, pszFormat);
		_vsnprintf_s(szBuf, _countof(szBuf), _TRUNCATE, pszFormat, vl);
		va_end(vl);

		m_vModel.push_back(MapModel(szBuf, FALSE));
	}
	void BaseMap::AddBorder(LPBASEMAP pMap, int iX, int iZ)
	{
		m_vBorder.push_back(MapBorder(pMap, iX, iZ));
		pMap->m_vBorder.push_back(MapBorder(this, iX, iZ));
	}
	LPBASEMAP BaseMap::GetBorder(int iX, int iZ)
	{
		for (auto &v : m_vBorder)
		{
			int iMapX = (iX - v.iX) >> 8;
			int iMapZ = (iZ - v.iZ) >> 8;

			int iDist = iMapX * iMapX + iMapZ * iMapZ;

			if (iDist < DIST_TRANSLEVEL_CONNECT && abs(iMapX) < 64 * fONE && abs(iMapZ) < 64 * fONE)
				return v.pMap;
		}

		return nullptr;
	}
	LPMAPTELEPORT BaseMap::AddTelePort(int iX, int iZ, int iY, int iSize, int iHeight)
	{
		m_vTeleport.push_back(MapTeleport(this, iX, iZ, iY, iSize, iHeight));

		return &m_vTeleport[m_vTeleport.size() - 1];
	}
	LPMAPTELEPORT BaseMap::GetTeleport(int iX, int iY, int iZ)
	{
		for (auto &v : m_vTeleport)
		{
			int iMapX, iMapZ, iMapY;
			int iDist;

			v.sPosition.GetPTDistanceXZY(&Point3D(iX, iY, iZ), iDist, iMapX, iMapZ, iMapY);

			if (v.vTeleport.size() > 0 && iMapX < 1024 && iMapZ < 1024 && iDist < (v.iSize * v.iSize) && iMapY < v.iHeight)
				return &v;
		}

		return nullptr;
	}
	LPMAPTELEPORT BaseMap::GetTeleport(int iLevel, int iEffect)
	{
		auto iSize = m_vTeleport.size();

		for (size_t t = 0; t < iSize * 2; t++)
		{
			auto i = (t >= iSize) ? t - iSize : rand() % iSize;

			auto pcBorder = &m_vTeleport[i];

			if (iLevel >= pcBorder->pcMap->GetLevel() && pcBorder->iEffect == iEffect)
				return pcBorder;
		}

		return nullptr;
	}
	void BaseMap::PlaySounds()
	{
		for (auto & v : m_vSound)
		{
			esPlayObjectSound2(v.iSound, v.iRound, v.iX, v.iY, v.iZ);
		}

		if (ResetLastVolumeDist() > 800)
			esPlayObjectSound2(-1, 0, 0, 0, 0);
	}
	BOOL BaseMap::CheckPosition(int iX, int iZ)
	{
		if (m_vSpawn.size() > 0)
		{
			for (auto &v : m_vSpawn)
			{
				if (abs(v.iX - iX) < 24 * fONE && abs(v.iY - iZ) < 24 * fONE)
					return TRUE;
			}
		}
		else
		{
			if (abs(m_sPositionCenter.iX - iX) < 24 * fONE && abs(m_sPositionCenter.iY - iZ) < 24 * fONE)
				return TRUE;
		}

		return FALSE;
	}
	Point2D BaseMap::GetPosition(int iX, int iZ)
	{
		Point2D sPosition;
		int iDist = 0;

		if (m_vSpawn.size() > 0)
		{
			if (iX == 0 && iZ == 0)
			{
				int i = rand() % m_vSpawn.size();

				sPosition = m_vSpawn[i];
			}
			else
			{
				for (auto &v : m_vSpawn)
				{
					auto iTempDist = v.GetPTDistance(Point2D(iX, iZ));

					if (iDist == 0 || iTempDist < iDist)
					{
						iDist = iTempDist;
						sPosition = v;
					}
				}
			}
		}
		else
		{
			sPosition = m_sPositionCenter;
		}

		return sPosition;
	}
	Point2D BaseMap::TranslateMap(int iX, int iZ)
	{
		Point2D sPosition = GetPosition(iX, iZ);

		MAPMODELHANDLE->LoadMap(this);

		auto pBorder = GetBorder(sPosition.iX, sPosition.iY);

		pBorder ? MAPMODELHANDLE->LoadMap(pBorder, this) : NULL;

		return sPosition;
	}
	void BaseMap::LoadTerrain()
	{
		DELET(m_pcTerrain);

		m_pcTerrain = new smSTAGE3D;

		AddLoaderStage(m_pcTerrain, (char *)m_strFilePatch.c_str());

		for (auto v : m_vModel)
		{
			auto pszName = (char *)v.strObject.c_str();

			v.bBip ? m_pcTerrain->AddObjectFile(pszName, pszName) : m_pcTerrain->AddObjectFile(pszName);
		}

		m_vModel.size() > 0 ? ReadTextures() : 0;
	}
	void BaseMap::Update(Point3D sPosition)
	{
		if (m_bHover)
			return;

		if (m_dwDelayTime < TICKCOUNT)
		{
			auto pTeleport = GetTeleport(sPosition.iX, sPosition.iY, sPosition.iZ);

			if (pTeleport)
			{
				int iLevel = lpCurPlayer->smCharInfo.Level;

				auto iRet = pTeleport->iEffect;
				m_dwDelayTime = TICKCOUNT + 3000;

				Point3D sPosition;

				switch (iRet)
				{
				case 0:
					sPosition = pTeleport->Load(this, iLevel, iRet);

					lpCurPlayer->SetStageFieldPos(sPosition.iX, sPosition.iZ);
					RestartPlayCount = 700;
					break;
				case 1:
					lpCurPlayer->MoveToStop(pTeleport->sPosition);
					StartEffect(sPosition + Point3D(0, 48 * fONE, 0), EFFECT_RETURN1);
					SkillPlaySound(SKILL_SOUND_LEARN, sPosition);
					sPosition = pTeleport->Load(this, iLevel, iRet);

					lpCurPlayer->SetStageFieldPos(sPosition.iX, sPosition.iY, sPosition.iZ, lpCurPlayer->m_sAngle.iX, lpCurPlayer->m_sAngle.iY, lpCurPlayer->m_sAngle.iZ);
					break;
				case 2:
					if (m_pcMap)
					{
						auto pBorder = m_pcMap->GetTeleport(iLevel, iRet);

						if (pBorder)
						{
							sPosition = pBorder->Load(this, iLevel, iRet);
							lpCurPlayer->SetStageFieldPos(sPosition.iX, sPosition.iY, sPosition.iZ, lpCurPlayer->m_sAngle.iX, lpCurPlayer->m_sAngle.iY, lpCurPlayer->m_sAngle.iZ);
						}

						m_pcMap = NULL;
					}
					else
					{
						lpCurPlayer->MoveToStop(pTeleport->sPosition);
						//MAPWARPHANDLE->Open();
						m_bHover = TRUE;
					}
					break;
				}
			}
		}
	}
	void BaseMap::SetTeleport(EMapID eID)
	{
		m_bHover = FALSE;
		m_dwDelayTime = 0;

		m_pcMap = (eID == MAPID_Invalid) ? this : NULL;

		int iLevel = lpCurPlayer->smCharInfo.Level;

		auto sBorder = GetTeleport(iLevel, 2);

		if (sBorder && m_pcMap != this)
		{
			Point3D sUserPosition = lpCurPlayer->GetPosition();

			int iDist = sUserPosition.GetPTDistance(sBorder->sPosition);

			if (iDist < DIST_TRANSLEVEL_LOW)
			{
				m_pcMap = MAPMODELHANDLE->GetMap(eID);
				StartEffect(sUserPosition + Point3D(0, 48 * fONE, 0), EFFECT_RETURN1);
				SkillPlaySound(SKILL_SOUND_LEARN, sUserPosition);
			}
		}
	}
	void BaseMap::LoadMinMap()
	{
		CLEARPTR(m_pcMinMap);
		CLEARPTR(m_pcTitleMap);

		UI::ImageLoader::DeleteImage(m_pcMinMap);
		UI::ImageLoader::DeleteImage(m_pcMinMap);

		m_pcMinMap = NULL;
		m_pcTitleMap = NULL;

		if (m_strMinMapFile.length())
		{
			m_pcMinMap = UI::ImageLoader::LoadImage_(m_strMinMapFile.c_str());

			if (m_strTitleFile.length())
				m_pcTitleMap = UI::ImageLoader::LoadImage_(m_strTitleFile.c_str());
		}
	}
	void BaseMap::Render2D(int iX, int iY, int iSize)
	{
		Rectangle2DF fRect;

		if (m_pcTerrain)
		{
			auto sRect = m_pcTerrain->GetMapRect();

			int iWidth = (sRect.iWidth - sRect.iX) >> 8;
			int iHeight = (sRect.iHeight - sRect.iY) >> 8;

			Point3D sUsePosition = lpCurPlayer->GetPosition();

			int iMapX = sUsePosition.iX - sRect.iX;
			int iMapZ = sRect.iHeight - sUsePosition.iZ;

			float fRenderX = (float)iX;
			float fRenderY = (float)iY;

			float fRenderWidth = 126;
			float fRenderHeight = 126;

			float fMapX = ((float)((iSize >> 8))) / (float)iWidth;
			float fMapY = ((float)((iSize >> 8))) / (float)iHeight;

			float fMapWdith = ((float)(iMapX >> 8)) / (float)iWidth;
			float fMapHeight = ((float)(iMapZ >> 8)) / (float)iHeight;

			fRect.fX = fMapWdith - fMapX;
			fRect.fY = fMapHeight - fMapY;
			fRect.fWidth = fMapWdith + fMapX;
			fRect.fHeight = fMapHeight + fMapY;

			if ((fRect.fX >= 0 || fRect.fWidth >= 0) && (fRect.fX <= 1 || fRect.fWidth <= 1))
			{
				if ((fRect.fY >= 0 || fRect.fHeight >= 0) && (fRect.fY <= 1 || fRect.fHeight <= 1))
				{
					if (fRect.fX < 0)
					{
						auto f = (-fRect.fX * (64 / fMapX));
						fRenderX += f;
						fRenderWidth -= f;
						fRect.fX = 0;
					}
					if (fRect.fWidth > 1)
					{
						auto f = ((fRect.fWidth - 1) * (64 / fMapX));
						fRenderWidth -= f;
						fRect.fWidth = 1;
					}
					if (fRect.fY < 0)
					{
						auto f = (-fRect.fY * (64 / fMapY));
						fRenderY += f;
						fRenderHeight -= f;
						fRect.fY = 0;
					}
					if (fRect.fHeight > 1)
					{
						auto f = ((fRect.fHeight - 1) * (64 / fMapY));
						fRenderHeight -= f;
						fRect.fHeight = 1;
					}

					m_pcMinMap ? UI::ImageRender::RenderQuad(m_pcMinMap, (int)fRenderX, (int)fRenderY, (int)fRenderWidth, (int)fRenderHeight, fRect, -1) : 0;
				}
			}
		}
	}
	void BaseMap::Render3D(Point3D sPosition, Point3D sAngle)
	{
		if (m_pcTerrain)
		{
			m_pcTerrain->SetDynLight(sPosition, DarkLevel);

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

				m_pcTerrain->RenderTerrain(sPosition, sAngle);

				cpRender->m_sColor = sColor;

				bRet ? cpRender->SetLightRange(DarkLightRange) : 0;
			}
			else
				m_pcTerrain->RenderTerrain(sPosition, sAngle);
		}
	}
	void BaseMap::RenderTitle(int iX, int iY)
	{
		m_pcTitleMap ? UI::ImageRender::Render(m_pcTitleMap, iX, iY - m_pcTitleMap->GetHeight(), m_pcTitleMap->GetWidth(), m_pcTitleMap->GetHeight(), -1) : 0;
	}
	void MapTeleport::Add(BaseMap *pcMap, int iX, int iZ, int iY, int iEffect)
	{
		this->iEffect = iEffect;

		vTeleport.push_back(MapTeleport(pcMap, iX, iZ, iY, iEffect));
	}
	Point3D MapTeleport::Load(BaseMap *pcMap, int iLevel, int iEffect)
	{
		Point3D sPosition;

		auto iSize = vTeleport.size();

		for (size_t t = 0; t < iSize * 2; t++)
		{
			auto i = (t >= iSize) ? t - iSize : rand() % iSize;

			auto sBorder = vTeleport[i];

			if (iLevel >= sBorder.pcMap->GetLevel() && sBorder.iEffect == iEffect)
			{
				sPosition = sBorder.sPosition;

				MAPMODELHANDLE->LoadMap(sBorder.pcMap, pcMap);
				break;
			}
		}

		return sPosition;
	}*/
}