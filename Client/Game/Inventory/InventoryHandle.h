#pragma once

#define	INVENTORYITEMSLOT					(INVENTROYHANDLE->GetInventoryItemSlot())

namespace INVENTROY
{
	class Handle : public CBaseHandle
	{
	public:
		Handle();
		Handle(EHandle eID);
		virtual ~Handle();

		void Init();
		void Shutdown();

		void UpdateIntegrity(UINT uIntegrity);

		ItemInventoryData *GetInventoryItemSlot() { return m_psaInventroyData; }
	private:
		ItemInventoryData * m_psaInventroyData = nullptr;
	};
}
