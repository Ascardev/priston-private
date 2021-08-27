#pragma once

namespace DX
{
	typedef std::shared_ptr<class FontFactory> LPFONTFACTORY;

	class FontFactory
	{
	public:
		FontFactory(GraphicsDevice *pGraphicsDevice);
		virtual ~FontFactory();

		LPFONT MakeFont(const char *pszName,int iHeight,int iWidth,BOOL bItalic,BOOL bBold);
		LPFONT FindFont(int iObject);
		void OnLostDevice();
		void OnResetDevice();
	protected:
		LPFONT FindFont(const char *pszName, int iHeight, int iWidth, BOOL bItalic, BOOL bBold);
		LPD3DXFONT CreateFont(std::string strName,int iHeight,int iWidth,BOOL bItalic,BOOL bBold);
	private:
		GraphicsDevice *m_pGraphicsDevice;
		std::vector<LPFONT> m_vpFont;
	};
}