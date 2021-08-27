#pragma once

namespace DX
{
	typedef std::shared_ptr<class Logger> LPLOGGER;

	class Logger
	{
	public:
		Logger();
		virtual ~Logger();
		void Print(const char *pszFormat);
		const char *ResultToString(HRESULT hr);
	private:
		std::string m_strLogFile;
	};
}