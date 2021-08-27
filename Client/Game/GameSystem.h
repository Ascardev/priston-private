#pragma once

class CGameSystem : public CINFO::System 
{
public:
	CGameSystem();
	virtual ~CGameSystem();

	void Init();
	void Shutdown();
};