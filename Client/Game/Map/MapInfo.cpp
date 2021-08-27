#include "StdAfx.h"
#include "MapInfo.h"

namespace MAP
{
	Info::Info()
	{

	}
	Info::Info(EMapID eID, const char *pszName) : m_eID(eID), m_strName(pszName)
	{
		m_iLevel = GetMapLevel(eID);
	}
	Info::~Info()
	{
		for (auto &v : m_vpElements)
		{
			DELET(v);
		}

		m_vpElements.clear();
	}
	void Info::AddSpawn(int iX, int iZ)
	{
		auto pElement = new ElementSpawn(iX << 8, iZ << 8);
		pElement->Set(EMAPELEMENT_Spawn);

		m_vpElements.push_back(pElement);
	}
	void Info::AddBorder(EMapID eID, int iX, int iZ)
	{
		auto pElement = new ElementBorder(eID, iX << 8, iZ << 8);
		pElement->Set(EMAPELEMENT_Border);

		m_vpElements.push_back(pElement);
	}
	ElementWarpGate *Info::AddWarpGate(int iX, int iZ, int iY, int iWidth, int iHeight, int iType)
	{
		auto pElement = new ElementWarpGate(m_eID, iX << 8, iZ << 8, iY << 8, iWidth, iHeight, iType);
		pElement->Set(EMAPELEMENT_WarpGate);

		m_vpElements.push_back(pElement);

		return pElement;
	}
	void Info::AddSound(int iX, int iY, int iZ, int iRound, int iSound)
	{
		auto pElement = new ElementSound(iX << 8, iY << 8, iZ << 8, iRound, iSound);
		pElement->Set(EMAPELEMENT_Sound);

		m_vpElements.push_back(pElement);
	}
	void Info::AddStaticModel(const char *pszName, BOOL bBip)
	{
		auto pElement = new ElementModel(pszName, bBip);
		pElement->Set(EMAPELEMENT_Model);

		m_vpElements.push_back(pElement);
	}
	void Info::AddModelEx(const char *pszFormat, ...)
	{
		va_list vl;

		char szBuf[256] = { 0 };

		va_start(vl, pszFormat);
		_vsnprintf_s(szBuf, _countof(szBuf), _TRUNCATE, pszFormat, vl);
		va_end(vl);

		//AddModel(szBuf, FALSE);
	}
}