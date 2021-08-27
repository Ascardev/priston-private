#pragma once

class smCHAR;

namespace ENGINE
{
	enum EObjectOwnerType
	{
		OBJECTOWNERTYPE_None,
		OBJECTOWNERTYPE_Unit,
		OBJECTOWNERTYPE_Projectile,
	};
	class ObjectOwner
	{
	public:
		ObjectOwner();
		ObjectOwner(ObjectOwner &c);
		ObjectOwner(EObjectOwnerType e, Point3D s) { SetPosition(s); SetType(e); }
		~ObjectOwner();

		virtual ObjectOwner *Clone() = 0;
		virtual void Update() = 0;
		virtual BOOL Lost(DWORD dwTickcount) { return FALSE; }
		EObjectOwnerType GetType() { return m_eType; }
		CPoint<int> &GetPosition() { return m_cPosition; }
		void SetType(EObjectOwnerType e) { m_eType = e; }
		void SetPosition(Point3D s) { m_cPosition.x = s.iX; m_cPosition.y = s.iY; m_cPosition.z = s.iZ; }
	protected:
		EObjectOwnerType m_eType;
		CPoint<int> m_cPosition;
	};
	class ObjectOwnerUnit : public ObjectOwner
	{
	public:
		ObjectOwnerUnit(smCHAR *_pcUnit);
		ObjectOwnerUnit(ObjectOwnerUnit & c);
		~ObjectOwnerUnit();

		virtual ObjectOwnerUnit *Clone();
		virtual void Update();
		virtual BOOL Lost(DWORD dwTickcount);

		void AddAnimationTypeLostCondition(EAnimationType eAnimationType) { m_vAnimationTypeLostConditions.push_back(eAnimationType); }
		ID GetUnitID();
	protected:
		ID m_IID = 0;
		smCHAR *m_pcUnit = NULL;

		std::vector<EAnimationType> m_vAnimationTypeLostConditions;
	};
	class ObjectOwnerPosition : public ObjectOwner
	{
	public:
		ObjectOwnerPosition(Point3D s);
		ObjectOwnerPosition(ObjectOwnerPosition &c);
		~ObjectOwnerPosition();

		virtual ObjectOwnerPosition *Clone();
		virtual void Update();
		virtual BOOL Lost(DWORD dwTickcount) { return FALSE; };
	};
	class ObjectOwnerProjectile : public ObjectOwner
	{
	public:
		ObjectOwnerProjectile(smCHAR *_pcUnit);
		ObjectOwnerProjectile(ObjectOwnerProjectile &c);
		~ObjectOwnerProjectile();

		virtual ObjectOwnerProjectile *Clone();
		virtual void Update();
		virtual BOOL Lost(DWORD dwTickcount);
		ID GetUnitID() { return m_IID; }
	protected:
		ID m_IID = 0;
		smCHAR *m_pcUnit = NULL;
	};
}