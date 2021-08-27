#pragma once

namespace CHARACTER
{
	class Window
	{
	public:
		void Init();
		void Shutdown();

		void Render();
		void Update(float fTime);
	};
}
