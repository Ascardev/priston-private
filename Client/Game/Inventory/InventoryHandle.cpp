#include "StdAfx.h"
#include "InventoryHandle.h"

namespace INVENTROY
{
	Handle::Handle() : CBaseHandle()
	{

	}
	Handle::Handle(EHandle eID) : CBaseHandle(eID)
	{

	}
	Handle::~Handle()
	{

	}
	void Handle::Init()
	{
		/*m_psaInventroyData = new ItemInventoryData[INVENTORY_MAX_POS];

		for (int i = 0; i < INVENTORY_MAX_POS; i++)
		{
			ZeroMemory(&m_psaInventroyData[i], sizeof(ItemInventoryData));
		}

		m_psaInventroyData[0].iItemSlot = ITEMSLOTFLAG_RightHand;
		m_psaInventroyData[0].sBox = Rectangle2D(574 + 1, 433 + 1, 640, 544);

		m_psaInventroyData[1].iItemSlot = ITEMSLOTFLAG_LeftHand;
		m_psaInventroyData[1].sBox = Rectangle2D(722 + 1, 433 + 1, 788, 544);

		m_psaInventroyData[2].iItemSlot = ITEMSLOTFLAG_Armor;
		m_psaInventroyData[2].sBox = Rectangle2D(648 + 1, 433 + 1, 714, 544);

		m_psaInventroyData[3].iItemSlot = ITEMSLOTFLAG_Amulet;
		m_psaInventroyData[3].sBox = Rectangle2D(304 + 1, 438 + 1, 326, 460);

		m_psaInventroyData[4].iItemSlot = ITEMSLOTFLAG_RingRight;
		m_psaInventroyData[4].sBox = Rectangle2D(356 + 1, 438 + 1, 378, 460);

		m_psaInventroyData[5].iItemSlot = ITEMSLOTFLAG_RingLeft;
		m_psaInventroyData[5].sBox = Rectangle2D(330 + 1, 438 + 1, 352, 460);

		m_psaInventroyData[6].iItemSlot = ITEMSLOTFLAG_Sheltom;
		m_psaInventroyData[6].sBox = Rectangle2D(382 + 1, 438 + 1, 404, 460);

		m_psaInventroyData[7].iItemSlot = ITEMSLOTFLAG_Bracelets;
		m_psaInventroyData[7].sBox = Rectangle2D(411 + 1, 438 + 1, 455, 482);

		m_psaInventroyData[8].iItemSlot = ITEMSLOTFLAG_Gauntlets;
		m_psaInventroyData[8].sBox = Rectangle2D(462 + 1, 438 + 1, 506, 482);

		m_psaInventroyData[9].iItemSlot = ITEMSLOTFLAG_Boots;
		m_psaInventroyData[9].sBox = Rectangle2D(513 + 1, 438 + 1, 557, 482);

		m_psaInventroyData[10].iItemSlot = ITEMSLOTFLAG_Potion;
		m_psaInventroyData[10].sBox = Rectangle2D(495, 565, 495 + 26, 565 + 26);

		m_psaInventroyData[11].iItemSlot = ITEMSLOTFLAG_Potion;
		m_psaInventroyData[11].sBox = Rectangle2D(495 + 26, 565, 495 + 26 + 26, 565 + 26);

		m_psaInventroyData[12].iItemSlot = ITEMSLOTFLAG_Potion;
		m_psaInventroyData[12].sBox = Rectangle2D(495 + 26 + 26, 565, 495 + 26 + 26 + 26, 565 + 26);

		m_psaInventroyData[13].iItemSlot = ITEMSLOTFLAG_Costume;
		m_psaInventroyData[13].sBox = Rectangle2D(648 + 1, 433 + 1, 714, 544);

		m_psaInventroyData[14].iItemSlot = ITEMSLOTFLAG_WingRight;
		m_psaInventroyData[14].sBox = Rectangle2D(574 + 1, 433 + 1, 640, 544);

		m_psaInventroyData[15].iItemSlot = ITEMSLOTFLAG_WingLeft;
		m_psaInventroyData[15].sBox = Rectangle2D(722 + 1, 433 + 1, 788, 544);*/

	}
	void Handle::Shutdown()
	{
		//DELETA(m_psaInventroyData);
	}
	void Handle::UpdateIntegrity(UINT uIntegrity)
	{
		for (int i = 0; i < INVENTORY_MAX_POS; i++)
		{
			if (sInven[i].ItemIndex)
			{
				ItemData * psItemData = &cInvenTory.InvenItem[sInven[i].ItemIndex - 1];

				if (psItemData->bValid && psItemData->sItem.sIntegrity.sMax > 0)
				{
					psItemData->sItem.sIntegrity.sMin -= uIntegrity;
					if (psItemData->sItem.sIntegrity.sMin <= 0)
					{
						psItemData->sItem.sIntegrity.sMin = 0;
						psItemData->sItem.bCanNotUse = TRUE;
					}
					else if (psItemData->sItem.sIntegrity.sMin > psItemData->sItem.sIntegrity.sMax)
						psItemData->sItem.sIntegrity.sMin = psItemData->sItem.sIntegrity.sMax;
				}
			}
		}
	}
}