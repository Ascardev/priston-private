#pragma once

namespace DX
{
	class GraphicsDevice;

	typedef std::shared_ptr<class SpriteFactory> LPSPRITEFACTORY;

	class SpriteFactory
	{
	public:
		SpriteFactory(GraphicsDevice *pGraphicsDevice);
		virtual ~SpriteFactory();

		void OnLostDevice();
		void OnResetDevice();

		LPSPRITE MakeSprite(BOOL bSharable);
	protected:
		LPSPRITE FindSprite(BOOL bSharable);
	private:
		GraphicsDevice *m_pGraphicsDevice;
		std::vector<LPSPRITE> m_vSprite;
	};
}