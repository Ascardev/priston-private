#pragma once

namespace DX
{
	typedef std::shared_ptr<class ViewPort> LPVIEWPORT;

	class ViewPort
	{
		friend class GraphicsDevice;

	public:
		ViewPort();
		ViewPort(DWORD dwX,DWORD dwY,DWORD dwWidth,DWORD dwHeight,float fMinZ,float fMaxZ);
		virtual ~ViewPort();
	private:
		DWORD m_dwX;
		DWORD m_dwY;
		DWORD m_dwWidth;
		DWORD m_dwHeight;
		float m_fMinZ;
		float m_fMaxZ;
	};
}