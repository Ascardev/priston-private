#pragma once

namespace CINFO
{
	typedef class ProcessEx *LPPROCESSEX;

	class ProcessEx
	{
	public:
		ProcessEx();
		virtual ~ProcessEx();
		void SetInstanceHandle(HINSTANCE _hInstance){m_hInstance = _hInstance;}
		HINSTANCE GetInstanceHandle() {return m_hInstance;}
		void ForceExit(UINT uExitCode = 0);
	protected:
		HINSTANCE m_hInstance;
	};
}