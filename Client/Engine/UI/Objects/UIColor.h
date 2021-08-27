#pragma once

namespace UI
{
	class Color
	{
	public:
		Color() {d3dColor = D3DCOLOR_ARGB(255,255,255,255);}
		Color(D3DCOLOR c) {d3dColor = c;}
		Color(int a,int r,int g,int b) {d3dColor = D3DCOLOR_ARGB(a,r,g,b);}
		Color(const Color &c) {d3dColor = c.d3dColor;}

		D3DCOLOR Get() const { return d3dColor; }
		int GetAlpha() const { return a; }
		void SetAlpha(int i) { i > 255 ? a = 255 : a = i; }
	protected:
		union
		{
			struct
			{
				BYTE a,r,g,b;
			};
			D3DCOLOR d3dColor;
		};
	};
}