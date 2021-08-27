#include "StdAfx.h"
#include "ObjectOwner.h"

namespace ENGINE
{
	/*ObjectOwner::ObjectOwner()
	{
		m_eType = OBJECTOWNERTYPE_None;
	}
	ObjectOwner::ObjectOwner(ObjectOwner &c)
	{
		m_eType = c.m_eType;
		m_cPosition.x = c.m_cPosition.x;
		m_cPosition.y = c.m_cPosition.y;
		m_cPosition.z = c.m_cPosition.z;
	}
	ObjectOwner::~ObjectOwner()
	{

	}

	ObjectOwnerUnit::ObjectOwnerUnit(smCHAR *_pcUnit) : ObjectOwner()
	{
		m_eType = OBJECTOWNERTYPE_Unit;
		m_IID = _pcUnit->m_iID;
		m_pcUnit = _pcUnit;
	}
	ObjectOwnerUnit::ObjectOwnerUnit(ObjectOwnerUnit & c)
	{
		m_eType = c.m_eType;

		m_IID = c.m_IID;
		m_pcUnit = c.m_pcUnit;

		for (vector<EAnimationType>::iterator it = c.m_vAnimationTypeLostConditions.begin(); it != c.m_vAnimationTypeLostConditions.end(); it++)
		{
			EAnimationType eAnimationType = *it;

			m_vAnimationTypeLostConditions.push_back(eAnimationType);
		}
	}

	ObjectOwnerUnit::~ObjectOwnerUnit()
	{
		m_pcUnit = NULL;
	}

	ObjectOwnerUnit * ObjectOwnerUnit::Clone()
	{
		ObjectOwnerUnit * pClone = new ObjectOwnerUnit(*this);

		return pClone;
	}
	void ObjectOwnerUnit::Update()
	{
		Point3D & p = m_pcUnit->GetPosition();

		m_cPosition.x = p.iX;
		m_cPosition.y = p.iY;
		m_cPosition.z = p.iZ;
	}
	BOOL ObjectOwnerUnit::Lost(DWORD dwTickcount)
	{
		if (m_pcUnit == NULL)
			return TRUE;

		if (m_pcUnit->m_iID != m_IID)
			return TRUE;

		if (m_pcUnit->bActive == FALSE)
			return TRUE;

		if (m_pcUnit != lpCurPlayer && (m_pcUnit->m_dwLastActiveTime + 10000) < dwTickcount)
			return TRUE;

		if (m_pcUnit->MotionInfo == NULL)
			return TRUE;

		for (vector<EAnimationType>::iterator it = m_vAnimationTypeLostConditions.begin(); it != m_vAnimationTypeLostConditions.end(); it++)
		{
			EAnimationType eAnimationType = *it;

			if (m_pcUnit->MotionInfo->State == eAnimationType)
				return TRUE;
		}

		return FALSE;
	}
	ID ObjectOwnerUnit::GetUnitID()
	{
		return m_pcUnit ? m_pcUnit->m_iID : 0;
	}

	ObjectOwnerPosition::ObjectOwnerPosition(Point3D s)
	{
		m_cPosition.x = s.iX; m_cPosition.y = s.iY; m_cPosition.z = s.iZ; m_eType = OBJECTOWNERTYPE_None;
	}

	ObjectOwnerPosition::ObjectOwnerPosition(ObjectOwnerPosition & c)
	{
		m_eType = c.m_eType;
		m_cPosition.x = c.m_cPosition.x;
		m_cPosition.y = c.m_cPosition.y;
		m_cPosition.z = c.m_cPosition.z;
	}
	ObjectOwnerPosition::~ObjectOwnerPosition()
	{
	}

	ObjectOwnerPosition * ObjectOwnerPosition::Clone()
	{
		ObjectOwnerPosition * pClone = new ObjectOwnerPosition(*this);

		return pClone;
	}

	void ObjectOwnerPosition::Update()
	{

	}
	ObjectOwnerProjectile::ObjectOwnerProjectile(smCHAR * _pcUnit) : ObjectOwner()
	{
		m_eType = OBJECTOWNERTYPE_Projectile;

		m_IID = _pcUnit->m_iID;
		m_pcUnit = _pcUnit;
	}
	ObjectOwnerProjectile::ObjectOwnerProjectile(ObjectOwnerProjectile & c)
	{
		m_eType = c.m_eType;

		m_IID = c.m_IID;
		m_pcUnit = c.m_pcUnit;
	}
	ObjectOwnerProjectile::~ObjectOwnerProjectile()
	{
		m_pcUnit = NULL;
	}
	ObjectOwnerProjectile * ObjectOwnerProjectile::Clone()
	{
		ObjectOwnerProjectile * pClone = new ObjectOwnerProjectile(*this);

		return pClone;
	}
	void ObjectOwnerProjectile::Update()
	{
		Point3D & p = m_pcUnit->GetPosition();

		m_cPosition.x = p.iX;
		m_cPosition.y = p.iY;
		m_cPosition.z = p.iZ;
	}
	BOOL ObjectOwnerProjectile::Lost(DWORD dwTickcount)
	{
		if (m_pcUnit == NULL)
			return TRUE;

		if (m_pcUnit->m_iID != m_IID)
			return TRUE;

		if (m_pcUnit->bActive == FALSE)
			return TRUE;

		if (m_pcUnit->MotionInfo == NULL)
			return TRUE;

		return FALSE;
	}*/
}