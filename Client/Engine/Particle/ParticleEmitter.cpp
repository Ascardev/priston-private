#include "StdAfx.h"
#include "ParticleEmitter.h"

namespace PARTICLE
{
	Emitter::Emitter(System *pcParticleSystem)
	{
		m_pcParticleSystem = pcParticleSystem;

		m_eType = PARTICLEEMITTERTYPE_Follow;

		m_sCurDelay = 0.0f;
		m_sMaxDelay = 0.0f;

		m_sCurLifeTime = 0.0f;
		m_sMaxLifeTime = -1.0f;

		m_pOwner = NULL;

		m_fLastEmit = 0.0f;

		m_bActive = FALSE;
	}
	Emitter::Emitter(System *pcParticleSystem, Emitter &c)
	{
		m_pcParticleSystem = pcParticleSystem;

		m_eType = c.m_eType;

		m_sPosition = c.m_sPosition;
		m_sVelocity = c.m_sVelocity;

		m_sRotation = c.m_sRotation;
		m_sAngularVelocity = c.m_sAngularVelocity;

		m_sCurDelay = c.m_sCurDelay;
		m_sMaxDelay = c.m_sMaxDelay;

		m_sCurLifeTime = c.m_sCurLifeTime;
		m_sMaxLifeTime = c.m_sMaxLifeTime;

		m_sParticles = c.m_sParticles;
		m_sInterval = c.m_sInterval;

		m_pOwner = (c.m_pOwner ? c.m_pOwner->Clone() : NULL);

		m_fLastEmit = 0.0f;

		m_bActive = FALSE;
	}
	Emitter::~Emitter()
	{
		DELET(m_pOwner);
	}
	void Emitter::Birth()
	{
		m_sCurDelay.Birth();
		m_sMaxDelay.Birth();

		m_sCurLifeTime.Birth();
		m_sMaxLifeTime.Birth();

		m_sParticles.Birth();
		m_sInterval.Birth();
	}
	BOOL Emitter::Update(double fTime)
	{
		if (m_pOwner)
		{
			//Update Owner
			m_pOwner->Update();
		}

		double fCurDelay = m_sCurDelay.Get();
		double fMaxDelay = m_sMaxDelay.Get();

		if (fCurDelay < fMaxDelay)
		{
			fCurDelay += fTime;

			if (fCurDelay > fMaxDelay)
			{
				fTime += (fCurDelay - fMaxDelay);

				fCurDelay = fMaxDelay;
			}

			m_sCurDelay.Set(fCurDelay);
		}

		if (fCurDelay >= fMaxDelay)
		{
			//Handle Time Events
			double fCurLifeTime = m_sCurLifeTime.t.value;
			double fMaxLifeTime = m_sMaxLifeTime.t.value;

			double fNewCurLifeTime = fCurLifeTime + fTime;

			//Reached Max Life Time?
			if (fNewCurLifeTime > fMaxLifeTime)
				fNewCurLifeTime = fMaxLifeTime;

			//Update Emit
			if ((m_sParticles.value > 0) || (m_sParticles.value == -1))
			{
				m_fLastEmit -= fTime;

				if (m_fLastEmit <= 0.0f)
				{
					double fOverTime = abs(m_fLastEmit);
					double fInterval = m_sInterval.value;

					do
					{
						//Emit with Update Over Time
						Emit(fOverTime);

						//Finite Particles?
						if (m_sParticles.value != -1)
						{
							m_sParticles.value--;

							if (m_sParticles.value <= 0)
								break;
						}

						//Another Particle?
						fOverTime -= fInterval;
					} while (fOverTime >= 0.0f);

					//Save Left Over Time
					m_fLastEmit = abs(fOverTime);
				}
			}

			fCurLifeTime = fNewCurLifeTime;

			m_sCurLifeTime.t.value = fCurLifeTime;

			//If the Max Life Time is negative, this Emitter never ends by time. Otherwise it does
			if (fMaxLifeTime >= 0.0f)
			{
				if (fCurLifeTime >= fMaxLifeTime)
					return TRUE;
			}
		}

		return FALSE;
	}
	void Emitter::Emit(double fUpdateTime)
	{
		//Create the Clone Particle
		Particle * pcParticle = m_pcParticleSystem->m_pcParticle->Clone();

		//Fill Particle Attributes
		if (((m_eType == PARTICLEEMITTERTYPE_Follow) && (m_pOwner != NULL)) && (pcParticle->m_eType != PARTICLETYPE_Follow))
		{
			//Base position on owner
			CPoint<int> & sOwnerPosition = m_pOwner->GetPosition();

			pcParticle->m_sPosition.x = Particle::Int(m_sPosition.x.low + sOwnerPosition.GetX(), m_sPosition.x.high + sOwnerPosition.GetX());
			pcParticle->m_sPosition.y = Particle::Int(m_sPosition.y.low + sOwnerPosition.GetY(), m_sPosition.y.high + sOwnerPosition.GetY());
			pcParticle->m_sPosition.z = Particle::Int(m_sPosition.z.low + sOwnerPosition.GetZ(), m_sPosition.z.high + sOwnerPosition.GetZ());
		}
		else
		{
			//No owner
			pcParticle->m_sPosition = m_sPosition;
		}
		pcParticle->m_sVelocity = m_sVelocity;

		pcParticle->m_sRotation = m_sRotation;
		pcParticle->m_sAngularVelocity = m_sAngularVelocity;

		//Birth Particle
		pcParticle->Birth();

		//Update Particle
		if (!pcParticle->Update(fUpdateTime))
		{
			//Add Particle to System
			m_pcParticleSystem->Add(pcParticle);
		}
		else
		{
			//Delete Particle
			DELET(pcParticle);
		}
	}
}