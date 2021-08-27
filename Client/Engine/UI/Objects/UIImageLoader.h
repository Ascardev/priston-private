#pragma once

namespace UI
{
	class ImageLoader
	{
	public:
		ImageLoader();
		virtual ~ImageLoader();

		static void SetScale(class Image *pImage,int iW,int iH,D3DXVECTOR2 *pVector);
		static class Image * LoadImage_(const char *pszFile,...);
		static std::pair<class Image *, class Image *> LoadActiveImage(char *pszFile1, char *pszFile2);
		static void DeleteImage(Image *ptr);
	protected:
		static class Image *LoadImageBase(std::string strFile);
	};
}