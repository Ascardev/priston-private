#include "StdAfx.h"
#include "DXFontFactory.h"

namespace DX
{
	FontFactory::FontFactory(GraphicsDevice *pGraphicsDevice) : m_pGraphicsDevice(pGraphicsDevice)
	{
		AddFontResourceExA("Resources\\fonts\\Frutiger.ttf", FR_PRIVATE, NULL);
		AddFontResourceExA("Resources\\fonts\\NotoSans-Regular.ttf", FR_PRIVATE, NULL);
	}
	FontFactory::~FontFactory()
	{
		RemoveFontResourceExA("Resources\\fonts\\Frutiger.ttf", FR_PRIVATE, NULL);
		RemoveFontResourceExA("Resources\\fonts\\NotoSans-Regular.ttf", FR_PRIVATE, NULL);
	}
	LPFONT FontFactory::MakeFont(const char *pszName,int iHeight,int iWidth,BOOL bItalic,BOOL bBold)
	{
		auto pFont = FindFont(pszName,iHeight,iWidth,bItalic,bBold);

		if (pFont)
			return pFont;

		auto lpFont = CreateFont(pszName,iHeight,iWidth,bItalic,bBold);

		pFont = std::make_shared<Font>(lpFont);

		RELEASE(lpFont);

		m_vpFont.push_back(pFont);

		return pFont;
	}
	LPFONT FontFactory::FindFont(const char *pszName,int iHeight,int iWidth,BOOL bItalic,BOOL bBold)
	{
		for (auto pFont : m_vpFont)
		{
			if (pFont)
			{
				D3DXFONT_DESCA Desc = pFont->GetFontDesc();

				if (STRINGCOMPARE(Desc.FaceName, pszName))
				{
					if (Desc.Width == iWidth && Desc.Height == iHeight && Desc.Italic == bItalic && bBold == (Desc.Weight == FW_BOLD ? TRUE : FALSE))
						return pFont;
				}
			}
		}

		return NULL;
	}
	LPFONT FontFactory::FindFont(int iObject)
	{
		if (iObject >= 0 && (UINT)iObject < m_vpFont.size())
			return m_vpFont[iObject];

		return nullptr;
	}

	void FontFactory::OnLostDevice()
	{
		for (auto pFont : m_vpFont)
		{
			if (pFont)
				pFont->OnLostDevice();
		}
	}
	void FontFactory::OnResetDevice()
	{
		for (auto pFont : m_vpFont)
		{
			if (pFont)
				pFont->OnResetDevice();
		}
	}
	LPD3DXFONT FontFactory::CreateFont(std::string strName,int iHeight,int iWidth,BOOL bItalic,BOOL bBold)
	{
		UINT uWeight = FW_NORMAL;

		if (bBold)
			uWeight = FW_BOLD;

		// Create the dx Font
		D3DXFONT_DESCA desc;

		desc.Height = iHeight;
		desc.Width	= iWidth;
		desc.Weight	= uWeight;
		desc.MipLevels = D3DX_DEFAULT;
		desc.Italic = bItalic;
		desc.CharSet = DEFAULT_CHARSET;
		desc.OutputPrecision = OUT_DEFAULT_PRECIS;
		desc.Quality = CLEARTYPE_QUALITY;
		desc.PitchAndFamily = DEFAULT_PITCH|FF_DONTCARE;
		STRINGCOPY(desc.FaceName,strName.c_str());

		LPD3DXFONT hFont = NULL;

		if (FAILED(D3DXCreateFontIndirectA(m_pGraphicsDevice->Get(),&desc,&hFont)))
			WRITEDBG("Create Font faild");

		return hFont;
	}
}