#pragma once

namespace MAP
{
	enum EMapElement
	{
		EMAPELEMENT_None,
		EMAPELEMENT_Spawn,
		EMAPELEMENT_Border,
		EMAPELEMENT_WarpGate,
		EMAPELEMENT_Sound,
		EMAPELEMENT_Model,
	};
	class Element
	{
		friend class ElementBorder;
		friend class ElementWarpGate;

	public:
		Element();
		Element(int iX, int iZ);
		Element(int iX, int iY, int iZ);
		Element(EMapID eID, int iX, int iZ, int iY);
		virtual ~Element();

		void Set(EMapElement e) { m_eElement = e; }
	private:
		EMapID m_eID = MAPID_Invalid;
		Point3D m_sPosition;
		EMapElement m_eElement = EMAPELEMENT_None;
	};
	class ElementSpawn : public Element 
	{
	public:
		ElementSpawn();
		ElementSpawn(int iX, int iZ);
		virtual ~ElementSpawn();
	};
	class ElementBorder : public Element
	{
	public:
		ElementBorder();
		ElementBorder(EMapID eID, int iX, int iZ, int iY = 0);
		virtual ~ElementBorder();

		BOOL InSide(Point3D sPosition);
	};
	class ElementWarpGate : public Element
	{
	public:
		ElementWarpGate();
		ElementWarpGate(EMapID eID, int iX, int iZ, int iY, int iWidth, int iHeight, int iType);
		virtual ~ElementWarpGate();

		void Add(EMapID eID, int iX, int iZ, int iY);
		Element *Get();
		BOOL InSide(Point3D sPosition);
	private:
		int m_iWidth = 0;
		int m_iHeight = 0;
		int m_iType = 0;
		std::vector<Element> m_vElement;
	};
	class ElementSound : public Element
	{
	public:
		ElementSound();
		ElementSound(int iX, int iY, int iZ, int iRound, int iSound);
		virtual ~ElementSound();
	private:
		int m_iRound = 0;
		int m_iSound = 0;
	};
	class ElementModel : public Element
	{
	public:
		ElementModel();
		ElementModel(const char *pszFileName, BOOL b);
		virtual ~ElementModel();
	private:
		std::string m_strFileName;
		BOOL m_bBip;
	};
}