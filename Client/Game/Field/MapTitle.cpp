#include "StdAfx.h"
#include "MapTitle.h"

namespace MAP
{
	/*Title::Title()
	{

	}
	Title::~Title()
	{

	}
	void Title::Init()
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

		m_pcToolTip = std::make_shared<UI::ToolTip>(Rectangle2D());
		m_pcToolTip->Init();
		m_pcToolTip->SetFont("Arial", 16, -1);
		m_pcToolTip->SetPosition(TOOLTIPPOSITION_Top);
		m_pcToolTip->SetFollowMouse(FALSE);
		m_pcToolTip->SetHover(TRUE);
		m_pcToolTip->Open();

		m_pEffectMask = GRAPHICDEVICE->GetEffectFactory()->MakeEffect("Resources\\Shaders\\UI\\Minimap.fx");
		m_pRenderTargetMask = GRAPHICDEVICE->MakeRenderTarget(-1, MINIMAP_SIZE, MINIMAP_SIZE);
		m_pFont = FONTHANDLE->MakeFont("Arial", 15, 0, FALSE, FALSE);

		SetMiniMapPostion(Point2D((RESOLUTION_WIDTH - MINIMAP_SIZE) - 16, (RESOLUTION_HEIGHT - MINIMAP_SIZE) - 50));
	}
	void Title::Shutdown()
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
	}
	void Title::Render()
	{
		if (m_bFlag && IsHave())
		{
			m_bIsHover = FALSE;

			RenderMap(lpCurPlayer->GetPosition());
			RenderUser(Point3D(lpCurPlayer->m_sAngle.iX, lpCurPlayer->m_sAngle.iY, lpCurPlayer->m_sAngle.iZ));

			if (m_bActive || SETTINGSHANDLE->GetModel()->Get().bMinimapAlwaysActive)
			{
				UI::ImageRender::Render(m_pcBorderImage, GetMiniMapPostion().iX - 9, GetMiniMapPostion().iY - 24, 144, 158, -1);

				auto pcMap = lpCurPlayer->GetMap();

				pcMap ? pcMap->RenderTitle(GetMiniMapPostion().iX, GetMiniMapPostion().iY) : 0;
			}
			if (m_bIsHover)
			{
				m_pcToolTip->SetText(m_strHoverUnit);
				m_pcToolTip->SetTextColor(m_cHoverColor);
				m_pcToolTip->Render(m_sHoverUnitBox.iX, m_sHoverUnitBox.iY, 0, 0, 0, 0);
			}
		}
	}
	BOOL Title::OnMouseClick(INPUTS::LPMOUSE pcMouse)
	{
		BOOL bRet = FALSE;

		if (m_bFlag && IsHave())
		{
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
		}

		return bRet;
	}
	void Title::OnMouseMove(INPUTS::LPMOUSE pcMouse)
	{
		if (m_bFlag && IsHave())
		{
			if (pcMouse->GetPosition()->Inside(Rectangle2D(GetMiniMapPostion().iX, GetMiniMapPostion().iY - 16, MINIMAP_SIZE, MINIMAP_SIZE + 16)))
				m_bActive = TRUE;
			else
				m_bActive = FALSE;

			if (m_bSelected)
			{
				int iX = pcMouse->GetPosition()->iX - m_sPointMouse.iX;
				int iY = pcMouse->GetPosition()->iY - m_sPointMouse.iY;

				SetMiniMapPostion(Point2D(iX < 0 ? 0 : iX, iY < 0 ? 0 : iY));
			}
		}
	}
	void Title::RenderMap(Point3D sUserPosition)
	{
		// New Render Target to Render the Minimap
		if (GRAPHICDEVICE->SetRenderTarget(m_pRenderTargetMask))
		{
			//Clear Render Target
			GRAPHICDEVICE->Clear(TRUE, TRUE, FALSE);

			float fMapSizeScale = 15.0f - ((MINIMAP_TEXTURE_SCALE * 10.0f) / 100.0f);

			int iMinimapSize = 256 * 256 * (int)fMapSizeScale;

			for (int i = 0; i < 2; i++)
			{
				auto pcMap = MAPMODELHANDLE->GetActiveMap(i);

				pcMap ? pcMap->Render2D(0, 0, iMinimapSize) : 0;
			}

			for (int i = 0; i < OTHER_PLAYER_MAX; i++)
			{
				auto pcChar = chrOtherPlayer + i;

				if (pcChar->bActive)
				{
					if (SETTINGHANDLE->Get().bShowNPCs)
						RenderNPC(pcChar, sUserPosition, iMinimapSize);
				}
			}

			GRAPHICDEVICE->UnsetRenderTarget();

			//Set Sprite Effect...
			UI::ImageRender::SetEffect(m_pEffectMask);

			m_pEffectMask->SetTechnique("MaskScale");

			if (m_pEffectMask->Begin() >= 0)
			{
				//Set Texture Mask Sampler
				//D3DXHANDLE hTexture = m_pEffectMask->Get()->GetParameterByName(0, "MaskTexture");
				m_pEffectMask->SetTexture("MaskTexture", (m_bActive /*|| SETTINGSHANDLE->GetModel()->Get().bMinimapAlwaysActive) ? m_pcMaskBackgroundActive->GetTexture() : m_pcMaskBackground->GetTexture());
			
				//m_pEffectMask->SetTexture("MaskTexture", m_pcMaskBackground->GetTexture());

				//Render the Render Target and mask it on effect
				UI::ImageRender::Render(m_pRenderTargetMask->GetTexture(), GetMiniMapPostion().iX, GetMiniMapPostion().iY, m_pRenderTargetMask->GetWidth(), m_pRenderTargetMask->GetHeight(), 0, 0, D3DCOLOR_XRGB(255, 255, 255), FALSE);

				m_pEffectMask->End();
			}

			UI::ImageRender::SetEffect(NULL);
		}
	}
	void Title::RenderUser(Point3D sUserAngle)
	{
		int iAngle = ((sUserAngle.iY * 360) / ANGLE_360) + 180;
		UI::ImageRender::Render(m_pcUserPoint, GetMiniMapPostion().iX + (MINIMAP_SIZE >> 1) - 8, GetMiniMapPostion().iY + (MINIMAP_SIZE >> 1) - 8, m_pcUserPoint->GetWidth(), m_pcUserPoint->GetHeight(), 0, 0, -1, 0.7f, (float)iAngle);
	}
	BOOL Title::RenderNPC(smCHAR *pcChar, Point3D sUserPosition, int iSize)
	{
		if (pcChar->smCharInfo.State == smCHAR_STATE_NPC)
		{
			if (pcChar->GetPosition().WithinPTDistance(&sUserPosition, DISTANCE_UNIT_VIEWLIMIT))
			{
				Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, pcChar->GetPosition(), m_pcNPCPoint->GetWidth() >> 1, m_pcNPCPoint->GetHeight() >> 1, iSize);
				Rectangle2D sBox = Rectangle2D(sPosition.iX + GetMiniMapPostion().iX, sPosition.iY + GetMiniMapPostion().iY, m_pcNPCPoint->GetWidth(), m_pcNPCPoint->GetHeight());

				UI::ImageRender::Render(m_pcNPCPoint, sPosition.iX, sPosition.iY, m_pcNPCPoint->GetWidth(), m_pcNPCPoint->GetHeight(), 0, 0, -1);

				if (MOUSEHANDLER->GetPosition()->Inside(sBox))
				{
					m_bIsHover = TRUE;
					m_sHoverUnitBox = sBox;
					m_strHoverUnit = pcChar->smCharInfo.szName;
					m_cHoverColor = UI::Color(255, 255, 255, 255);
				}
			}

			return TRUE;
		}

		return FALSE;
	}
	BOOL Title::RenderPlayer(smCHAR *pcChar, Point3D sUserPosition, int iUserClanID, int iSize)
	{
		if (pcChar->PkMode_CharState == smCHAR_STATE_USER || pcChar->smCharInfo.State == smCHAR_STATE_USER)
		{
			if (pcChar->smCharInfo.ClassClan > 0 && pcChar->smCharInfo.ClassClan == iUserClanID && SETTINGHANDLE->Get().bShowClanMembers)
			{
				if (pcChar->GetPosition().WithinPTDistance(&sUserPosition, DISTANCE_UNIT_VIEWLIMIT))
				{
					Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, pcChar->GetPosition(), m_pcImageFriendlyIcon->GetWidth() >> 1, m_pcImageFriendlyIcon->GetHeight() >> 1, iSize);

					UI::ImageRender::Render(m_pcImageFriendlyIcon, sPosition.iX, sPosition.iY, m_pcImageFriendlyIcon->GetWidth(), m_pcImageFriendlyIcon->GetHeight(), 0, 0, -1);
				}
			}
			else if (pcChar->GetMap() && pcChar->GetMap()->GetID() == MAPID_BlessCastle && SETTINGHANDLE->Get().bShowEnemies)
			{
				//Enemy Clan
				if (pcChar->GetPosition().WithinPTDistance(&sUserPosition, DISTANCE_UNIT_VIEWLIMIT))
				{
					Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, pcChar->GetPosition(), m_pcImageEnemyIcon->GetWidth() >> 1, m_pcImageEnemyIcon->GetHeight() >> 1, iSize);

					UI::ImageRender::Render(m_pcImageEnemyIcon, sPosition.iX, sPosition.iY, m_pcImageEnemyIcon->GetWidth(), m_pcImageEnemyIcon->GetHeight(), 0, 0, -1);
				}
			}

			return TRUE;
		}

		return FALSE;
	}
	void Title::RenderParty(Point3D sUserPosition, int iUserID, int iSize)
	{
		if (InterfaceParty.PartyMemberCount > 0 && SETTINGHANDLE->Get().bShowPartyMembers)
		{
			for (int i = 0; i < InterfaceParty.PartyMemberCount; i++)
			{
				auto sMember = InterfaceParty.PartyMember[i];
				UI::Image * pImage = m_pcaImagesPartyMemberIcon[i];

				if (sMember.Level > 0 && (sMember.ChrCode != iUserID) && pImage)
				{
					Point2D sPosition = GetMinimapPositionFromCenter(sUserPosition, sMember.sPosition, pImage->GetWidth() >> 1, pImage->GetHeight() >> 1, iSize);
					Rectangle2D sBox = Rectangle2D(sPosition.iX + GetMiniMapPostion().iX, sPosition.iY + GetMiniMapPostion().iY, pImage->GetWidth(), pImage->GetHeight());

					UI::ImageRender::Render(pImage, sPosition.iX, sPosition.iY, pImage->GetWidth(), pImage->GetHeight(), 0, 0, -1);

					if (MOUSEHANDLER->GetPosition()->Inside(sBox))
					{
						m_bIsHover = TRUE;
						m_sHoverUnitBox = sBox;
						m_strHoverUnit = sMember.Name;
						m_cHoverColor = UI::Color(255, 175, 230, 175);
					}
				}
			}
		}
	}
	Point2D Title::GetMinimapPositionFromCenter(Point3D sCenterPosition, Point3D sObjectPosition, int iWidthPoint, int iHeightPoint, int iSize)
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
	BOOL Title::IsHave()
	{
		auto pcMap = lpCurPlayer->GetMap();

		return pcMap ? pcMap->IsMiniMap() : FALSE;
	}*/
}