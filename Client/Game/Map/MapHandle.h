#pragma once

namespace MAP
{
	class Handle : public CBaseHandle
	{
	public:
		Handle();
		Handle(EHandle eID);
		virtual ~Handle();

		void Init();
		void Shutdown();

	protected:
		Info *Add(Info *pInfo) { m_vpInfo.push_back(pInfo); return pInfo; }
	private:
		std::vector<Info *> m_vpInfo;

	};
}