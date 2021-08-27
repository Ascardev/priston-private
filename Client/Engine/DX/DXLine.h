#pragma once

namespace DX
{
	typedef std::shared_ptr<class Line> LPLINE;

	class Line
	{
	public:
		Line(LPD3DXLINE hLine);
		virtual ~Line();

		void OnLostDevice();
		void OnResetDevice();

		void Draw(Rectangle2D rRect,DWORD dwColor);
	private:
		LPD3DXLINE m_pLine = NULL;
	};
}