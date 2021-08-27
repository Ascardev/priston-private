#include "StdAfx.h"
#include "UIComboBox.h"

namespace UI
{
	ComboBox::ComboBox(Rectangle2D rRectangle) : Element(rRectangle)
	{
		m_pTextValue = std::make_shared<Text>("", Rectangle2D(0, 0, rRectangle.iWidth - 22, rRectangle.iHeight), FALSE, -1);
		m_pTextValue->SetVerticalAlign(ALIGN_Middle);
		m_pTextValue->SetHorizontalAlign(ALIGN_Center);
	}
	ComboBox::~ComboBox()
	{
		//Clear();
	}
	void ComboBox::Clear()
	{
		CLEARPTR(m_pBackgroundImage);
		CLEARPTR(m_pBackgroundActiveImage);
		CLEARPTR(m_pBackgroundActiveTopImage);
		CLEARPTR(m_pBackgroundActiveMiddleImage);
		CLEARPTR(m_pBackgroundActiveBottomImage);

		UI::ImageLoader::DeleteImage(m_pBackgroundImage);
		UI::ImageLoader::DeleteImage(m_pBackgroundActiveImage);
		UI::ImageLoader::DeleteImage(m_pBackgroundActiveTopImage);
		UI::ImageLoader::DeleteImage(m_pBackgroundActiveMiddleImage);
		UI::ImageLoader::DeleteImage(m_pBackgroundActiveBottomImage);

		m_vTextOptions.clear();
	}
	LPTEXT ComboBox::MakeOption(const std::string &strText,const Rectangle2D &rBox,BOOL bBold,const DWORD dwColor)
	{
		LPTEXT pText = std::make_shared<Text>(strText,rBox,bBold,dwColor);
		pText->SetNoClip(TRUE);

		return pText;
	}
	void ComboBox::AddOption(LPTEXT p)
	{
		p->SetBox(Rectangle2D(p->GetX(),p->GetY() + GetHeight() + (m_vTextOptions.size() * p->GetHeight()),p->GetWidth(),p->GetHeight()));
		p->SetID(m_vTextOptions.size() + 1);
		p->SetHorizontalAlign(ALIGN_Center);
		p->SetVerticalAlign(ALIGN_Middle);

		m_vTextOptions.push_back(p);

		m_iHeightMenu += p->GetHeight();
	}
	void ComboBox::AddOption(LPTEXT p,int iID)
	{
		p->SetBox(Rectangle2D(p->GetX(),p->GetY() + GetHeight() + (m_vTextOptions.size() * p->GetHeight()),p->GetWidth(),p->GetHeight()));
		p->SetID(iID);
		p->SetHorizontalAlign(ALIGN_Center);
		p->SetVerticalAlign(ALIGN_Middle);

		m_vTextOptions.push_back(p);

		m_iHeightMenu += p->GetHeight();
	}
	void ComboBox::SetBackgroundImage(std::pair<class Image *,class Image *> pPair)
	{
		m_pBackgroundImage = pPair.first;
		m_pBackgroundActiveImage = pPair.second;
	}
	void ComboBox::SetBackgroundActiveImage(std::pair<class Image *,class Image *> pPair)
	{
		m_pBackgroundActiveMiddleImage = pPair.first;
		m_pBackgroundActiveBottomImage = pPair.second;
	}
	void ComboBox::Render(int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (IsOpen())
		{
			int iRenderX = GetX() + iX;
			int iRenderY = GetY() + iY;
			int iRenderWidth = low(GetWidth(), iWidth);
			int iRenderHeight = low(GetHeight(), iHeight);

			//Render Background Image
			if (!m_bShowMenu)
			{
				if (m_bHover)
				{
					if (m_pBackgroundActiveImage)
						UI::ImageRender::Render(m_pBackgroundActiveImage, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY,-1);
				}
				else
				{
					if (m_pBackgroundImage)
						UI::ImageRender::Render(m_pBackgroundImage, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);
				}
			}
			else
			{
				if (m_pBackgroundActiveTopImage)
					UI::ImageRender::Render(m_pBackgroundActiveTopImage, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);
				if (m_pBackgroundActiveMiddleImage)
					UI::ImageRender::Render(m_pBackgroundActiveMiddleImage, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);
				if (m_pBackgroundActiveBottomImage)
					UI::ImageRender::Render(m_pBackgroundActiveBottomImage, iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY, -1);
			}

			//Render Value Text
			if (m_pTextValue)
				m_pTextValue->Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);

			//Show Options from Menu
			if (m_bShowMenu)
			{
				LINEHANDLE->MakeLine()->Draw(m_rOptionPosition, m_dwHoverColor);

				for (auto &v : m_vTextOptions)
				{
					v->Render(GetX() + iX, GetY() + iY, iWidth, iHeight, iSourceX, iSourceY);
				}
			}

			Element::Render(iRenderX, iRenderY, iRenderWidth, iRenderHeight, iSourceX, iSourceY);
		}
	}

	std::string ComboBox::GetTextOption(int iIDObject)
	{
		for (UINT u = 0; u < m_vTextOptions.size(); u ++)
		{
			if (m_vTextOptions[u]->GetID() == iIDObject)
				return m_vTextOptions[u]->GetText();
		}

		return "";
	}

	BOOL ComboBox::OnMouseClick(INPUTS::LPMOUSE pcMouse,int iX,int iY,int iWidth,int iHeight,int iSourceX,int iSourceY)
	{
		if (!IsOpen() || IsEnjoin())
			return FALSE;

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(),iWidth);
		int iRenderHeight = low(GetHeight(),iHeight);

		Rectangle2D rBox(iRenderX,iRenderY,iRenderWidth,iRenderHeight);
		Rectangle2D rMenu(iRenderX,iRenderY + iRenderHeight,iRenderWidth,m_iHeightMenu);

		if (pcMouse->GetEvent() == ClickDownL && rBox.Inside(pcMouse->GetPosition()))
		{
			m_bShowMenu = TRUE;
			return TRUE;
		}
		else if (pcMouse->GetEvent() == ClickDownL && m_bShowMenu && rMenu.Inside(pcMouse->GetPosition()))
		{
			if (m_iEventID != -1)
				UI::Event::Invoke(m_iEventID);

			//Update Value
			if (m_pTextValue)
				m_pTextValue->SetText(GetTextOption(m_iSelectID));

			m_bShowMenu = FALSE;
			return TRUE;
		}
		else if (pcMouse->GetEvent() == ClickDownL)
			m_bShowMenu = FALSE;

		return FALSE;
	}
	void ComboBox::OnMouseMove(INPUTS::LPMOUSE pcMouse, int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
	{
		if (!IsOpen() || IsEnjoin())
			return;

		int iRenderX = GetX() + iX;
		int iRenderY = GetY() + iY;
		int iRenderWidth = low(GetWidth(), iWidth);
		int iRenderHeight = low(GetHeight(), iHeight);

		//Show Options from Menu
		if (m_bShowMenu)
		{
			//Set SelectID to default
			m_iSelectID = -1;
			m_rOptionPosition = { 0 , 0 , 0 , 0 };

			for (auto &v : m_vTextOptions)
			{
				Rectangle2D rBox = {iRenderX + v->GetX(),iRenderY + v->GetY(),v->GetWidth(),v->GetHeight()};

				if (rBox.Inside(pcMouse->GetPosition()))
				{
					m_rOptionPosition = rBox;
					m_iSelectID = v->GetID();
				}
			}
		}
		else
		{
			Rectangle2D rBox = { iRenderX,iRenderY,iRenderWidth,iRenderHeight };

			if (rBox.Inside(pcMouse->GetPosition()))
				m_bHover = TRUE;
			else
				m_bHover = FALSE;
		}
	}
}