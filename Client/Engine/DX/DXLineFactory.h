#pragma once

namespace DX
{
	typedef std::shared_ptr<class LineFactory> LPLINEFACTORY;

	class LineFactory
	{
	public:
		LineFactory(GraphicsDevice *pGraphicsDevice);
		virtual ~LineFactory();

		void OnLostDevice();
		void OnResetDevice();

		LPLINE FindLine();
		LPLINE MakeLine();
	private:
		std::vector<LPLINE> m_vpLine;
		GraphicsDevice *m_pGraphicsDevice;
	};
}