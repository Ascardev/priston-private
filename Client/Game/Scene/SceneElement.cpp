#include "StdAfx.h"
#include "SceneElement.h"

namespace SCENE
{
	Element::Element()
	{

	}
	Element::~Element()
	{

	}
	void Element::SetFileName(const char *pszName)
	{
		m_strFileName = pszName;
	}
	void Element::AddStaticModel(const char *pszFileName, BOOL bAnimation)
	{
		m_vModel.push_back(Model(pszFileName, bAnimation));
	}
	void Element::AddModelEx(const char *pszFormat, ...)
	{
		va_list vl;

		char szBuf[256] = { 0 };

		va_start(vl, pszFormat);
		_vsnprintf_s(szBuf, _countof(szBuf), _TRUNCATE, pszFormat, vl);
		va_end(vl);

		m_vModel.push_back(Model(szBuf, FALSE));
	}
	void Element::SetBackgroundMusicID(EBackgroundMusicID eID)
	{
		m_eBackgroundMusicID = eID;
	}
}