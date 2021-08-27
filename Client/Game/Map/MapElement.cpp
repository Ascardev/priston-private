#include "StdAfx.h"
#include "MapElement.h"

namespace MAP
{
	Element::Element()
	{

	}
	Element::Element(int iX, int iZ) : m_sPosition(Point3D(iX, 0, iZ))
	{

	}
	Element::Element(int iX, int iY, int iZ) : m_sPosition(Point3D(iX, iY, iZ))
	{

	}
	Element::Element(EMapID eID, int iX, int iZ, int iY) : m_eID(eID), m_sPosition(Point3D(iX, iY, iZ))
	{

	}
	Element::~Element()
	{

	}

	ElementSpawn::ElementSpawn() : Element()
	{

	}
	ElementSpawn::ElementSpawn(int iX, int iZ) : Element(iX, iZ)
	{

	}
	ElementSpawn::~ElementSpawn()
	{

	}

	ElementBorder::ElementBorder() : Element()
	{

	}
	ElementBorder::ElementBorder(EMapID eID, int iX, int iZ, int iY) : Element(eID, iX, iZ, iY)
	{

	}
	ElementBorder::~ElementBorder()
	{

	}
	BOOL ElementBorder::InSide(Point3D sPosition)
	{
		int iDist, iX, iY, iZ;

		m_sPosition.GetPTDistanceXZY(&sPosition, iDist, iX, iY, iZ);

		return (iDist < DIST_TRANSLEVEL_CONNECT && iX < 64 * 256 && iZ < 64 * 256) ? TRUE : FALSE;
	}

	ElementWarpGate::ElementWarpGate() : Element()
	{

	}
	ElementWarpGate::ElementWarpGate(EMapID eID, int iX, int iZ, int iY, int iWidth, int iHeight, int iType) : Element(eID, iX, iZ, iY), m_iWidth(iWidth), m_iHeight(iHeight), m_iType(iType)
	{

	}
	ElementWarpGate::~ElementWarpGate()
	{

	}
	void ElementWarpGate::Add(EMapID eID, int iX, int iZ, int iY)
	{
		m_vElement.push_back(Element(eID, iX << 8, iZ << 8, iY << 8));
	}
	Element *ElementWarpGate::Get()
	{
		return m_vElement.size() ? &m_vElement[rand() % m_vElement.size()] : nullptr;
	}
	BOOL ElementWarpGate::InSide(Point3D sPosition)
	{
		int iDist, iX, iY, iZ;

		m_sPosition.GetPTDistanceXZY(&sPosition, iDist, iX, iY, iZ);

		return (iX < 1024 && iZ < 1024 && iDist < m_iWidth * m_iWidth && iY < m_iHeight) ? TRUE : FALSE;
	}

	ElementSound::ElementSound() : Element()
	{

	}
	ElementSound::ElementSound(int iX, int iY, int iZ, int iRound, int iSound) : Element(iX, iY, iZ), m_iRound(iRound), m_iSound(iSound)
	{

	}
	ElementSound::~ElementSound()
	{

	}

	ElementModel::ElementModel()
	{

	}
	ElementModel::ElementModel(const char *pszFileName, BOOL b) : m_strFileName(pszFileName), m_bBip(b)
	{

	}
	ElementModel::~ElementModel()
	{

	}
}