#include "StdAfx.h"
#include "DXTexture.h"

namespace DX
{
	Texture::Texture(LPDIRECT3DTEXTURE9 lpTexture) : m_pTexture(lpTexture)
	{
		ADDREF(m_pTexture);
		LoadDescription();
	}
	Texture::Texture(LPDIRECT3DTEXTURE9 lpTexture,BOOL bUse3D) : m_pTexture(lpTexture)
	{
		ADDREF(m_pTexture);
		LoadDescription();
	}
	Texture::Texture(LPDIRECT3DTEXTURE9 lpTexture,std::string strTextureFile,BOOL bUse3D) : m_pTexture(lpTexture),m_strTextureFile(strTextureFile),m_bUse3D(bUse3D),m_bIsTransparent(FALSE)
	{
		ADDREF(m_pTexture);
		LoadDescription();
	}
	Texture::~Texture()
	{
		RELEASE(m_pTexture);
	}
	void Texture::Renew(LPDIRECT3DTEXTURE9 lpTexture)
	{
		RELEASE(m_pTexture);
		m_pTexture = lpTexture;

		ADDREF(m_pTexture);
		LoadDescription();
	}
	UINT Texture::GetWidth()
	{
		if (!m_pTexture)
			return 0;

		return m_d3dSurfaceDesc.Width;
	}
	UINT Texture::GetHeight()
	{
		if (!m_pTexture)
			return 0;

		return m_d3dSurfaceDesc.Height;
	}
	void Texture::LoadDescription()
	{
		if (m_pTexture)
			m_pTexture->GetLevelDesc(0,&m_d3dSurfaceDesc);
	}
}