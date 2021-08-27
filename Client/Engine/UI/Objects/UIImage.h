#pragma once

namespace UI
{
	typedef class Image *LPIMAGE;

	class Image
	{
	public:
		Image();
		virtual ~Image();

		void AddRef() {m_uRef ++;}
		UINT GetRef() {return m_uRef;}
		void DecRef() {m_uRef --;}

		void Clear() {}

		void SetID(int iID,LPDIRECT3DTEXTURE9 lpTexture) {m_iID = iID; m_pTexture = lpTexture;}
		void SetFile(std::string &strFileName) {m_strFileName = strFileName; m_uSum = CalSpeedSum(m_strFileName.c_str());}

		void SetWidth(int iWidth) {m_iWidth = iWidth;}
		void SetHeight(int iHeight) {m_iHeight = iHeight;}

		void SetFormat(UINT uFormat) {m_uFormat = uFormat;}

		void SetTexture(LPDIRECT3DTEXTURE9 h) {m_pTexture = h;}

		int GetID() {return m_iID;}

		int GetWidth() {return m_iWidth;}
		int GetHeight() {return m_iHeight;}

		UINT GetFormat() {return m_uFormat;}

		std::string GetFileName() {return m_strFileName;}

		UINT GetFileSum() {return m_uSum;}

		LPDIRECT3DTEXTURE9 GetTexture() {return m_pTexture;}

		LPIMAGE GetPointer() {return this;}

	protected:
		int m_iID;
		UINT m_uRef = 0;
		LPDIRECT3DTEXTURE9 m_pTexture;
		std::string m_strFileName;
		int m_iWidth;
		int m_iHeight;
		UINT m_uFormat;
		UINT m_uSum = 0;
	};
}