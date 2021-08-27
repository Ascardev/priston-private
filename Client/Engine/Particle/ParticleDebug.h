#pragma once

namespace PARTICLE
{
	class Debug
	{
	public:
		Debug();
		virtual ~Debug();

		void Render();

		BOOL GetDisplay() { return m_bDisplay; }
		void SetDisplay(BOOL b) { m_bDisplay = b; }
	protected:
		BOOL m_bDisplay = FALSE;
	};
}
