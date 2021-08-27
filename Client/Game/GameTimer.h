#pragma once

class CGameTime : public CINFO::Time
{
public:
	CGameTime();
	virtual ~CGameTime();

	void Init();
	void Shutdown();

	void Update(double fTime);

	void Add(BASE::LPTIME pTimer);
private:
	CList<BASE::LPTIME> *m_pcList;
};