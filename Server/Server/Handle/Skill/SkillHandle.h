#pragma once

#define PRIESTESSSKILL		(SKILLHANDLE->GetPriestess())


class CSkillHandle
{
public:
	CSkillHandle();
	virtual ~CSkillHandle();

	CPriestess * GetPriestess() { return m_pcPriestess; }
private:
	CPriestess * m_pcPriestess = nullptr;
};