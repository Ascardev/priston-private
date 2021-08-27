#pragma once

namespace DX
{
	class Render : public std::enable_shared_from_this<Render>
	{
	public:
		Render(LPGRAPHICSDEVICE pGraphicsDevice);
		virtual ~Render();
		LPGRAPHICSDEVICE GetGraphicsDevice() {return m_pGraphicsDevice;}
	private:
		LPGRAPHICSDEVICE m_pGraphicsDevice;
	};
}