#pragma once

namespace DX
{
	class GraphicsDevice;

	typedef std::shared_ptr<class TextureFactory>LPTEXTUREFACTORY;

	class TextureFactory
	{
	public:
		TextureFactory(GraphicsDevice *pGraphicsDevice);
		virtual ~TextureFactory();

		void OnLostDevice();
		void OnResetDevice();

		LPTEXTURE FindTexture(const std::string &strFilePath,BOOL bUse3D = FALSE);
		LPTEXTURE MakeTexture(const std::string &strFilePath,BOOL bUse3D = FALSE);
		LPTEXTURE MakeTemporaryTexture(const std::string &strFilePath,BOOL bUse3D = FALSE);
		LPTEXTURE MakeTemporaryTexture(LPDIRECT3DTEXTURE9 lpTexture);
		LPTEXTURE MakeBlankTexutre();

		void ReloadTextures();
		void SetQuality(int iQualityLevel) {m_iQualityLevel = iQualityLevel;}
		LPDIRECT3DTEXTURE9 CreateTextureFromFile(const std::string &strTextureFile,BOOL bUseQualityLevel,BOOL *pbTransparent = NULL);
	protected:
		LPDIRECT3DTEXTURE9 CreateTextureFromFileInMemory(HRESULT &hr,const char * pBuffer,UINT uBufferSize,UINT uMipLevels,D3DCOLOR d3dColorKey, BOOL bUseQualityLevel);
	private:
		GraphicsDevice *m_pGraphicsDevice;
		std::vector<LPTEXTURE> m_vTexture;
		int m_iQualityLevel;
	};
}