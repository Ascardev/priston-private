#include "StdAfx.h"
#include "LuaBase.h"

namespace LUA
{
	Base::Base()
	{
		m_strName = "";
		m_strNameType = "";

		m_eType = LUATYPE_None;
		m_eVisualType = LUAVISUALTYPE_None;

		m_eSourceBlendMode = BLENDTYPE_None;
		m_uTextureID = 0;

		m_sCurLifeTime = 0.0f;
		m_sMaxLifeTime = -1.0f;

		m_bLoop = FALSE;
		m_fLoopAt = 0.0f;
		m_fLoopTime = 0.0f;

		m_pOwner = NULL;

		m_bActive = FALSE;
	}
	Base::Base(Base & c)
	{
		m_strName = "";

		m_eType = c.m_eType;
		m_eVisualType = c.m_eVisualType;

		m_eSourceBlendMode = c.m_eSourceBlendMode;
		m_uTextureID = c.m_uTextureID;

		m_sColor = c.m_sColor;
		m_sSize = c.m_sSize;

		m_sPosition = c.m_sPosition;
		m_sVelocity = c.m_sVelocity;

		m_sRotation = c.m_sRotation;
		m_sAngularVelocity = c.m_sAngularVelocity;

		m_sCurLifeTime = c.m_sCurLifeTime;
		m_sMaxLifeTime = c.m_sMaxLifeTime;

		m_bLoop = c.m_bLoop;
		m_fLoopAt = c.m_fLoopAt;
		m_fLoopTime = c.m_fLoopTime;

		for (vector<Event*>::iterator it = c.m_vLuaEvents.begin(); it != c.m_vLuaEvents.end(); it++)
		{
			Event * pcLuaEvent = *it;

			m_vLuaEvents.push_back(pcLuaEvent->Clone());
		}

		for (vector<ModifierGroup*>::iterator it = c.m_vLuaModifierGroups.begin(); it != c.m_vLuaModifierGroups.end(); it++)
		{
			ModifierGroup * pcLuaModifierGroup = *it;

			m_vLuaModifierGroups.push_back(new ModifierGroup(*pcLuaModifierGroup));
		}

		m_pOwner = (c.m_pOwner ? c.m_pOwner->Clone() : NULL);

		m_bActive = FALSE;
	}
	Base::~Base()
	{
		//WRITEDBG( "~CParticle()" );

		for (vector<Event*>::iterator it = m_vLuaEvents.begin(); it != m_vLuaEvents.end(); it++)
		{
			Event * pcLuaEvent = *it;

			DELET(pcLuaEvent);
		}
		m_vLuaEvents.clear();

		for (vector<ModifierGroup*>::iterator it = m_vLuaModifierGroups.begin(); it != m_vLuaModifierGroups.end(); it++)
		{
			ModifierGroup * pcLuaModifierGroup = *it;

			DELET(pcLuaModifierGroup);
		}
		m_vLuaModifierGroups.clear();

		DELET(m_pOwner);
	}
	Base * Base::Clone()
	{
		Base * pcClone = new Base(*this);

		return pcClone;
	}
	void Base::Birth()
	{
		m_sColor.Birth();
		m_sSize.Birth();

		m_sPosition.Birth();
		m_sVelocity.Birth();

		m_sRotation.Birth();
		m_sAngularVelocity.Birth();

		m_sCurLifeTime.Birth();
		m_sMaxLifeTime.Birth();
	}
	BOOL Base::Update(double fTime)
	{
		if (m_pOwner)
		{
			//Update Owner
			m_pOwner->Update();
		}

		double fCurLifeTime = m_sCurLifeTime.t.value;
		double fMaxLifeTime = m_sMaxLifeTime.t.value;

		double fNewCurLifeTime = fCurLifeTime + fTime;

		//Reached Max Life Time?
		if (fNewCurLifeTime > fMaxLifeTime)
			fNewCurLifeTime = fMaxLifeTime;

		//Looping?
		if (m_bLoop)
		{
			while (fNewCurLifeTime >= m_fLoopAt)
			{
				//Perform Updates from the Current Life Time to the Loop At Time
				Loop(fCurLifeTime, m_fLoopAt);

				fCurLifeTime = m_fLoopTime;
				fNewCurLifeTime = fCurLifeTime + (fNewCurLifeTime - m_fLoopAt);
			}
		}

		Loop(fCurLifeTime, fNewCurLifeTime);

		fCurLifeTime = fNewCurLifeTime;

		m_sCurLifeTime.t.value = fCurLifeTime;

		if (fCurLifeTime >= fMaxLifeTime)
			return TRUE;

		//Apply Modifiers
		Modify();

		return FALSE;
	}
	void Base::Loop(double fBegin, double fEnd)
	{
		//Loop through Events, must be ordered ascending by time
		for (vector<Event*>::iterator it = m_vLuaEvents.begin(); it != m_vLuaEvents.end(); it++)
		{
			Event * pcLuaEvent = *it;

			double fEventTime = pcLuaEvent->GetTime();
			if ((fEventTime >= fBegin) && (fEventTime < fEnd))
			{
				double fTimeTillEvent = fEventTime - fBegin;

				//Apply any time based changes to Particle before applying Event
				Apply(fTimeTillEvent);
				fBegin += fTimeTillEvent;

				//Finally, we apply the changes of the Event to this Particle
				pcLuaEvent->Apply(this);
			}
		}

		//Any leftover time we apply to the Particle here
		Apply(fEnd - fBegin);
	}
	void Base::Modify()
	{
		for (vector<ModifierGroup*>::iterator it = m_vLuaModifierGroups.begin(); it != m_vLuaModifierGroups.end(); it++)
		{
			ModifierGroup * pcLuaModifierGroup = *it;

			pcLuaModifierGroup->Apply(this);
		}
	}
	void Base::Render()
	{
		SMD::Billboard bb;

		if ((m_eType == PARTICLETYPE_Follow) && (m_pOwner != NULL))
		{
			CPoint<int> & sOwnerPosition = m_pOwner->GetPosition();

			bb.sPosition = Point3D(sOwnerPosition.x + m_sPosition.x.value, sOwnerPosition.y + m_sPosition.y.value, sOwnerPosition.z + m_sPosition.z.value);
		}
		else
		{
			bb.sPosition = Point3D(m_sPosition.x.value, m_sPosition.y.value, m_sPosition.z.value);
		}

		bb.uWidth = m_sSize.GetW();
		bb.uHeight = m_sSize.GetH();

		bb.sRect = TextureRangle2D(0, 0, 1, 1);

		bb.uID = m_uTextureID;

		bb.sColor = Color4D(m_sColor.r.value, m_sColor.g.value, m_sColor.b.value, m_sColor.a.value);

		Point3D sAngle = Point3D((int)m_sRotation.p.value, (int)m_sRotation.y.value, (int)m_sRotation.r.value);

		switch (m_eVisualType)
		{
		case PARTICLEVISUALTYPE_Billboard:
			cpRender->AddBillboard(&bb);
			break;
		case PARTICLEVISUALTYPE_BillboardRotation:
			cpRender->AddBillboardRotation(&bb, sAngle);
			break;
		case PARTICLEVISUALTYPE_BillboardHorizontal:
			cpRender->AddBillboardHorizontal(&bb);
			break;
		case PARTICLEVISUALTYPE_BillboardHorizontalRotation:
			cpRender->AddBillboardHorizontalRotation(&bb, sAngle);
			break;
		case PARTICLEVISUALTYPE_BillboardVertical:
			cpRender->AddBillboardVertical(&bb);
			break;
		case PARTICLEVISUALTYPE_BillboardVerticalRotation:
			cpRender->AddBillboardVerticalRotation(&bb, sAngle);
			break;
		}
	}
	void Base::AddLuaModifierGroup(ModifierGroup * pcLuaModifierGroup)
	{
		m_vLuaModifierGroups.push_back(pcLuaModifierGroup);
	}
	ModifierGroup * Base::GetLuaModifierGroup(ELuaModifierGroupType eType)
	{
		for (vector<ModifierGroup*>::iterator it = m_vLuaModifierGroups.begin(); it != m_vLuaModifierGroups.end(); it++)
		{
			ModifierGroup * pcLuaModifierGroup = *it;

			if (pcLuaModifierGroup->GetType() == eType)
				return pcLuaModifierGroup;
		}

		return NULL;
	}
	void Base::Apply(double fTime)
	{
		if (fTime > 0.0f)
		{
			ApplyVelocity(m_sVelocity, fTime);
			ApplyAngularVelocity(m_sAngularVelocity, fTime);
		}
	}
	void Base::ApplyVelocity(Point & sVelo, double fTime)
	{
		Point sPos = sVelo * fTime;

		sPos.x.value /= 1000;
		sPos.y.value /= 1000;
		sPos.z.value /= 1000;

		m_sPosition += sPos;
	}
	void Base::ApplyAngularVelocity(Rotation & sAnguVelo, double fTime)
	{
		Rotation sRot = sAnguVelo * fTime;

		sRot.p.value /= 1000;
		sRot.y.value /= 1000;
		sRot.r.value /= 1000;

		m_sRotation += sRot;
	}
}