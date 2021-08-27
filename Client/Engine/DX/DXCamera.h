#pragma once

namespace DX
{
	typedef std::shared_ptr<class Camera>LPCAMERA;

	class Camera
	{
	public:
		Camera(GraphicsDevice *pGraphicsDevice);
		virtual ~Camera(){}

		void Update(double fTime);

		void SetViewMatrix(const D3DXMATRIX &mat) {m_matView = mat;}
		D3DXMATRIX GetViewMatrix(){return m_matView;}
	private:
		D3DXMATRIX m_matView;
		GraphicsDevice *m_pGraphicsDevice;
	};
}