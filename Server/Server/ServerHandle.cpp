#include "StdAfx.h"

CServerHandle::CServerHandle()
{
	m_pcPartyHandle = new CPartyHandle;
	m_pcChristmasHandle = new CChristmasHandle;
	m_pcSkillHandle = new CSkillHandle;
	m_pcAgeHandle = new CAgeHandle;
	m_pcCoinShopHandle = new CCoinShopHandle;
	m_pcDistributorHandle = new CDistributorHandle;
}
CServerHandle::~CServerHandle()
{
	DELET(m_pcDistributorHandle);
	DELET(m_pcCoinShopHandle);
	DELET(m_pcAgeHandle);
	DELET(m_pcSkillHandle);
	DELET(m_pcChristmasHandle);
	DELET(m_pcPartyHandle);
}
void CServerHandle::Init()
{
	INIT(m_pcCoinShopHandle);
}
void CServerHandle::Shutdown()
{

}