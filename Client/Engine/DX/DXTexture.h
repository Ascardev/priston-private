#pragma once

namespace DX
{
	typedef std::shared_ptr<class Texture> LPTEXTURE;

	class Texture
	{
	public:
		Texture(LPDIRECT3DTEXTURE9 lpTexture);
		Texture(LPDIRECT3DTEXTURE9 lpTexture,BOOL bUse3D);
		Texture(LPDIRECT3DTEXTURE9 lpTexture,std::string strTextureFile,BOOL bUse3D);
		virtual ~Texture();

		LPDIRECT3DTEXTURE9 Get() {return m_pTexture;}
		const std::string &GetFile() const {return m_strTextureFile;}
		BOOL GetUse3D() const {return m_bUse3D;}
		void Renew(LPDIRECT3DTEXTURE9 lpTexture);
		void SetTransparent(BOOL b) {m_bIsTransparent = b;}
		BOOL GetTransparent() {return m_bIsTransparent;}

		UINT GetWidth();
		UINT GetHeight();
	protected:
		void LoadDescription();
	private:
		LPDIRECT3DTEXTURE9 m_pTexture;
		std::string m_strTextureFile;
		BOOL m_bUse3D = FALSE;
		BOOL m_bIsTransparent = FALSE;
		D3DSURFACE_DESC m_d3dSurfaceDesc;
	};
}