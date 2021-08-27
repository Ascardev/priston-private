#include "StdAfx.h"
#include "DXLogger.h"

namespace DX
{
	Logger::Logger()
	{

	}
	Logger::~Logger()
	{
		m_strLogFile = "save\\logs\\directx.log";
	}
	void Logger::Print(const char *pszFormat)
	{
		SYSTEMTIME time;
		GetLocalTime(&time);

		char szMessage[2048];
		STRINGFORMAT(szMessage, "%02d:%02d:%02d:%03d - %s\r\n", time.wHour, time.wMinute, time.wSecond, time.wMilliseconds, pszFormat);

		FILE * fp;
		if(fopen_s(&fp,m_strLogFile.c_str(), "a") == 0)
		{
			fputs(szMessage,fp);
			fclose(fp);
		}
	}
	const char *Logger::ResultToString(HRESULT hr)
	{
		switch(hr)
		{
			//E
		case E_OUTOFMEMORY:
			return "E_OUTOFMEMORY";
		case E_FAIL:
			return "E_FAIL";

			//D3D
		case D3D_OK:
			return "D3D_OK";
		case D3DERR_DEVICELOST:
			return "D3DERR_DEVICELOST";
		case D3DERR_INVALIDCALL:
			return "D3DERR_INVALIDCALL";
		case D3DERR_NOTAVAILABLE:
			return "D3DERR_NOTAVAILABLE";
		case D3DERR_OUTOFVIDEOMEMORY:
			return "D3DERR_OUTOFVIDEOMEMORY";

			//DSOUND
		case DSERR_ALLOCATED:
			return "DSERR_ALLOCATED";
		case DSERR_INVALIDPARAM:
			return "DSERR_INVALIDPARAM";
		case DSERR_NOAGGREGATION:
			return "DSERR_NOAGGREGATION";
		case DSERR_BADFORMAT:
			return "DSERR_BADFORMAT";
		case DSERR_NODRIVER:
			return "DSERR_NODRIVER";
		case DSERR_UNINITIALIZED:
			return "DSERR_UNINITIALIZED";
		case DSERR_UNSUPPORTED:
			return "DSERR_UNSUPPORTED";

			//D3DX
		case D3DXERR_INVALIDDATA:
			return "D3DXERR_INVALIDDATA";
		}

		return "UNKNOWN";
	}
}