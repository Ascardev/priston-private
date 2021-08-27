#pragma once

namespace MAP
{
	namespace MINI
	{
		class Window : public CBaseWindow
		{
		public:
			Window();
			Window(EWindow eID);
			virtual ~Window();

			void Init();
			void Shutdown();
		};
	}
}
