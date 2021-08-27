#include "StdAfx.h"
#include "DXTextureFactory.h"

namespace DX
{
	TextureFactory::TextureFactory(GraphicsDevice *pGraphicsDevice) : m_pGraphicsDevice(pGraphicsDevice),m_iQualityLevel(0)
	{
		m_vTexture.reserve(1000);
	}
	TextureFactory::~TextureFactory()
	{
		
	}
	void TextureFactory::OnLostDevice()
	{

	}
	void TextureFactory::OnResetDevice()
	{

	}
	LPTEXTURE TextureFactory::FindTexture(const std::string &strFilePath,BOOL bUse3D)
	{
		for (auto pTexture : m_vTexture)
		{
			if (pTexture)
			{
				// Not same Use 3D and Not same File
				if (STRINGCOMPAREI(strFilePath.c_str(), pTexture->GetFile().c_str()) &&
					pTexture->GetUse3D() == bUse3D)
				{
					return pTexture;
				}
			}
		}

		return NULL;
	}
	LPTEXTURE TextureFactory::MakeTexture(const std::string &strFilePath,BOOL bUse3D)
	{
		auto pTexture = FindTexture(strFilePath,bUse3D);

		if (!pTexture)
			pTexture = MakeTemporaryTexture(strFilePath,bUse3D);

		return pTexture;
	}
	LPTEXTURE TextureFactory::MakeTemporaryTexture(const std::string &strFilePath,BOOL bUse3D)
	{
		// Make New Texture
		BOOL bTransparent = FALSE;
		LPDIRECT3DTEXTURE9 lpTexture = CreateTextureFromFile(strFilePath,bUse3D,&bTransparent);

		//New Texture (Adds Reference)
		auto pTexture = std::make_shared<Texture>(lpTexture,strFilePath,bUse3D);

		//Set Texture Transparent setting
		pTexture->SetTransparent(bTransparent);

		//Release our Reference
		RELEASE(lpTexture);

		//Cache New Texture
		m_vTexture.push_back(pTexture);

		return pTexture;
	}
	LPTEXTURE TextureFactory::MakeTemporaryTexture(LPDIRECT3DTEXTURE9 lpTexture)
	{
		return std::make_shared<Texture>(lpTexture);
	}
	LPTEXTURE TextureFactory::MakeBlankTexutre()
	{
		//new Blank Texture
		return MakeTexture("Resources\\Texture\\misc\\White.bmp");
	}
	void TextureFactory::ReloadTextures()
	{
		//Loop through Textures in Cache
		for (auto pTexture : m_vTexture)
		{
			if (pTexture)
			{
				//Create Texture
				auto lpTexture = CreateTextureFromFile(pTexture->GetFile(), pTexture->GetUse3D());

				//Renew Texture (adds Reference)
				pTexture->Renew(lpTexture);
				//Release our Reference
				RELEASE(lpTexture);
			}
		}
	}
	LPDIRECT3DTEXTURE9 TextureFactory::CreateTextureFromFile(const std::string &strTextureFile,BOOL bUseQualityLevel,BOOL *pbTransparent)
	{
		LPDIRECT3DTEXTURE9 lpTexture = NULL;
		HRESULT hr = 0;

		// Load Texture from File
		CFILE::LPBIN cpFile = new CFILE::Bin;

		if (cpFile && cpFile->Open(strTextureFile.c_str(),BIN_READ))
		{
			// Get File Size
			UINT uFileSize = cpFile->GetSize();

			//Emptry File Size
			if (uFileSize <= 0)
			{
				DELET(cpFile);
				return NULL;
			}

			//Create Buffer for File contents
			char *pBuffer = new char[uFileSize];
			//Read File into Buffer
			cpFile->Read(pBuffer,uFileSize);

			DELET(cpFile);

			//Get MipMap Count
			UINT uMipLevels = 0;

			if (bUseQualityLevel)
				uMipLevels = GetFileLevel(strTextureFile);

			//Get File Extension
			std::string strFileExtension = GetFileExtension(strTextureFile);

			if ((pBuffer[0] == 'B') && (pBuffer[1] == 'M'))
				strFileExtension = "bmp";

			//Load BMP
			if (strFileExtension.compare("bmp") == 0)
			{
				if (pbTransparent)
					*pbTransparent = FALSE;

				if (DecryptBMP(pBuffer,uFileSize))
					lpTexture = CreateTextureFromFileInMemory(hr,pBuffer,uFileSize,uMipLevels == 0 ? D3DX_FROM_FILE : uMipLevels + 1,bUseQualityLevel ? D3DCOLOR_ARGB(0,0,0,0) : D3DCOLOR_ARGB(255,0,0,0),bUseQualityLevel);
			}
			else if (strFileExtension.compare("jpg") == 0)
			{
				if (pbTransparent)
					*pbTransparent = FALSE;

				lpTexture = CreateTextureFromFileInMemory(hr,pBuffer,uFileSize,uMipLevels == 0 ? D3DX_FROM_FILE : uMipLevels + 1,bUseQualityLevel ? D3DCOLOR_ARGB(0,0,0,0) : D3DCOLOR_ARGB(255,0,0,0),bUseQualityLevel);
			}
			else if (strFileExtension.compare("tga") == 0)
			{
				if (pbTransparent)
					*pbTransparent = TRUE;

				if (DecryptTGA(pBuffer,uFileSize))
					lpTexture = CreateTextureFromFileInMemory(hr,pBuffer,uFileSize,uMipLevels == 0 ? D3DX_FROM_FILE : uMipLevels + 1,D3DCOLOR_ARGB(0,0,0,0),bUseQualityLevel);
			}
			else if (strFileExtension.compare("png") == 0)
			{
				if (pbTransparent)
					*pbTransparent = TRUE;

				lpTexture = CreateTextureFromFileInMemory(hr,pBuffer,uFileSize,uMipLevels == 0 ? D3DX_FROM_FILE : uMipLevels + 1,D3DCOLOR_ARGB(0,0,0,0),bUseQualityLevel);
			}

			DELETA(pBuffer);
		}

		return lpTexture;
	}
	LPDIRECT3DTEXTURE9 TextureFactory::CreateTextureFromFileInMemory(HRESULT &hr,const char * pBuffer,UINT uBufferSize,UINT uMipLevels,D3DCOLOR d3dColorKey, BOOL bUseQualityLevel)
	{
		UINT uWidth = D3DX_DEFAULT_NONPOW2;
		UINT uHeight= D3DX_DEFAULT_NONPOW2;

		D3DXIMAGE_INFO ii;

		ZeroMemory(&ii,sizeof(D3DXIMAGE_INFO));

		//Reduce Texture Dimension if necessary
		if ((bUseQualityLevel) && (m_iQualityLevel > 0))
		{
			if (FAILED(hr = D3DXGetImageInfoFromFileInMemory(pBuffer,uBufferSize,&ii)))
				return NULL;

			uWidth = ii.Width >> m_iQualityLevel;
			uHeight = ii.Height >> m_iQualityLevel;
		}

		LPDIRECT3DTEXTURE9 lpTexture = NULL;

		if (FAILED(hr = D3DXCreateTextureFromFileInMemoryEx(m_pGraphicsDevice->Get(),pBuffer,uBufferSize,uWidth,uHeight,uMipLevels,0,D3DFMT_FROM_FILE,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,d3dColorKey,&ii,NULL,&lpTexture)))
			return NULL;

		return lpTexture;
	}
}