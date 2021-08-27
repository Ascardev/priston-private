#include "StdAfx.h"
#include "MiniMapHandle.h"

CMiniMapHandle::CMiniMapHandle()
{

}
CMiniMapHandle::~CMiniMapHandle()
{

}
void CMiniMapHandle::Init()
{
	m_pcMaskBackground = UI::ImageLoader::LoadImage_("Resources\\UI\\MiniMap\\mask_minimap.tga");
	m_pcMaskBackgroundActive = UI::ImageLoader::LoadImage_("Resources\\UI\\MiniMap\\Mask_activeminimap.tga");
	m_pcBorderImage = UI::ImageLoader::LoadImage_("Resources\\UI\\MiniMap\\Border.png");
	m_pcUserPoint = UI::ImageLoader::LoadImage_("Resources\\UI\\MiniMap\\Arrow.png");
	m_pcNPCPoint = UI::ImageLoader::LoadImage_("Resources\\UI\\MiniMap\\Npc.png");
	m_pcImageRaidIcon = UI::ImageLoader::LoadImage_("Resources\\UI\\Party\\RaidMember.png");
	m_pcImageEnemyIcon = UI::ImageLoader::LoadImage_("Resources\\UI\\MiniMap\\enemy.png");
	m_pcImageFriendlyIcon = UI::ImageLoader::LoadImage_("Resources\\UI\\MiniMap\\friendly.png");
	m_pcImageNextBoss = UI::ImageLoader::LoadImage_("Resources\\UI\\MiniMap\\nextboss.png");

	for (int i = 0; i < 6; i++)
	{
		m_pcaImagesPartyMemberIcon[i] = UI::ImageLoader::LoadImage_("Resources\\UI\\party\\member%d.png", i + 1);
	}

	m_pTooltipUnit = std::make_shared<UI::ToolTip>(Rectangle2D());
	m_pTooltipUnit->Init();
	m_pTooltipUnit->SetFont("Arial", 16, -1);
	m_pTooltipUnit->SetPosition(TOOLTIPPOSITION_Top);
	m_pTooltipUnit->SetFollowMouse(FALSE);
	m_pTooltipUnit->SetHover(TRUE);
	m_pTooltipUnit->Open();

	m_pEffectMask = GRAPHICDEVICE->GetEffectFactory()->MakeEffect("Resources\\Shaders\\UI\\Minimap.fx");
	m_pRenderTargetMask = GRAPHICDEVICE->MakeRenderTarget(-1, MINIMAP_SIZE, MINIMAP_SIZE);
	m_pFont = FONTHANDLE->MakeFont("Arial", 15, 0, FALSE, FALSE);

	SetMiniMapPostion(Point2D((RESOLUTION_WIDTH - MINIMAP_SIZE) - 16, (RESOLUTION_HEIGHT - MINIMAP_SIZE) - 50));
}
void CMiniMapHandle::Shutdown()
{
	CLEARPTR(m_pcMaskBackground);
	CLEARPTR(m_pcMaskBackgroundActive);
	CLEARPTR(m_pcBorderImage);
	CLEARPTR(m_pcUserPoint);
	CLEARPTR(m_pcNPCPoint);
	CLEARPTR(m_pcImageRaidIcon);
	CLEARPTR(m_pcImageEnemyIcon);
	CLEARPTR(m_pcImageFriendlyIcon);
	CLEARPTR(m_pcImageNextBoss);

	for (int i = 0; i < 6; i++)
	{
		CLEARPTR(m_pcaImagesPartyMemberIcon[i]);
	}

	UI::ImageLoader::DeleteImage(m_pcMaskBackground);
	UI::ImageLoader::DeleteImage(m_pcMaskBackgroundActive);
	UI::ImageLoader::DeleteImage(m_pcBorderImage);
	UI::ImageLoader::DeleteImage(m_pcUserPoint);
	UI::ImageLoader::DeleteImage(m_pcNPCPoint);
	UI::ImageLoader::DeleteImage(m_pcImageRaidIcon);
	UI::ImageLoader::DeleteImage(m_pcImageEnemyIcon);
	UI::ImageLoader::DeleteImage(m_pcImageFriendlyIcon);
	UI::ImageLoader::DeleteImage(m_pcImageNextBoss);

	for (int i = 0; i < 6; i++)
	{
		UI::ImageLoader::DeleteImage(m_pcaImagesPartyMemberIcon[i]);
	}

	for (int i = 0; i < 2; i++)
	{
		MiniMapData *psMaps = GetMiniMapData(i);

		if (psMaps->psImage)
		{
			CLEARPTR(psMaps->psImage);
			UI::ImageLoader::DeleteImage(psMaps->psImage);
		}

		if (psMaps->psImageTitle)
		{
			CLEARPTR(psMaps->psImageTitle);
			UI::ImageLoader::DeleteImage(psMaps->psImageTitle);
		}
	}
}
void CMiniMapHandle::Render()
{
	if (IsOpen() && IsHave())
	{
		m_bIsHoverUnit = FALSE;

		//Render Minimaps
		RenderMap(UNIT->sPosition);

		//Render user Point
		RenderUser(UNIT->sAngle);

		//Render Border
		if (m_bActive || SETTINGHANDLE->Get().bMinimapAlwaysActive)
		{
			UI::ImageRender::Render(m_pcBorderImage, GetMiniMapPostion().iX - 9, GetMiniMapPostion().iY - 24, 144, 158, -1);

			int i = UNIT->iLoadedMapIndex >= 0 ? UNIT->iLoadedMapIndex : 0;

			UI::ImageRender::Render(GetMiniMapData(i)->psImageTitle,
				GetMiniMapPostion().iX - 1,
				GetMiniMapPostion().iY - GetMiniMapData(i)->psImageTitle->GetHeight(),
				GetMiniMapData(i)->psImageTitle->GetWidth(),
				GetMiniMapData(i)->psImageTitle->GetHeight(), 0, 0, -1, FALSE);
		}

		if (m_bIsHoverUnit)
		{
			m_pTooltipUnit->SetText(m_strHoverUnit);
			m_pTooltipUnit->SetTextColor(m_cHoverColor);
			m_pTooltipUnit->Render(m_sHoverUnitBox.iX, m_sHoverUnitBox.iY, 0, 0, 0, 0);
		}
	}
}
void CMiniMapHandle::Update(float fTime)
{
	m_dwTickTime++;

	//1 Second?
	if ((m_dwTickTime % 10) == 0)
	{
		//Decrease Boss Time
		if (m_dwNextBossTime > 0)
		{
			m_dwNextBossTime--;
			//Boss Time End? Hide.
			if (m_dwNextBossTime == 0)
			{
				m_bShowBossTime = FALSE;

				//Get new Boss Time
				ProcessPacket(&PacketBossTimeUpdate(MAP_ID));
			}
		}
	}
}
BOOL CMiniMapHandle::OnMouseClick(class INPUTS::Mouse *pcMouse)
{
	BOOL bRet = FALSE;

	if (m_bSelected)
	{
		if (pcMouse->GetEvent() == ClickUpL)
			m_bSelected = FALSE;
	}
	else if (!m_bSelected && !SETTINGHANDLE->Get().bLockUI && pcMouse->GetEvent() == ClickDownL && pcMouse->GetPosition()->Inside(Rectangle2D(GetMiniMapPostion().iX, GetMiniMapPostion().iY - 16, MINIMAP_SIZE, MINIMAP_SIZE + 16)))
	{
		int iExtraAdd = 0;
		m_bSelected = TRUE;

		if (pcMouse->GetPosition()->Inside(Rectangle2D(GetMiniMapPostion().iX, GetMiniMapPostion().iY - 16, MINIMAP_SIZE, 16)))
			iExtraAdd += 15;

		m_sPointMouse.iX = abs(pcMouse->GetPosition()->iX - GetMiniMapPostion().iX);
		m_sPointMouse.iY = abs(pcMouse->GetPosition()->iY - GetMiniMapPostion().iY) - iExtraAdd;
		bRet = TRUE;
	}

	if (m_bActive && !m_bSelected)
		bRet = TRUE;

	return bRet;
}
void CMiniMapHandle::OnMouseMove(class INPUTS::Mouse * pcMouse)
{
	m_bActive = (pcMouse->GetPosition()->Inside(Rectangle2D(GetMiniMapPostion().iX, GetMiniMapPostion().iY - 16, MINIMAP_SIZE, MINIMAP_SIZE + 16))) ? TRUE : FALSE;

	if (m_bSelected)
	{
		int iX = pcMouse->GetPosition()->iX - m_sPointMouse.iX;
		int iY = pcMouse->GetPosition()->iY - m_sPointMouse.iY;

		SetMiniMapPostion(Point2D(iX < 0 ? 0 : iX, iY < 0 ? 0 : iY));
	}
}
void CMiniMapHandle::RenderMap(Point3D sUserPosition)
{
	//New Render Target to render the minimap
	if (GRAPHICDEVICE->SetRenderTarget(m_pRenderTargetMask))
	{
		//Clear Render Target
		GRAPHICDEVICE->Clear(TRUE, TRUE, FALSE);

		float fMapSizeScale = 15.0f - ((MINIMAP_TEXTURE_SCALE * 10.0f) / 100.0f);

		int iMinimapSize = 256 * 256 * (int)fMapSizeScale;

		//Draw MiniMap
		DrawMinimap(GetMiniMapData(1), 0, 0, iMinimapSize);
		DrawMinimap(GetMiniMapData(0), 0, 0, iMinimapSize);

		//Units
		for (int i = 0; i < MAX_UNITS; i++)
		{
			Unit * pc = chrOtherPlayer + i;

			if (pc->bActive)
			{
				if (SETTINGHANDLE->Get().bShowNPCs)
					if (RenderNPC(pc, sUserPosition, iMinimapSize))
						continue;

				if (RenderPlayer(pc, sUserPosition, UNIT->sCharacterData.iClanID, iMinimapSize))
					continue;
			}
		}

		RenderParty(sUserPosition, UNIT->iID, iMinimapSize);

		//Back Old Render Target
		GRAPHICDEVICE->UnsetRenderTarget();

		//Set Sprite Effect...
		UI::ImageRender::SetEffect(m_pEffectMask);
		m_pEffectMask->SetTechnique("MaskScale");

		if (m_pEffectMask->Begin() >= 0)
		{
			//Set Texture Mask Sampler
			m_pEffectMask->SetTexture("MaskTexture", (m_bActive || SETTINGHANDLE->Get().bMinimapAlwaysActive) ? m_pcMaskBackgroundActive->GetTexture() : m_pcMaskBackground->GetTexture());

			//Render the Render Target and mask it on effect
			UI::ImageRender::Render(m_pRenderTargetMask->GetTexture(), GetMiniMapPostion().iX, GetMiniMapPostion().iY, m_pRenderTargetMask->GetWidth(), m_pRenderTargetMask->GetHeight(), 0, 0, D3DCOLOR_XRGB(255, 255, 255), FALSE);

			m_pEffectMask->End();
		}

		UI::ImageRender::SetEffect(NULL);
	}
}
void CMiniMapHandle::RenderUser(Point3D sUserAngle)
{
	//Angle of User Point
	int iAngle = ((sUserAngle.iY * 360) / ANGLE_360) + 180;
	UI::ImageRender::Render(m_pcUserPoint, GetMiniMapPostion().iX + (MINIMAP_SIZE >> 1) - 8, GetMiniMapPostion().iY + (MINIMAP_SIZE >> 1) - 8, m_pcUserPoint->GetWidth(), m_pcUserPoint->GetHeight(), 0, 0, -1, 0.7f, (float)iAngle);
}
BOOL CMiniMapHandle::RenderNPC(Unit * pcUnit, Point3D sUserPosition, int iSize)
{
	if (pcUnit->sCharacterData.iType == CHARACTERTYPE_NPC)
	{
		if (pcUnit->sPosition.WithinPTDistance(&sUserPosition, DISTANCE_UNIT_VIEWLIMIT))
		{
			Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, pcUnit->sPosition, m_pcNPCPoint->GetWidth() >> 1, m_pcNPCPoint->GetHeight() >> 1, iSize);
			Rectangle2D sBox = Rectangle2D(sPosition.iX + GetMiniMapPostion().iX, sPosition.iY + GetMiniMapPostion().iY, m_pcNPCPoint->GetWidth(), m_pcNPCPoint->GetHeight());

			UI::ImageRender::Render(m_pcNPCPoint, sPosition.iX, sPosition.iY, m_pcNPCPoint->GetWidth(), m_pcNPCPoint->GetHeight(), 0, 0, -1);

			if (MOUSEHANDLER->GetPosition()->Inside(sBox))
			{
				m_bIsHoverUnit = TRUE;
				m_sHoverUnitBox = sBox;
				m_strHoverUnit = pcUnit->sCharacterData.szName;
				m_cHoverColor = UI::Color(255, 255, 255, 255);
			}
		}

		return TRUE;
	}

	return FALSE;
}
BOOL CMiniMapHandle::RenderPlayer(Unit * pcUnit, Point3D sUserPosition, int iUserClanID, int iSize)
{
	if (pcUnit->iCharacterType == CHARACTERTYPE_Player || pcUnit->sCharacterData.iType == CHARACTERTYPE_Player)
	{
		//Allied Clan
		if (pcUnit->sCharacterData.iClanID > 0 && pcUnit->sCharacterData.iClanID == iUserClanID && SETTINGHANDLE->Get().bShowClanMembers)
		{
			if (pcUnit->sPosition.WithinPTDistance(&sUserPosition, DISTANCE_UNIT_VIEWLIMIT))
			{
				Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, pcUnit->sPosition, m_pcImageFriendlyIcon->GetWidth() >> 1, m_pcImageFriendlyIcon->GetHeight() >> 1, iSize);

				UI::ImageRender::Render(m_pcImageFriendlyIcon, sPosition.iX, sPosition.iY, m_pcImageFriendlyIcon->GetWidth(), m_pcImageFriendlyIcon->GetHeight(), 0, 0, -1);
			}
		}
		else if (MAP_ID == MAPID_BlessCastle && SETTINGHANDLE->Get().bShowEnemies)
		{
			//Enemy Clan
			if (pcUnit->sPosition.WithinPTDistance(&sUserPosition, DISTANCE_UNIT_VIEWLIMIT))
			{
				Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, pcUnit->sPosition, m_pcImageEnemyIcon->GetWidth() >> 1, m_pcImageEnemyIcon->GetHeight() >> 1, iSize);

				UI::ImageRender::Render(m_pcImageEnemyIcon, sPosition.iX, sPosition.iY, m_pcImageEnemyIcon->GetWidth(), m_pcImageEnemyIcon->GetHeight(), 0, 0, -1);
			}
		}

		return TRUE;
	}

	return FALSE;
}
BOOL CMiniMapHandle::RenderParty(Point3D sUserPosition, int iUserID, int iSize)
{
	if (PARTYHANDLE->GetPartyData().iMembersCount > 0 && SETTINGHANDLE->Get().bShowPartyMembers)
	{
		for (int i = 0; i < PARTYHANDLE->GetPartyData().iMembersCount; i++)
		{
			PartyMember sMember = PARTYHANDLE->GetPartyData().saMembers[i];
			UI::Image * pImage = m_pcaImagesPartyMemberIcon[i];

			if (sMember.sData.sLevel > 0 && (sMember.sData.iID != iUserID) && pImage)
			{
				Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, sMember.sData.sPosition, pImage->GetWidth() >> 1, pImage->GetHeight() >> 1, iSize);
				Rectangle2D sBox = Rectangle2D(sPosition.iX + GetMiniMapPostion().iX, sPosition.iY + GetMiniMapPostion().iY, pImage->GetWidth(), pImage->GetHeight());

				UI::ImageRender::Render(pImage, sPosition.iX, sPosition.iY, pImage->GetWidth(), pImage->GetHeight(), 0, 0, -1);

				if (MOUSEHANDLER->GetPosition()->Inside(sBox))
				{
					m_bIsHoverUnit = TRUE;
					m_sHoverUnitBox = sBox;
					m_strHoverUnit = sMember.szCharacterName;
					m_cHoverColor = UI::Color(255, 175, 230, 175);
				}
			}
		}
	}

	if (PARTYHANDLE->GetPartyData().iRaidCount > 0 && SETTINGHANDLE->Get().bShowRaidMembers)
	{
		for (int i = 0; i < PARTYHANDLE->GetPartyData().iRaidCount; i++)
		{
			for (size_t j = 0; j < MAX_PARTY_MEMBERS; j++)
			{
				PartyRaidMember sMember = PARTYHANDLE->GetPartyData().saRaid[i].saMembers[j];

				if (sMember.sData.iID && sMember.szCharacterName[0] != 0)
				{
					Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, sMember.sData.sPosition, m_pcImageRaidIcon->GetWidth() >> 1, m_pcImageRaidIcon->GetHeight() >> 1, iSize);
					Rectangle2D sBox = Rectangle2D(sPosition.iX + GetMiniMapPostion().iX, sPosition.iY + GetMiniMapPostion().iY, m_pcImageRaidIcon->GetWidth(), m_pcImageRaidIcon->GetHeight());

					UI::ImageRender::Render(m_pcImageRaidIcon, sPosition.iX, sPosition.iY, m_pcImageRaidIcon->GetWidth(), m_pcImageRaidIcon->GetHeight(), 0, 0, -1);

					if (MOUSEHANDLER->GetPosition()->Inside(sBox))
					{
						m_bIsHoverUnit = TRUE;
						m_sHoverUnitBox = sBox;
						m_strHoverUnit = sMember.szCharacterName;
						m_cHoverColor = UI::Color(255, 40, 240, 230);
					}
				}
			}
		}
	}

	return TRUE;
}
void CMiniMapHandle::LoadMiniMap(int iIndex, BaseMap * pcMap, smSTAGE3D * pcStage)
{
	MiniMapData * psMap = GetMiniMapData(iIndex);

	psMap->sRectangle = Rectangle2D(
		pcStage->StageMapRect.left,
		pcStage->StageMapRect.top,
		pcStage->StageMapRect.right,
		pcStage->StageMapRect.bottom);

	if (psMap->psImage)
	{
		CLEARPTR(psMap->psImage);
		UI::ImageLoader::DeleteImage(psMap->psImage);
		psMap->psImage = nullptr;
	}
	if (psMap->psImageTitle)
	{
		CLEARPTR(psMap->psImageTitle);
		UI::ImageLoader::DeleteImage(psMap->psImageTitle);
		psMap->psImageTitle = nullptr;
	}

	if (pcMap->szMiniMapFilePath[0])
	{
		psMap->psImage = UI::ImageLoader::LoadImage_(pcMap->szMiniMapFilePath);

		int iX = (pcStage->StageMapRect.right - pcStage->StageMapRect.left) >> 8;
		int iY = (pcStage->StageMapRect.bottom - pcStage->StageMapRect.top) >> 8;

		psMap->sPosition = Point2D(iX, iY);
	}

	if (pcMap->szMiniMapNameFilePath[0])
	{
		psMap->psImageTitle = UI::ImageLoader::LoadImage_(pcMap->szMiniMapNameFilePath);
	}
}
void CMiniMapHandle::DrawMinimap(MiniMapData * psMap, int iX, int iY, int iSize)
{
	Rectangle2D sRectangle = psMap->sRectangle;

	Point3D sPosition = UNIT->sPosition;

	int iWidth = psMap->sPosition.iX;
	int iHeight = psMap->sPosition.iY;

	int iMapX = sPosition.iX - sRectangle.iX;
	int iMapZ = sRectangle.iHeight - sPosition.iZ;

	float fRenderX = (float)iX;
	float fRenderY = (float)iY;

	float fRenderWidth = MINIMAP_SIZE - 2;
	float fRenderHeight = MINIMAP_SIZE - 2;

	float fMapX = ((float)((iSize >> 8))) / (float)iWidth;
	float fMapY = ((float)((iSize >> 8))) / (float)iHeight;

	float fMapWdith = ((float)(iMapX >> 8)) / (float)iWidth;
	float fMapHeight = ((float)(iMapZ >> 8)) / (float)iHeight;

	Rectangle2DF fRect = Rectangle2DF(fMapWdith - fMapX, fMapHeight - fMapY, fMapWdith + fMapX, fMapHeight + fMapY);

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

			UI::ImageRender::RenderQuad(psMap->psImage, (int)fRenderX, (int)fRenderY, (int)fRenderWidth, (int)fRenderHeight, fRect, -1);
		}
	}
}
Point2D CMiniMapHandle::GetMinimapPositionFromCenter(Point3D sCenterPosition, Point3D sObjectPosition, int iWidthPoint, int iHeightPoint, int iSize)
{
	//Compute position from center to object
	int iX = sObjectPosition.iX - sCenterPosition.iX;
	int iZ = sObjectPosition.iZ - sCenterPosition.iZ;

	//Divide points to inside of minimap
	iX /= (iSize / (MINIMAP_SIZE / 2));
	iZ /= (iSize / (MINIMAP_SIZE / 2));

	//Negative Z, since it will up...
	iZ = -iZ;

	return Point2D(iX + (MINIMAP_SIZE >> 1) - iWidthPoint, iZ + (MINIMAP_SIZE >> 1) - iHeightPoint);
}
void CMiniMapHandle::OnResolutionChanged()
{
	SetMiniMapPostion(Point2D((RESOLUTION_WIDTH - MINIMAP_SIZE) - 16, (RESOLUTION_HEIGHT - MINIMAP_SIZE) - 50));
}
void CMiniMapHandle::HandlePacket(PacketBossTimeUpdate * psPacket)
{
	m_strNextBossName = psPacket->szBossName;
	m_dwNextBossTime = psPacket->dwTime;
	m_bShowBossTime = m_dwNextBossTime ? TRUE : FALSE;
}
void CMiniMapHandle::ProcessPacket(PacketBossTimeUpdate * psPacket)
{
	psPacket->iLength = sizeof(PacketBossTimeUpdate);
	psPacket->iHeader = PKTHDR_BossTimeUpdate;
	SENDPACKETG(psPacket);
}
BOOL CMiniMapHandle::IsHave()
{
	BOOL bRet = FALSE;

	int iIndex = UNIT->iLoadedMapIndex;

	if (iIndex >= 0)
	{
		bRet = TRUE;

		EMapID iMapID = STAGE_MAP[iIndex]->iMapID;

		if (iMapID == MAPID_Bellatra ||
			iMapID == MAPID_KelvezuLair ||
			iMapID == MAPID_ChessRoom ||
			iMapID == MAPID_QuestArena ||
			iMapID == MAPID_T5QuestArena)
		{
			bRet = FALSE;
		}
	}

	return bRet;
}