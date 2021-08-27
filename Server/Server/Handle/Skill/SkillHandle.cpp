#include "StdAfx.h"
#include "SkillHandle.h"

CSkillHandle::CSkillHandle()
{
	m_pcPriestess = new CPriestess;
}
CSkillHandle::~CSkillHandle()
{
	DELET(m_pcPriestess);
}