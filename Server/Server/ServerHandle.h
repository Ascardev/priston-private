#pragma once

#define PARTYHANDLE				(GHANDLE->GetPartyHandle())
#define XMASHANDLE				(GHANDLE->GetChristmasHandle())
#define SKILLHANDLE				(GHANDLE->GetSkillHandle())
#define AGEHANDLE				(GHANDLE->GetAgeHandle())
#define COINSHOPHANDLE			(GHANDLE->GetCoinShopHandle())
#define DISTRIBUTORHANDLE		(GHANDLE->GetDistributorHandle())


class CServerHandle
{
public:
	CServerHandle();
	virtual ~CServerHandle();

	void Init();
	void Shutdown();

	CPartyHandle * GetPartyHandle() { return m_pcPartyHandle; }
	CChristmasHandle * GetChristmasHandle() { return m_pcChristmasHandle; }
	CSkillHandle * GetSkillHandle() { return m_pcSkillHandle; }
	CAgeHandle * GetAgeHandle() { return m_pcAgeHandle; }
	CCoinShopHandle * GetCoinShopHandle() { return m_pcCoinShopHandle; }
	CDistributorHandle * GetDistributorHandle() { return m_pcDistributorHandle; }
private:
	CPartyHandle * m_pcPartyHandle = nullptr;
	CChristmasHandle * m_pcChristmasHandle = nullptr;
	CSkillHandle * m_pcSkillHandle = nullptr;
	CAgeHandle * m_pcAgeHandle = nullptr;
	CCoinShopHandle * m_pcCoinShopHandle = nullptr;
	CDistributorHandle * m_pcDistributorHandle = nullptr;

};
