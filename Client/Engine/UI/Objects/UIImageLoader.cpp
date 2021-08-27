#include "StdAfx.h"
#include "UIImageLoader.h"

std::vector<UI::Image *> vImageResource;

namespace UI
{
	ImageLoader::ImageLoader()
	{

	}
	ImageLoader::~ImageLoader()
	{

	}
	void ImageLoader::SetScale(class Image *pImage,int iW,int iH,D3DXVECTOR2 *pVector)
	{
		if (pImage->GetWidth() > iW)
			pVector->x = (float)pImage->GetWidth() / (float)iW;
		else
			pVector->x = (float)iW / (float)pImage->GetWidth();

		if (pImage->GetHeight() > iH)
			pVector->y = (float)pImage->GetHeight() / (float)iH;
		else
			pVector->y = (float)iH / (float)pImage->GetHeight();
	}
	UI::Image *ImageLoader::LoadImage_(const char *pszFile,...)
	{
		char szBuffer[1024];

		STRINGEMPTY(szBuffer);

		va_list ap;
		va_start(ap,pszFile);
		_vsnprintf_s(szBuffer,1024,1023,pszFile,ap);
		va_end(ap);

		return LoadImageBase(szBuffer);
	}
	std::pair<class Image *, class Image *> ImageLoader::LoadActiveImage(char *pszFile1, char *pszFile2)
	{
		Image *f = ImageLoader::LoadImage_(pszFile1);
		Image *s = ImageLoader::LoadImage_(pszFile2);

		return std::pair<class Image *, class Image *>(f, s);
	}
	UI::Image *ImageLoader::LoadImageBase(std::string strFile)
	{
		//Get the size of string

		int iStrNameSize = strFile.length();
		if (iStrNameSize <= 4)
			return nullptr;

		for (UINT u = 0; u < vImageResource.size(); u ++)
		{
			auto pImage = vImageResource.at(u);
			
			if (pImage->GetFileSum() == CalSpeedSum(strFile.c_str()))
			{
				pImage->AddRef();
				return pImage;
			}
		}

		D3DXIMAGE_INFO ii;

		UI::Image *pImage = new UI::Image;

		//Use a magenta colorkey
		D3DCOLOR colorkey = 0xFFFF00FF;

		//OPEN File Memory;
		CFILE::Bin cFile;

		if (cFile.Open(strFile,BIN_READ))
		{
			UINT uFileSize = cFile.GetSize();

			if (uFileSize <= 0)
			{
				cFile.Close();
				return nullptr;
			}

			//Buffer Read
			char *pBuffer = new char[uFileSize];

			cFile.Read(pBuffer,uFileSize);
			cFile.Close();

			std::string strFileExtension = GetFileExtension(strFile);

			if (strFileExtension.compare("bmp") == 0)
			{
				if (!DecryptBMP(pBuffer,uFileSize))
				{
					DELETA(pBuffer);
					return nullptr;
				}
			}
			else if (strFileExtension.compare("tga") == 0)
			{
				if (!DecryptTGA(pBuffer,uFileSize))
				{
					DELETA(pBuffer);
					return nullptr;
				}
			}

			D3DXGetImageInfoFromFileInMemory(pBuffer,uFileSize,&ii);

			if (ii.ImageFileFormat == D3DXIFF_BMP)
				colorkey = 0xFF000000;

			LPDIRECT3DTEXTURE9 lpTexture;

			// Load Image from file
			if (FAILED(D3DXCreateTextureFromFileInMemoryEx(GRAPHICENGINE->GetDevice(),pBuffer,uFileSize,ii.Width,ii.Height,1,0,(D3DFORMAT)D3DX_FROM_FILE,D3DPOOL_MANAGED,D3DX_DEFAULT,D3DX_DEFAULT,ii.ImageFileFormat == D3DXIFF_BMP ? D3DCOLOR_ARGB(255,0,0,0) : 0, &ii,NULL,&lpTexture)))
			{
				WRITEDBG("Could not Find file from %s",strFile.c_str());
			}

			DELETA(pBuffer);

			pImage->SetWidth(ii.Width);
			pImage->SetHeight(ii.Height);
			pImage->SetFormat(ii.ImageFileFormat);
			pImage->SetFile(strFile);
			pImage->SetID(vImageResource.size(),lpTexture);

			vImageResource.push_back(pImage);

			pImage->AddRef();

			return pImage;
		}

		return nullptr;
	}
	void ImageLoader::DeleteImage(Image *ptr)
	{
		if (ptr)
		{
			ptr->DecRef();

			if (ptr->GetRef() <= 0)
			{
				for (std::vector<UI::Image *>::iterator it = vImageResource.begin(); it != vImageResource.end(); it ++)
				{
					auto pc = *it;

					if (pc == ptr)
					{
						auto lpTexture = pc->GetTexture();

						RELEASE(lpTexture);
						DELET(pc);

						it = vImageResource.erase(it);
						break;
					}
				}
			}
		}
	}
}