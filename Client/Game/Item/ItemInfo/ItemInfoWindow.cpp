#include "StdAfx.h"
#include "ItemInfoWindow.h"

namespace ITEM
{
	namespace INFO
	{
		Window::Window()
		{
			m_iSocketGem[0] = -1;
			m_iSocketGem[1] = -1;
		}
		Window::~Window()
		{

		}
		void Window::Init()
		{
			//Load Images
			m_pImageMaskLeftTop = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\mask\\topleft.png");
			m_pImageMaskRightTop = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\mask\\topright.png");
			m_pImageMaskLeftBottom = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\mask\\bottomleft.png");
			m_pImageMaskRightBottom = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\mask\\bottomright.png");

			//Load Border Images
			m_pImageBorderLeftTop = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\topleft.png");
			m_pImageBorderRightTop = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\topright.png");
			m_pImageBorderTop = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\top.png");
			m_pImageBorderRightBottom = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\bottomright.png");
			m_pImageBorderLeftBottom = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\bottomleft.png");
			m_pImageBorderBottom = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\bottom.png");
			m_pImageBorderLeft = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\left.png");
			m_pImageBorderRight = UI::ImageLoader::LoadImage_("Resources\\UI\\box\\border\\right.png");

			//Load Icons
			m_pImageIconArmor = UI::ImageLoader::LoadImage_("Resources\\UI\\Items\\Info\\Weapon_Knight.bmp");
			m_pImageIconRobe = UI::ImageLoader::LoadImage_("Resources\\UI\\Items\\Info\\Weapon_Wizard.bmp");
			m_pImageIconWeaponOneHand = UI::ImageLoader::LoadImage_("Resources\\UI\\Items\\Info\\Weapon_Onehand.bmp");
			m_pImageIconWeaponTwoHand = UI::ImageLoader::LoadImage_("Resources\\UI\\Items\\Info\\Weapon_Twohand.bmp");

			//Load Aging Bar
			m_pImageAgingBar = UI::ImageLoader::LoadImage_("Resources\\UI\\Items\\Info\\Aging\\Bar.bmp");
			m_pImageAgingBarGage = UI::ImageLoader::LoadImage_("Resources\\UI\\Items\\Info\\Aging\\Bar_.bmp");
			m_pImageAgingBarNum = UI::ImageLoader::LoadImage_("Resources\\UI\\Items\\Info\\Aging\\Aging.bmp");

			m_pTextAging = std::make_shared<UI::Text>(Rectangle2D(0, 0, 0, 0));
			m_pTextAging->SetFont("Arial", 14, 0, FALSE, FALSE, D3DCOLOR_ARGB(255, 215, 215, 215));

			m_cBackgroundColor2 = UI::Color(235, 45, 39, 27);
			m_cBackgroundColor2 = UI::Color(245, 9, 23, 22);

			m_paSocketText[0][0] = std::make_shared<UI::Text>(Rectangle2D(0, 0, 0, 0));
			m_paSocketText[0][0]->SetFont("Arial", 16, 0, FALSE, TRUE, -1);

			m_paSocketText[0][1] = std::make_shared<UI::Text>(Rectangle2D(0, 0, 0, 0));
			m_paSocketText[0][1]->SetFont("Arial", 16, 0, FALSE, FALSE, -1);

			m_paSocketText[1][0] = std::make_shared<UI::Text>(Rectangle2D(0, 0, 0, 0));
			m_paSocketText[1][0]->SetFont("Arial", 16, 0, FALSE, TRUE, -1);

			m_paSocketText[1][1] = std::make_shared<UI::Text>(Rectangle2D(0, 0, 0, 0));
			m_paSocketText[1][1]->SetFont("Arial", 16, 0, FALSE, FALSE, -1);

			m_pRenderTargetMask = GRAPHICDEVICE->MakeRenderTarget(5001, 600, 600);
			m_pEffectMask = GRAPHICDEVICE->GetEffectFactory()->MakeEffect("Resources\\Shaders\\UI\\InfoBox.fx");

			//Socket Images
			m_pImageSocketBackground = UI::ImageLoader::LoadImage_("Resources\\UI\\Items\\Info\\Socket\\socketbg.png");

			for (int i = 0; i < 6; i++)
			{
				m_paSocket[i] = UI::ImageLoader::LoadImage_("Resources\\UI\\Items\\Info\\Socket\\socket%d.png", i + 1);
			}
			for (int i = 0; i < 15; i++)
			{
				m_paSocketGems[i] = UI::ImageLoader::LoadImage_("image\\Sinimage\\Items\\Event\\itPR5%02d.bmp", i + 1);
			}
		}
		void Window::Shutdown()
		{
			CLEARPTR(m_pImageMaskLeftTop);
			CLEARPTR(m_pImageMaskRightTop);
			CLEARPTR(m_pImageMaskLeftBottom);
			CLEARPTR(m_pImageMaskRightBottom);
			CLEARPTR(m_pImageBorderLeftTop);
			CLEARPTR(m_pImageBorderRightTop);
			CLEARPTR(m_pImageBorderTop);
			CLEARPTR(m_pImageBorderRightBottom);
			CLEARPTR(m_pImageBorderLeftBottom);
			CLEARPTR(m_pImageBorderBottom);
			CLEARPTR(m_pImageBorderLeft);
			CLEARPTR(m_pImageBorderRight);

			CLEARPTR(m_pImageIconArmor);
			CLEARPTR(m_pImageIconRobe);
			CLEARPTR(m_pImageIconWeaponOneHand);
			CLEARPTR(m_pImageIconWeaponTwoHand);

			CLEARPTR(m_pImageAgingBar);
			CLEARPTR(m_pImageAgingBarGage);
			CLEARPTR(m_pImageAgingBarNum);

			UI::ImageLoader::DeleteImage(m_pImageMaskLeftTop);
			UI::ImageLoader::DeleteImage(m_pImageMaskRightTop);
			UI::ImageLoader::DeleteImage(m_pImageMaskLeftBottom);
			UI::ImageLoader::DeleteImage(m_pImageMaskRightBottom);
			UI::ImageLoader::DeleteImage(m_pImageBorderLeftTop);
			UI::ImageLoader::DeleteImage(m_pImageBorderRightTop);
			UI::ImageLoader::DeleteImage(m_pImageBorderTop);
			UI::ImageLoader::DeleteImage(m_pImageBorderRightBottom);
			UI::ImageLoader::DeleteImage(m_pImageBorderLeftBottom);
			UI::ImageLoader::DeleteImage(m_pImageBorderBottom);
			UI::ImageLoader::DeleteImage(m_pImageBorderLeft);
			UI::ImageLoader::DeleteImage(m_pImageBorderRight);

			UI::ImageLoader::DeleteImage(m_pImageIconArmor);
			UI::ImageLoader::DeleteImage(m_pImageIconRobe);
			UI::ImageLoader::DeleteImage(m_pImageIconWeaponOneHand);
			UI::ImageLoader::DeleteImage(m_pImageIconWeaponTwoHand);

			UI::ImageLoader::DeleteImage(m_pImageAgingBar);
			UI::ImageLoader::DeleteImage(m_pImageAgingBarGage);
			UI::ImageLoader::DeleteImage(m_pImageAgingBarNum);
		}
		void Window::AddString(int iSide, const std::string &strString, DWORD dwColor, BOOL bBold)
		{
			std::vector<std::string> vString;

			//Find breakline in String
			BOOL bMultiLine = FALSE;

			if (strString.find('\n') != std::string::npos)
			{
				vString = split(strString, '\n');
				bMultiLine = TRUE;
			}
			switch (iSide)
			{
			case 0: // Left Side 左边
				// Is Mutiline 
				if (bMultiLine)
				{
					int i = 0;
					for (const auto &strSplitted : vString)
					{
						m_vLeftText.push_back(std::make_shared<UI::Text>(strSplitted, Rectangle2D(0, 0, 180, 20), bBold, dwColor));
						i++;

						if (i != vString.size())
						{
							m_vRightText.push_back(std::make_shared<UI::Text>("", Rectangle2D(0, 0, 180, 20), bBold, dwColor));
						}
					}
				}
				else
				{
					m_vLeftText.push_back(std::make_shared<UI::Text>(strString, Rectangle2D(0, 0, 180, 20), bBold, dwColor));
				}
				break;
			case 1: // Right Side
				m_vRightText.push_back(std::make_shared<UI::Text>(strString, Rectangle2D(0, 0, 180, 20), bBold, dwColor));
				break;
			}
		}
		void Window::SetLineColor(DWORD dwColor, int iSide, int iLineCount)
		{
			int iSetColor = iLineCount < 0 ? m_vLeftText.size() - 1 : iLineCount;

			switch (iSide)
			{
			case -1:
				m_vLeftText[iSetColor]->SetColor(dwColor);
				m_vRightText[iSetColor]->SetColor(dwColor);
				break;
			case 0:
				m_vLeftText[iSetColor]->SetColor(dwColor);
				break;
			case 1:
				m_vRightText[iSetColor]->SetColor(dwColor);
				break;
			}
		}
		void Window::AppendLineText(std::string str, int iSide, int iLineCount)
		{
			int iSetColor = iLineCount < 0 ? m_vLeftText.size() - 1 : iLineCount;

			switch (iSide)
			{
			case -1:
				m_vLeftText[iSetColor]->AppendText(str);
				m_vRightText[iSetColor]->AppendText(str);
				break;
			case 0:
				m_vLeftText[iSetColor]->AppendText(str);
				break;
			case 1:
				m_vRightText[iSetColor]->AppendText(str);
				break;
			}
		}
		void Window::AddCompareString(const std::string & strString, DWORD dwColor)
		{
			m_vRowCompare.push_back(m_vLeftText.size());
			m_vCompareText.push_back(std::make_shared<UI::Text>(strString, Rectangle2D(0, 0, 180, 20), FALSE, dwColor));
		}
		void Window::ClearCompareItem()
		{
			m_cItemCompare = ItemData();
			m_bCompareItem = FALSE;
		}
		void Window::SetCompareItem(const ItemData *pcCompareItemData, BOOL bEquippedItem)
		{
			m_cItemCompare = *pcCompareItemData;
			m_bCompareItem = TRUE;
			m_bIsEquippedItem = bEquippedItem;
		}
		void Window::PrepareShowItem(ItemData * pcItemData, BOOL bShowBuyPrice, BOOL bShowSellPrice, BOOL bShowChecksums)
		{
			//Clear Vectors
			m_vLeftText.clear();
			m_vRightText.clear();
			m_vCompareText.clear();
			m_vRowCompare.clear();

			m_iSocketCount = 0;
			m_bIsPerfectItem = FALSE;
			m_bCantUseItem = FALSE;

			m_cBackgroundColor1 = UI::Color(235, 45, 39, 27);
			m_cBackgroundColor2 = UI::Color(245, 9, 23, 22);

			m_cItemWrapper = *pcItemData;

			//Name Item 物品的名字
			AddString(0, m_cItemWrapper.sItem.szItemName, -1, TRUE);
			AddString(1, "");

			//Color Name Item
			if (m_cItemWrapper.sItem.iItemUniqueID)
			{
				SetLineColor(D3DCOLOR_ARGB(255, 128, 255, 128));
			}
			else
			{
				// Default Color
				SetLineColor(D3DCOLOR_ARGB(255, 222, 231, 255));

				//Set Special Colors 特效颜色

				if (m_cItemWrapper.sItem.eCraftType)
				{
					switch (m_cItemWrapper.sItem.eCraftType)
					{
					case ITEMCRAFTTYPE_Mixing:
						SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255));
						break;
					case ITEMCRAFTTYPE_Aging:
						SetLineColor(D3DCOLOR_ARGB(255, 100, 230, 255));
						break;
					case ITEMCRAFTTYPE_QuestWeapon:
						SetLineColor(D3DCOLOR_ARGB(255, 132, 50, 254));
						break;
					}
				}
			}

			//Make Description Item
			FormatItemInfo();

			//Aging Bar 锻造的状态条
			if (m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging)
			{
				AddString(0, "\n ");
				AddString(1, "\n ");
			}

			//Attack Power 攻击伤害
			if (m_cItemWrapper.sItem.sDamage.sMin || m_cItemWrapper.sItem.sDamage.sMax)
			{
				AddString(0, "Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d-%d", m_cItemWrapper.sItem.sDamage.sMin, m_cItemWrapper.sItem.sDamage.sMax), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if ((m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_MinAttackPower) || (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_MaxAttackPower))
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Aging Color
				if ((m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging) && (m_cItemWrapper.sBaseItemID.ToItemBase() == ITEMBASE_Weapon))
					SetLineColor(D3DCOLOR_ARGB(255, 100, 230, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.sDamage.sMin - m_cItemCompare.sItem.sDamage.sMin;
					int iCalcMax = m_cItemWrapper.sItem.sDamage.sMax - m_cItemCompare.sItem.sDamage.sMax;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0 || iCalcMax != 0)
						AddCompareString(FormatString("(%s%d-%d)", iCalc > 0 ? "+" : "", iCalc, iCalcMax), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}

			//Attack fMovementSpeed 攻击速度
			if (m_cItemWrapper.sItem.iAttackSpeed)
			{
				AddString(0, "Attack Speed:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.iAttackSpeed), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_WeaponSpeed)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iAttackSpeed - m_cItemCompare.sItem.iAttackSpeed;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Range 范围
			if (m_cItemWrapper.sItem.iAttackRange)
			{
				AddString(0, "Range:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.iAttackRange), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iAttackRange - m_cItemCompare.sItem.iAttackRange;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Critical 必杀
			if (m_cItemWrapper.sItem.iCritical)
			{
				AddString(0, "Critical Rate:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d%%", m_cItemWrapper.sItem.iCritical), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_Critical)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Aging Color
				if ((m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging) && 
					(m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Claw || 
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Scythe || 
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Dagger || 
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Hammer ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Bow || 
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Javelin || 
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Sword ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Wand ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Phantom))
					SetLineColor(D3DCOLOR_ARGB(255, 100, 230, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iCritical - m_cItemCompare.sItem.iCritical;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Defense 防御
			if (m_cItemWrapper.sItem.iDefenseRating)
			{
				AddString(0, "Defense:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.iDefenseRating), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_DefenseRating)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Aging Color
				if ((m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging) && 
					(m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Orb || 
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Armor ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Robe ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Boots || 
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Gauntlets ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Bracelets ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Shield))
					SetLineColor(D3DCOLOR_ARGB(255, 100, 230, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iDefenseRating - m_cItemCompare.sItem.iDefenseRating;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Attack Rating 攻击命中
			if (m_cItemWrapper.sItem.iAttackRating)
			{
				AddString(0, "Attack Rate:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.iAttackRating), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_AttackRating)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Aging Color
				if ((m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging) && 
					(m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Axe || 
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Claw ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Wand ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Hammer ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Scythe ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Sword ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Bracelets ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Phantom ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Dagger))
					SetLineColor(D3DCOLOR_ARGB(255, 100, 230, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iAttackRating - m_cItemCompare.sItem.iAttackRating;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Absorption 吸收
			if (m_cItemWrapper.sItem.fAbsorbRating)
			{
				AddString(0, "Absorption:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.1f", m_cItemWrapper.sItem.fAbsorbRating), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_AbsorbRating)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Aging Color
				if ((m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging) && 
					(m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Orb || 
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Armor ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Robe ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Shield ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Gauntlets ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Boots))
					SetLineColor(D3DCOLOR_ARGB(255, 100, 230, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.fAbsorbRating - m_cItemCompare.sItem.fAbsorbRating;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Block 格挡
			if (m_cItemWrapper.sItem.fBlockRating)
			{
				AddString(0, "Block:", D3DCOLOR_ARGB(255, 245, 240, 218));

				if (fabs(m_cItemWrapper.sItem.fBlockRating - round(m_cItemWrapper.sItem.fBlockRating)) < FLT_MIN)
					AddString(1, FormatString("%.0f%%", round(m_cItemWrapper.sItem.fBlockRating)), D3DCOLOR_ARGB(255, 240, 215, 150));
				else
					AddString(1, FormatString("%.1f%%", m_cItemWrapper.sItem.fBlockRating), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_Block)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Aging Color
				if ((m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging) && 
					(m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Shield))
					SetLineColor(D3DCOLOR_ARGB(255, 100, 230, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.fBlockRating - m_cItemCompare.sItem.fBlockRating;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f%%)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//fMovementSpeed 移动速度
			if (m_cItemWrapper.sItem.fMovementSpeed)
			{
				AddString(0, "Speed:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.1f", m_cItemWrapper.sItem.fMovementSpeed), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_WalkSpeed)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.fMovementSpeed - m_cItemCompare.sItem.fMovementSpeed;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Integrity
			if (m_cItemWrapper.sItem.sIntegrity.sMin || m_cItemWrapper.sItem.sIntegrity.sMax)
			{
				AddString(0, "Integrity:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d/%d", m_cItemWrapper.sItem.sIntegrity.sMin, m_cItemWrapper.sItem.sIntegrity.sMax), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Aging Color
				if (m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging)
					SetLineColor(D3DCOLOR_ARGB(255, 100, 230, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalcMin = m_cItemWrapper.sItem.sIntegrity.sMin - m_cItemCompare.sItem.sIntegrity.sMin;
					int iCalcMax = m_cItemWrapper.sItem.sIntegrity.sMax - m_cItemCompare.sItem.sIntegrity.sMax;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalcMin != 0)
						AddCompareString(FormatString("(%s%d/%d)", iCalcMin > 0 ? "+" : "", iCalcMin, iCalcMax), iCalcMin > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Mana 魔法
			if (m_cItemWrapper.sItem.sMPRecovery.sMin || m_cItemWrapper.sItem.sMPRecovery.sMax)
			{
				AddString(0, "MP Recovery:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d-%d", m_cItemWrapper.sItem.sMPRecovery.sMin, m_cItemWrapper.sItem.sMPRecovery.sMax), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalcMin = m_cItemWrapper.sItem.sMPRecovery.sMin - m_cItemCompare.sItem.sMPRecovery.sMin;
					int iCalcMax = m_cItemWrapper.sItem.sMPRecovery.sMax - m_cItemCompare.sItem.sMPRecovery.sMax;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalcMin != 0)
						AddCompareString(FormatString("(%s%d-%d)", iCalcMin > 0 ? "+" : "", iCalcMin, iCalcMax), iCalcMin > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//HP 生命
			if (m_cItemWrapper.sItem.sHPRecovery.sMin || m_cItemWrapper.sItem.sHPRecovery.sMax)
			{
				AddString(0, "HP Recovery:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d-%d", m_cItemWrapper.sItem.sHPRecovery.sMin, m_cItemWrapper.sItem.sHPRecovery.sMax), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalcMin = m_cItemWrapper.sItem.sHPRecovery.sMin - m_cItemCompare.sItem.sHPRecovery.sMin;
					int iCalcMax = m_cItemWrapper.sItem.sHPRecovery.sMax - m_cItemCompare.sItem.sHPRecovery.sMax;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalcMin != 0)
						AddCompareString(FormatString("(%s%d-%d)", iCalcMin > 0 ? "+" : "", iCalcMin, iCalcMax), iCalcMin > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//STM 耐力
			if (m_cItemWrapper.sItem.sSPRecovery.sMin || m_cItemWrapper.sItem.sSPRecovery.sMax)
			{
				AddString(0, "STM Recovery:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d-%d", m_cItemWrapper.sItem.sSPRecovery.sMin, m_cItemWrapper.sItem.sSPRecovery.sMax), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalcMin = m_cItemWrapper.sItem.sSPRecovery.sMin - m_cItemCompare.sItem.sSPRecovery.sMin;
					int iCalcMax = m_cItemWrapper.sItem.sSPRecovery.sMax - m_cItemCompare.sItem.sSPRecovery.sMax;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalcMin != 0)
						AddCompareString(FormatString("(%s%d-%d)", iCalcMin > 0 ? "+" : "", iCalcMin, iCalcMax), iCalcMin > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Resistances 属性
			{
				if (m_cItemWrapper.sItem.saElementalDef[0])
				{
					AddString(0, "Organic:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", m_cItemWrapper.sItem.saElementalDef[0]), D3DCOLOR_ARGB(255, 240, 215, 150));

					//Mix Color
					if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_Organic)
						SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

					//Compare Item
					if (m_bCompareItem && m_bIsEquippedItem)
					{
						int iCalc = m_cItemWrapper.sItem.saElementalDef[0] - m_cItemCompare.sItem.saElementalDef[0];
						SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

						if (iCalc != 0)
							AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
					}
				}
				if (m_cItemWrapper.sItem.saElementalDef[2])
				{
					AddString(0, "Fire:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", m_cItemWrapper.sItem.saElementalDef[2]), D3DCOLOR_ARGB(255, 240, 215, 150));

					//Mix Color
					if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_Flame)
						SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

					//Compare Item
					if (m_bCompareItem && m_bIsEquippedItem)
					{
						int iCalc = m_cItemWrapper.sItem.saElementalDef[2] - m_cItemCompare.sItem.saElementalDef[2];
						SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

						if (iCalc != 0)
							AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
					}
				}
				if (m_cItemWrapper.sItem.saElementalDef[3])
				{
					AddString(0, "Frost:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", m_cItemWrapper.sItem.saElementalDef[3]), D3DCOLOR_ARGB(255, 240, 215, 150));

					//Mix Color
					if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_Frost)
						SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

					//Compare Item
					if (m_bCompareItem && m_bIsEquippedItem)
					{
						int iCalc = m_cItemWrapper.sItem.saElementalDef[3] - m_cItemCompare.sItem.saElementalDef[3];
						SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

						if (iCalc != 0)
							AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
					}
				}
				if (m_cItemWrapper.sItem.saElementalDef[4])
				{
					AddString(0, "Lightning:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", m_cItemWrapper.sItem.saElementalDef[4]), D3DCOLOR_ARGB(255, 240, 215, 150));

					//Mix Color
					if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_Light)
						SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

					//Compare Item
					if (m_bCompareItem && m_bIsEquippedItem)
					{
						int iCalc = m_cItemWrapper.sItem.saElementalDef[4] - m_cItemCompare.sItem.saElementalDef[4];
						SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

						if (iCalc != 0)
							AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
					}
				}
				if (m_cItemWrapper.sItem.saElementalDef[5])
				{
					AddString(0, "Poison:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", m_cItemWrapper.sItem.saElementalDef[5]), D3DCOLOR_ARGB(255, 240, 215, 150));

					//Mix Color
					if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_Poison)
						SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

					//Compare Item
					if (m_bCompareItem && m_bIsEquippedItem)
					{
						int iCalc = m_cItemWrapper.sItem.saElementalDef[5] - m_cItemCompare.sItem.saElementalDef[5];
						SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

						if (iCalc != 0)
							AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
					}
				}
			}
			//HP Regen 生命回复
			if (m_cItemWrapper.sItem.fHPRegen && m_cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb)
			{
				AddString(0, "HP Regen:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.1f", m_cItemWrapper.sItem.fHPRegen), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_HPRegen)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.fHPRegen - m_cItemCompare.sItem.fHPRegen;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//MP Regen 魔法回复
			if (m_cItemWrapper.sItem.fMPRegen && m_cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb)
			{
				AddString(0, "MP Regen:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.1f", m_cItemWrapper.sItem.fMPRegen), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_MPRegen)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.fMPRegen - m_cItemCompare.sItem.fMPRegen;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//STM Regen 耐力回复
			if (m_cItemWrapper.sItem.fSPRegen && m_cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb)
			{
				AddString(0, "STM Regen:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.1f", m_cItemWrapper.sItem.fSPRegen), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_SPRegen)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.fSPRegen - m_cItemCompare.sItem.fSPRegen;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Add HP 增加生命
			if (m_cItemWrapper.sItem.fAddHP)
			{
				AddString(0, "Add HP:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.0f", m_cItemWrapper.sItem.fAddHP), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_HP)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.fAddHP - m_cItemCompare.sItem.fAddHP;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.0f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Add MP 增加魔法
			if (m_cItemWrapper.sItem.fAddMP)
			{
				AddString(0, "Add MP:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.0f", m_cItemWrapper.sItem.fAddMP), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_MP)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Aging Color
				if ((m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging) && 
					(m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Wand || 
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Phantom ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Bow ||
						m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Javelin))
					SetLineColor(D3DCOLOR_ARGB(255, 100, 230, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.fAddMP - m_cItemCompare.sItem.fAddMP;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.0f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Add STM 增加耐力
			if (m_cItemWrapper.sItem.fAddSP)
			{
				AddString(0, "Add STM:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.0f", m_cItemWrapper.sItem.fAddSP), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Mix Color
				if (m_cItemWrapper.sItem.eMixEffect & MIXEFFECT_SP)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 110, 255), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.fAddSP - m_cItemCompare.sItem.fAddSP;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.0f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Potion Storage 存放数量
			if (m_cItemWrapper.sItem.iPotionStorage)
			{
				AddString(0, "Pot Count:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.iPotionStorage), D3DCOLOR_ARGB(255, 240, 215, 150));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iPotionStorage - m_cItemCompare.sItem.iPotionStorage;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}

			// 时间道具

			//Req Level 需要等级
			if (m_cItemWrapper.sItem.iLevel)
			{
				AddString(0, "\nReq. Level:");
				AddString(1, FormatString("\n%d", m_cItemWrapper.sItem.iLevel));

				if (lpCurPlayer->smCharInfo.Level < m_cItemWrapper.sItem.iLevel)
				{
					SetLineColor(D3DCOLOR_ARGB(255, 255, 0, 0));
					m_bCantUseItem = TRUE;
				}
				else
					SetLineColor(D3DCOLOR_ARGB(255, 125, 120, 100));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iLevel - m_cItemCompare.sItem.iLevel;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc < 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Req Strenght 需要力量
			if (m_cItemWrapper.sItem.iStrength)
			{
				AddString(0, "Req. Strength:");
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.iStrength));

				if (lpCurPlayer->smCharInfo.Strength < m_cItemWrapper.sItem.iStrength)
				{
					SetLineColor(D3DCOLOR_ARGB(255, 255, 0, 0));
					m_bCantUseItem = TRUE;
				}
				else
					SetLineColor(D3DCOLOR_ARGB(255, 125, 120, 100));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iLevel - m_cItemCompare.sItem.iLevel;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc < 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Req Spirit 需要精神
			if (m_cItemWrapper.sItem.iSpirit)
			{
				AddString(0, "Req. Spirit:");
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.iSpirit));

				if (lpCurPlayer->smCharInfo.Spirit < m_cItemWrapper.sItem.iSpirit)
				{
					SetLineColor(D3DCOLOR_ARGB(255, 255, 0, 0));
					m_bCantUseItem = TRUE;
				}
				else
					SetLineColor(D3DCOLOR_ARGB(255, 125, 120, 100));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iSpirit - m_cItemCompare.sItem.iSpirit;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc < 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Req Talent 需要材质
			if (m_cItemWrapper.sItem.iTalent)
			{
				AddString(0, "Req. Talent:");
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.iTalent));

				if (lpCurPlayer->smCharInfo.Talent < m_cItemWrapper.sItem.iTalent)
				{
					SetLineColor(D3DCOLOR_ARGB(255, 255, 0, 0));
					m_bCantUseItem = TRUE;
				}
				else
					SetLineColor(D3DCOLOR_ARGB(255, 125, 120, 100));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iTalent - m_cItemCompare.sItem.iTalent;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc < 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Req Agility 需要敏捷
			if (m_cItemWrapper.sItem.iAgility)
			{
				AddString(0, "Req. Agility:");
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.iAgility));

				if (lpCurPlayer->smCharInfo.Dexterity < m_cItemWrapper.sItem.iAgility)
				{
					SetLineColor(D3DCOLOR_ARGB(255, 255, 0, 0));
					m_bCantUseItem = TRUE;
				}
				else
					SetLineColor(D3DCOLOR_ARGB(255, 125, 120, 100));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iAgility - m_cItemCompare.sItem.iAgility;
					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc < 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Req Health 需要体质
			if (m_cItemWrapper.sItem.iHealth)
			{
				AddString(0, "Req. Health:");
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.iHealth));

				if (lpCurPlayer->smCharInfo.Health < m_cItemWrapper.sItem.iHealth)
				{
					SetLineColor(D3DCOLOR_ARGB(255, 255, 0, 0));
					m_bCantUseItem = TRUE;
				}
				else
					SetLineColor(D3DCOLOR_ARGB(255, 125, 120, 100));

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.iHealth - m_cItemCompare.sItem.iHealth;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc < 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}

			//Spec
			/*if (m_cItemWrapper.sItem.eSpecialization)
			{
				EClassFlag e = static_cast<EClassFlag>(m_cItemWrapper.sItem.eSpecialization);
				AddString(0, FormatString("\n%s Spec", GetCharacterClassByFlag(e)));
				AddString(1, "\n");

				if (PLAYERDATA->iFlag == m_cItemWrapper.sItem.eSpecialization)
					SetLineColor(D3DCOLOR_ARGB(255, 255, 220, 0));
				else
					SetLineColor(D3DCOLOR_ARGB(255, 255, 0, 0));
			}*/
			//Spec ATK fMovementSpeed 特效移动速度
			if (m_cItemWrapper.sItem.sSpecData.iAttackSpeed)
			{
				AddString(0, "Attack Speed:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.sSpecData.iAttackSpeed));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.sSpecData.iAttackSpeed - m_cItemCompare.sItem.sSpecData.iAttackSpeed;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Spec Critical 特效必杀
			if (m_cItemWrapper.sItem.sSpecData.iCritical)
			{
				AddString(0, "Critical Rate:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d%%", m_cItemWrapper.sItem.sSpecData.iCritical));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.sSpecData.iCritical - m_cItemCompare.sItem.sSpecData.iCritical;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d%%)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Spec Defense 特效防御
			if (m_cItemWrapper.sItem.sSpecData.iDefenseRating)
			{
				AddString(0, "Defense:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.sSpecData.iDefenseRating));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.sSpecData.iDefenseRating - m_cItemCompare.sItem.sSpecData.iDefenseRating;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Spec fAbsorbRating 特效吸收
			if (m_cItemWrapper.sItem.sSpecData.fAbsorbRating)
			{
				AddString(0, "Absorption:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.1f", m_cItemWrapper.sItem.sSpecData.fAbsorbRating));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.sSpecData.fAbsorbRating - m_cItemCompare.sItem.sSpecData.fAbsorbRating;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0.0f)
						AddCompareString(FormatString("(%s%.1f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Spec Block
			if (m_cItemWrapper.sItem.sSpecData.fBlockRating)
			{
				AddString(0, "Block:", D3DCOLOR_ARGB(255, 245, 240, 218));

				if (fabs(m_cItemWrapper.sItem.sSpecData.fBlockRating - round(m_cItemWrapper.sItem.sSpecData.fBlockRating)) < FLT_MIN)
					AddString(1, FormatString("%.0f%%", round(m_cItemWrapper.sItem.sSpecData.fBlockRating)));
				else
					AddString(1, FormatString("%.1f%%", m_cItemWrapper.sItem.sSpecData.fBlockRating));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.sSpecData.fBlockRating - m_cItemCompare.sItem.sSpecData.fBlockRating;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f%%)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Spec MagicAPT
			if (m_cItemWrapper.sItem.sSpecData.fMagicMastery)
			{
				AddString(0, "Magic APT:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.0f", m_cItemWrapper.sItem.sSpecData.fMagicMastery));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.sSpecData.fMagicMastery - m_cItemCompare.sItem.sSpecData.fMagicMastery;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.0f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Spec fMovementSpeed
			if (m_cItemWrapper.sItem.sSpecData.fMovementSpeed)
			{
				AddString(0, "Speed:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.1f", m_cItemWrapper.sItem.sSpecData.fMovementSpeed));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.sSpecData.fMovementSpeed - m_cItemCompare.sItem.sSpecData.fMovementSpeed;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Spec Resistances
			{
				if (m_cItemWrapper.sItem.sSpecData.saElementalDef[0])
				{
					AddString(0, "Organic:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", m_cItemWrapper.sItem.sSpecData.saElementalDef));

					SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

					//Compare Item
					if (m_bCompareItem && m_bIsEquippedItem)
					{
						int iCalc = m_cItemWrapper.sItem.sSpecData.saElementalDef[0] - m_cItemCompare.sItem.sSpecData.saElementalDef[0];

						SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

						if (iCalc != 0)
							AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
					}
				}
				if (m_cItemWrapper.sItem.sSpecData.saElementalDef[2])
				{
					AddString(0, "Fire:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", m_cItemWrapper.sItem.sSpecData.saElementalDef[2]));

					SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

					//Compare Item
					if (m_bCompareItem && m_bIsEquippedItem)
					{
						int iCalc = m_cItemWrapper.sItem.sSpecData.saElementalDef[2] - m_cItemCompare.sItem.sSpecData.saElementalDef[2];

						SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

						if (iCalc != 0)
							AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
					}
				}
				if (m_cItemWrapper.sItem.sSpecData.saElementalDef[3])
				{
					AddString(0, "Frost:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", m_cItemWrapper.sItem.sSpecData.saElementalDef[3]));

					SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

					//Compare Item
					if (m_bCompareItem && m_bIsEquippedItem)
					{
						int iCalc = m_cItemWrapper.sItem.sSpecData.saElementalDef[3] - m_cItemCompare.sItem.sSpecData.saElementalDef[3];

						SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

						if (iCalc != 0)
							AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
					}
				}
				if (m_cItemWrapper.sItem.sSpecData.saElementalDef[4])
				{
					AddString(0, "Lightning:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", m_cItemWrapper.sItem.sSpecData.saElementalDef[4]));

					SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

					//Compare Item
					if (m_bCompareItem && m_bIsEquippedItem)
					{
						int iCalc = m_cItemWrapper.sItem.sSpecData.saElementalDef[4] - m_cItemCompare.sItem.sSpecData.saElementalDef[4];

						SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

						if (iCalc != 0)
							AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
					}
				}
				if (m_cItemWrapper.sItem.sSpecData.saElementalDef[5])
				{
					AddString(0, "Poison:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", m_cItemWrapper.sItem.sSpecData.saElementalDef[5]));

					SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

					//Compare Item
					if (m_bCompareItem && m_bIsEquippedItem)
					{
						int iCalc = m_cItemWrapper.sItem.sSpecData.saElementalDef[5] - m_cItemCompare.sItem.sSpecData.saElementalDef[5];

						SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

						if (iCalc != 0)
							AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
					}
				}
			}
			//Spec ATK Power
			if (m_cItemWrapper.sItem.sSpecData.iAttackPowerDiv.sMax)
			{
				AddString(0, "Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("LV/%d", m_cItemWrapper.sItem.sSpecData.iAttackPowerDiv.sMax));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.sSpecData.iAttackPowerDiv.sMax - m_cItemCompare.sItem.sSpecData.iAttackPowerDiv.sMax;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%sLV/%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 225, 30, 0) : D3DCOLOR_ARGB(255, 0, 130, 255));
				}
			}
			//Spec ATK Rtg
			if (m_cItemWrapper.sItem.sSpecData.iAttackRatingDiv)
			{
				AddString(0, "Attack Rate:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("LV/%d", m_cItemWrapper.sItem.sSpecData.iAttackRatingDiv));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.sSpecData.iAttackRatingDiv - m_cItemCompare.sItem.sSpecData.iAttackRatingDiv;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%sLV/%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 225, 30, 0) : D3DCOLOR_ARGB(255, 0, 130, 255));
				}
			}

			//Spec Range
			if (m_cItemWrapper.sItem.sSpecData.iAttackRange)
			{
				AddString(0, "Range:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%d", m_cItemWrapper.sItem.sSpecData.iAttackRange));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.sSpecData.iAttackRange - m_cItemCompare.sItem.sSpecData.iAttackRange;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%s%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Spec HP Boost
			if (m_cItemWrapper.sItem.sSpecData.iAddHPDiv)
			{
				AddString(0, "Max HP Boost:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("LV/%d", m_cItemWrapper.sItem.sSpecData.iAddHPDiv));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.sSpecData.iAddHPDiv - m_cItemCompare.sItem.sSpecData.iAddHPDiv;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%sLV/%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Spec MP Boost
			if (m_cItemWrapper.sItem.sSpecData.iAddMPDiv)
			{
				AddString(0, "Max MP Boost:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("LV/%d", m_cItemWrapper.sItem.sSpecData.iAddMPDiv));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					int iCalc = m_cItemWrapper.sItem.sSpecData.iAddMPDiv - m_cItemCompare.sItem.sSpecData.iAddMPDiv;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (iCalc != 0)
						AddCompareString(FormatString("(%sLV/%d)", iCalc > 0 ? "+" : "", iCalc), iCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}
			//Spec HP Regen
			if (m_cItemWrapper.sItem.sSpecData.fHPRegen && m_cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb)
			{
				AddString(0, "HP Regen:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.1f", m_cItemWrapper.sItem.sSpecData.fHPRegen));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.sSpecData.fHPRegen - m_cItemCompare.sItem.sSpecData.fHPRegen;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}

			//Spec MP Regen
			if (m_cItemWrapper.sItem.sSpecData.fMPRegen && m_cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb)
			{
				AddString(0, "MP Regen:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.1f", m_cItemWrapper.sItem.sSpecData.fMPRegen));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.sSpecData.fMPRegen - m_cItemCompare.sItem.sSpecData.fMPRegen;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}

			//Spec STM Regen
			if (m_cItemWrapper.sItem.sSpecData.fSPRegen && m_cItemWrapper.sBaseItemID.ToItemType() != ITEMTYPE_ForceOrb)
			{
				AddString(0, "STM Regen:", D3DCOLOR_ARGB(255, 245, 240, 218));
				AddString(1, FormatString("%.1f", m_cItemWrapper.sItem.sSpecData.fSPRegen));

				SetLineColor(D3DCOLOR_ARGB(255, 235, 190, 60), 1);

				//Compare Item
				if (m_bCompareItem && m_bIsEquippedItem)
				{
					float fCalc = m_cItemWrapper.sItem.sSpecData.fSPRegen - m_cItemCompare.sItem.sSpecData.fSPRegen;

					SetLineColor(D3DCOLOR_ARGB(255, 165, 157, 140), 0);

					if (fCalc != 0)
						AddCompareString(FormatString("(%s%.1f)", fCalc > 0 ? "+" : "", fCalc), fCalc > 0 ? D3DCOLOR_ARGB(255, 0, 130, 255) : D3DCOLOR_ARGB(255, 225, 30, 0));
				}
			}

			//Debug Item Info
			if (bShowChecksums)
			{
				AddString(0, "\n");
				AddString(1, "");

				AddString(0, FormatString("%d", m_cItemWrapper.sItem.iChk1));
				AddString(1, "");

				AddString(0, FormatString("%d", m_cItemWrapper.sItem.iChk2));
				AddString(1, "");
			}

			//Socket Item
			if (m_cItemWrapper.sItem.sSocketData[0].eSocketType != SOCKETTYPE_None)
			{
				AddString(0, "\n\n ");
				AddString(1, "\n\n ");
			}

			//Can't use Item?
			if (m_bCantUseItem)
			{
				m_cBackgroundColor1 = UI::Color(235, 10, 10, 10);
				m_cBackgroundColor2 = UI::Color(235, 75, 25, 25);
			}

			//Is Perfect Item?
			if (m_bIsPerfectItem)
			{
				m_cBackgroundColor1 = UI::Color(235, 45, 39, 27);
				m_cBackgroundColor2 = UI::Color(245, 24, 42, 56);
			}

			//Clear Text
			m_paSocketText[0][0]->SetText("");
			m_paSocketText[0][1]->SetText("");
			m_paSocketText[1][0]->SetText("");
			m_paSocketText[1][1]->SetText("");

			for (int i = 0; i < 2; i++)
			{
				if (m_cItemWrapper.sItem.sSocketData[i].eSocketType != SOCKETTYPE_None)
				{
					m_iSocketCount += 1;

					//Get Gem Image
					switch (m_cItemWrapper.sItem.sSocketData[i].eGemItem)
					{
					case GEMITEM_Ruby:
						m_iSocketGem[i] = 0;
						break;
					case GEMITEM_Topaz:
						m_iSocketGem[i] = 3;
						break;
					case GEMITEM_Emerald:
						m_iSocketGem[i] = 6;
						break;
					case GEMITEM_Aquamarine:
						m_iSocketGem[i] = 9;
						break;
					case GEMITEM_Amethyst:
						m_iSocketGem[i] = 12;
						break;
					}

					//Format Gem Type
					if (m_cItemWrapper.sItem.sSocketData[i].eGemType == GEMTYPE_Triangular)
						m_paSocketText[i][1]->SetText("+2");
					else if (m_cItemWrapper.sItem.sSocketData[i].eGemType == GEMTYPE_Square)
					{
						m_paSocketText[i][1]->SetText("+4");
						m_iSocketGem[i] += 1;
					}
					else if (m_cItemWrapper.sItem.sSocketData[i].eGemType == GEMTYPE_Marquise)
					{
						m_paSocketText[i][1]->SetText("+6");
						m_iSocketGem[i] += 2;
					}

					//Format Name and Stats of Gem
					switch (m_cItemWrapper.sItem.sSocketData[i].eGemItem)
					{
					case GEMITEM_Topaz:
						m_paSocketText[i][0]->SetColor(D3DCOLOR_ARGB(255, 255, 220, 0));
						m_paSocketText[i][0]->SetText("Topaz Gem");

						m_paSocketText[i][1]->AppendText(" Talent");
						break;
					case GEMITEM_Aquamarine:
						m_paSocketText[i][0]->SetColor(D3DCOLOR_ARGB(255, 0, 150, 255));
						m_paSocketText[i][0]->SetText("Aquamarine Gem");

						m_paSocketText[i][1]->AppendText(" Spirit");
						break;
					case GEMITEM_Ruby:
						m_paSocketText[i][0]->SetColor(D3DCOLOR_ARGB(255, 180, 25, 25));
						m_paSocketText[i][0]->SetText("Ruby Gem");

						m_paSocketText[i][1]->AppendText(" Strenght");
						break;
					case GEMITEM_Amethyst:
						m_paSocketText[i][0]->SetColor(D3DCOLOR_ARGB(255, 150, 5, 235));
						m_paSocketText[i][0]->SetText("Amethyst Gem");

						m_paSocketText[i][1]->AppendText(" Health");
						break;
					case GEMITEM_Emerald:
						m_paSocketText[i][0]->SetColor(D3DCOLOR_ARGB(255, 0, 170, 10));
						m_paSocketText[i][0]->SetText("Emerald Gem");

						m_paSocketText[i][1]->AppendText(" Agility");
						break;
					}
				}
			}

			//Not have description or stats? So only show the Title of Item
			if (m_vLeftText.size() < 3)
			{
				m_vLeftText.erase(m_vLeftText.begin() + 1);
				m_vRightText.erase(m_vRightText.begin() + 1);
			}
		}
		void Window::Render(int iX, int iY, int iWidth, int iHeight, int iSourceX, int iSourceY)
		{
			if (m_bSelect == FALSE)
				return;

			iX = (m_cItemWrapper.sPosition.iX + (m_cItemWrapper.iWidth / 2)) - 90;
			iY = (m_cItemWrapper.sPosition.iY - (m_vLeftText.size() * 14)) - 14;

			int iSocketHeightExtra = 0;

			for (int i = 0; i < 2; i++)
			{
				if (m_cItemWrapper.sItem.sSocketData[i].eSocketType)
					iSocketHeightExtra += i > 0 ? 36 : 8;
			}

			//Set iWidth and iHeight of Box
			int iItemInfoBoxWidth = 200 - 16;
			int iItemInfoBoxHeight = (14 * m_vLeftText.size());

			//iItemSlot of box is out the window?
			iX = iX < 0 ? 0 : iX;
			iY = iY < 0 ? 16 : iY;

			if (iX + iItemInfoBoxWidth > (int)RESOLUTION_WIDTH)
				iX -= ((iX + iItemInfoBoxWidth) - (int)RESOLUTION_WIDTH) + 16;

			//Update Item Info Box Width and Height
			iItemInfoBoxWidth += 10;
			iItemInfoBoxHeight += 20 + iSocketHeightExtra;

			//Draw Item Info Box Background
			DrawItemInfoBox(iX, iY, iItemInfoBoxWidth, iItemInfoBoxHeight);

			//Drawing Border
			UI::ImageRender::Render(m_pImageBorderLeftTop, iX, iY - 10, m_pImageBorderLeftTop->GetWidth(), m_pImageBorderLeftTop->GetHeight(), -1);
			UI::ImageRender::Render(m_pImageBorderTop, iX + m_pImageBorderLeftTop->GetWidth(), iY - 10, iItemInfoBoxWidth - m_pImageBorderLeftTop->GetWidth() - m_pImageBorderRightTop->GetWidth(), m_pImageBorderTop->GetHeight(), -1);
			UI::ImageRender::Render(m_pImageBorderRightTop, iX + m_pImageBorderLeftTop->GetWidth() + iItemInfoBoxWidth - m_pImageBorderLeftTop->GetWidth() - m_pImageBorderRightTop->GetWidth(), iY - 10, m_pImageBorderRightTop->GetWidth(), m_pImageBorderRightTop->GetHeight(), -1);
			UI::ImageRender::Render(m_pImageBorderLeft, iX, iY - 10 + m_pImageBorderLeftTop->GetHeight(), m_pImageBorderLeft->GetWidth(), iItemInfoBoxHeight - m_pImageBorderLeftTop->GetWidth() - m_pImageBorderLeftBottom->GetWidth(), -1);
			UI::ImageRender::Render(m_pImageBorderRight, iX + iItemInfoBoxWidth - m_pImageBorderRight->GetWidth(), iY - 10 + m_pImageBorderLeftTop->GetHeight(), m_pImageBorderRight->GetWidth(), iItemInfoBoxHeight - m_pImageBorderLeftTop->GetWidth() - m_pImageBorderLeftBottom->GetWidth(), -1);
			UI::ImageRender::Render(m_pImageBorderLeftBottom, iX, iY - 10 + iItemInfoBoxHeight - m_pImageBorderLeftBottom->GetHeight(), m_pImageBorderLeftBottom->GetWidth(), m_pImageBorderLeftBottom->GetHeight(), -1);
			UI::ImageRender::Render(m_pImageBorderRightBottom, iX + iItemInfoBoxWidth - m_pImageBorderRightBottom->GetWidth(), iY - 10 + iItemInfoBoxHeight - m_pImageBorderRightBottom->GetHeight(), m_pImageBorderRightBottom->GetWidth(), m_pImageBorderRightBottom->GetHeight(), -1);
			UI::ImageRender::Render(m_pImageBorderBottom, iX + m_pImageBorderLeftBottom->GetWidth(), iY - 10 + iItemInfoBoxHeight - m_pImageBorderBottom->GetHeight(), iItemInfoBoxWidth - m_pImageBorderLeftTop->GetWidth() - m_pImageBorderRightTop->GetWidth(), m_pImageBorderBottom->GetHeight(), -1);

			//Render Item Type Icon
			if (m_cItemWrapper.IsOneHandedWeapon())
			{
				m_pImageIconWeaponOneHand ? UI::ImageRender::Render(m_pImageIconWeaponOneHand, iX + iItemInfoBoxWidth - 30, iY, 18, 16, 0, 0, -1) : 0;
			}
			else if (m_cItemWrapper.IsTwoHandedWeapon())
			{
				m_pImageIconWeaponTwoHand ? UI::ImageRender::Render(m_pImageIconWeaponTwoHand, iX + iItemInfoBoxWidth - 30, iY, 18, 16, 0, 0, -1) : 0;
			}
			else if (m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Armor)
			{
				m_pImageIconArmor ? UI::ImageRender::Render(m_pImageIconArmor, iX + iItemInfoBoxWidth - 30, iY, 18, 16, 0, 0, -1) : 0;
			}
			else if (m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Robe)
			{
				m_pImageIconRobe ? UI::ImageRender::Render(m_pImageIconRobe, iX + iItemInfoBoxWidth - 30, iY, 18, 16, 0, 0, -1) : 0;
			}
			else if (m_cItemWrapper.sBaseItemID.ToItemType() == ITEMTYPE_Orb)
			{
				m_pImageIconRobe ? UI::ImageRender::Render(m_pImageIconRobe, iX + iItemInfoBoxWidth - 30, iY, 18, 16, 0, 0, -1) : 0;
			}

			//Render Compare Text
			if (m_bIsEquippedItem && m_bCompareItem)
			{
				for (UINT i = 0; i < m_vRowCompare.size(); i++)
				{
					auto pLeftText = m_vLeftText[m_vRowCompare[i] - 1];
					auto pRightText = m_vRightText[m_vRowCompare[i] - 1];
					auto pCompareText = m_vCompareText[i];

					//Load Texts
					pCompareText->SetNoClip(TRUE);
					pCompareText->SetHorizontalAlign(ALIGN_Left);
					pCompareText->SetBox(Rectangle2D(pLeftText->GetWidthText() + pRightText->GetWidthText() + 22, 0 + (14 * (m_vRowCompare[i] - 1)), 180, iHeight));

					//Render Texts
					pCompareText->Render(iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
				}
			}

			//Render Text
			if (m_vLeftText.size() == m_vRightText.size())
			{
				for (size_t i = 0; i < m_vLeftText.size(); i++)
				{
					auto pLeftText = m_vLeftText[i];
					auto pRightText = m_vRightText[i];

					//Load Texts
					pLeftText->SetMultiLine(TRUE);
					pLeftText->SetNoClip(TRUE);

					pRightText->SetNoClip(TRUE);

					pLeftText->SetHorizontalAlign(ALIGN_Left);
					pLeftText->SetBox(Rectangle2D(15, 0 + (14 * i), 180, iHeight));

					pRightText->SetHorizontalAlign(ALIGN_Left);
					pRightText->SetBox(Rectangle2D(pLeftText->GetWidthText() + 20, 0 + (14 * i), 180, iHeight));

					//Render Texts
					pLeftText->Render(iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
					pRightText->Render(iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
				}
			}

			//Render Aging Bar
			if (m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Aging)
			{
				int iYExtra = 0;

				if ((m_bCompareItem && m_bIsEquippedItem) || m_bIsPerfectItem)
					iYExtra = 15;

				if (m_cItemWrapper.sItem.sMatureBar.sMax)
				{
					int iBarLenght = (int)((float)((float)125 * (((float)m_cItemWrapper.sItem.sMatureBar.sMin / (float)m_cItemWrapper.sItem.sMatureBar.sMax))));

					if (m_pImageAgingBar)
						UI::ImageRender::Render(m_pImageAgingBar, (iX + 90) - (130 >> 1), iY + 26 + iYExtra, 130, 19, 0, 0, -1);

					if (m_pImageAgingBarGage)
						UI::ImageRender::Render(m_pImageAgingBarGage, ((iX + 90) - (125 >> 1)) - 1, iY + 33 + iYExtra, iBarLenght, 4, 0, 0, -1);
				}
				else
				{
					if (m_pImageAgingBarNum)
						UI::ImageRender::Render(m_pImageAgingBarNum, (iX + 90) - (26 >> 1), iY + 26 + iYExtra, 26, 19, 0, 0, -1);
				}

				//Render Aging Text
				if (m_pTextAging)
				{
					m_pTextAging->SetNoClip(TRUE);
					m_pTextAging->SetText(FormatString("+%d", m_cItemWrapper.sItem.sAgeLevel));
					m_pTextAging->SetBox(Rectangle2D(79, 26 + iYExtra, 23, 18));
					m_pTextAging->SetHorizontalAlign(ALIGN_Center);
					m_pTextAging->SetVerticalAlign(ALIGN_Center);
					m_pTextAging->Render(iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);
				}
			}

			//Render Socket System
			if (iSocketHeightExtra)
			{
				LINEHANDLE->MakeLine()->Draw(Rectangle2D(iX + 15, iY + iItemInfoBoxHeight - 30, 150, 1), D3DCOLOR_ARGB(255, 160, 130, 105));

				for (int i = 0; i < m_iSocketCount; i++)
				{
					//Render Socket Info
					m_paSocketText[i][0]->SetNoClip(TRUE);
					m_paSocketText[i][0]->SetBox(Rectangle2D(56, iItemInfoBoxHeight - 22 + (i * 38), 120, 18));
					m_paSocketText[i][0]->SetHorizontalAlign(ALIGN_Left);
					m_paSocketText[i][0]->Render(iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);

					m_paSocketText[i][1]->SetNoClip(TRUE);
					m_paSocketText[i][1]->SetBox(Rectangle2D(56, iItemInfoBoxHeight - 8 + (i * 38), 120, 18));
					m_paSocketText[i][1]->SetHorizontalAlign(ALIGN_Left);
					m_paSocketText[i][1]->Render(iX, iY, RESOLUTION_WIDTH, RESOLUTION_HEIGHT, 0, 0);

					//Render Socket Background
					if (m_pImageSocketBackground)
						UI::ImageRender::Render(m_pImageSocketBackground, iX + 17, iY + iItemInfoBoxHeight - 18 + (i * 38), 27, 27, -1);

					//Render Socket Type
					for (int k = 1; k < SOCKETTYPE_Count; k++)
					{
						if (m_cItemWrapper.sItem.sSocketData[i].eSocketType == (ESocketType)k)
						{
							UI::ImageRender::Render(m_paSocket[k - 1], iX + 16, iY + iItemInfoBoxHeight - 19 + (i * 38), 29, 29, -1);
							break;
						}
					}

					//Render Socket Gem
					if (m_cItemWrapper.sItem.sSocketData[i].eGemItem != GEMITEM_None && m_paSocketGems[m_iSocketGem[i]])
						UI::ImageRender::Render(m_paSocketGems[m_iSocketGem[i]], iX + 19, iY + iItemInfoBoxHeight - 15 + (i * 38), 22, 22, -1);
				}
			}
		}
		void Window::Update(float fTime)
		{
			if (m_bIsPerfectItem)
			{
				if (m_bFadeToColor)
				{
					m_fProgress += 0.01f;

					if (m_fProgress > 1.0f)
					{
						m_bFadeToColor = FALSE;
						m_fProgress = 1.0f;
					}
				}
				else if (!m_bFadeToColor)
				{
					m_fProgress -= 0.005f;

					if (m_fProgress < 0.0f)
					{
						m_bFadeToColor = TRUE;
						m_fProgress = 0.0f;
					}
				}

				m_cBackgroundColor2 = UI::Color(245, 9 + (int)(15.0f * m_fProgress), 23 + (int)(19.0f * m_fProgress), 22 + (int)(34.0f * m_fProgress));
			}
		}
		BOOL Window::IsSameItem(ItemData *pcItemData)
		{
			return ((m_cItemWrapper.sItem.iChk1 == pcItemData->sItem.iChk1) && (m_cItemWrapper.sItem.iChk2 == pcItemData->sItem.iChk2) && (m_cItemWrapper.sPosition.Equals(&pcItemData->sPosition))) ? TRUE : FALSE;
		}
		void Window::FormatItemInfo()
		{
			if (m_cItemWrapper.IsBeginnerSet())
			{
				AddString(0, "Quest Item", D3DCOLOR_ARGB(255, 132, 50, 254));
				AddString(1, "");
			}
			if (m_cItemWrapper.IsBoss())
			{
				AddString(0, "Boss Item", D3DCOLOR_RGBA(0, 128, 128, 255));
				AddString(1, "");
			}

			if (m_cItemWrapper.sItem.eCraftType == ITEMCRAFTTYPE_Mixing)
			{
				switch (m_cItemWrapper.sItem.eMixTypeName)
				{
				case MIXTYPENAME_Devine:
					AddString(0, "Devine Mix", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Celesto:
					AddString(0, "Celesto Mix", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Mirage:
					AddString(0, "Mirage Mix", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Inferna:
					AddString(0, "Inferna Mix", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Enigma:
					AddString(0, "Enigma Mix", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Bellum:
					AddString(0, "Bellum Mix", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Oredo:
					AddString(0, "Oredo Mix", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Devine2:
					AddString(0, "Devine Mix #2", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Celesto2:
					AddString(0, "Celesto Mix #2", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Mirage2:
					AddString(0, "Mirage Mix #2", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Inferna2:
					AddString(0, "Inferna Mix #2", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Enigma2:
					AddString(0, "Enigma Mix #2", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Bellum2:
					AddString(0, "Bellum Mix #2", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				case MIXTYPENAME_Oredo2:
					AddString(0, "Oredo Mix #2", D3DCOLOR_ARGB(255, 170, 160, 170));
					AddString(1, "");
					break;
				}
			}

			if (m_cItemWrapper.sItem.bPerfectItem)
			{
				AddString(0, "Perfect Item", D3DCOLOR_RGBA(0, 191, 255, 255));
				AddString(1, "");
			}
			if (m_bIsEquippedItem && m_bCompareItem)
			{
				AddString(0, "Equipped Item", D3DCOLOR_RGBA(70, 125, 80, 255));
				AddString(1, "");
			}

			/*if (m_cItemWrapper.eGender == EGender_Male)
			{
				AddString(0, "Male Item", D3DCOLOR_RGBA(255, 155, 50, 255));
				AddString(1, "");
			}
			else if (m_cItemWrapper.eGender == EGender_Female)
			{
				AddString(0, "Female Item", D3DCOLOR_RGBA(255, 155, 50, 255));
				AddString(1, "");
			}*/

			//Break Line
			AddString(0, " ");
			AddString(1, " ");

			EItemID eItemID = m_cItemWrapper.sBaseItemID.ToItemID();
			{
				switch (eItemID)
				{
				case ITEMID_LightBlueRune:
					AddString(0, "Used to Craft Tulla Amulet", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_DarkRedRune:
					AddString(0, "Used to Craft Draxos Boots", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_LightGreenRune:
					AddString(0, "Used to Craft Abyss Ring", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_BrilliantStone:
					AddString(0, "Exchange on Ihin\nBellatra Event NPC", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_BlueStone:
					AddString(0, "Reset all stat points.", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_RedStone:
					AddString(0, "Reset all Skills points.", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_GreenStone:
					AddString(0, "Reset all Skills and\n Stats points.", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_FatalEdge:
					AddString(0, "+10% Final Damage\nOnly works on SoD", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_AvertScroll:
					AddString(0, "+10% of Absorption\nOnly works on SoD", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MatureStoneA:
					AddString(0, "Mature the aging bar of \nequipped Weapon \nto 100% instantly", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MatureStoneB:
					AddString(0, "Mature the aging bar of \nequipped Orb or Shield \nto 100% instantly", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MatureStoneC:
					AddString(0, "Mature the aging bar of \nequipped Robe or Armor \nto 100% instantly", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_SapphireStone:
					AddString(0, "Train all skills from T1\nto T3 to 100% instantly", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_RubyStone:
					AddString(0, "Train all skills from T1\nto T3 to 10%\nReq. Level: 1-95", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_ExpUp1H:
				case ITEMID_ExpUp24H:
				case ITEMID_ExpUp48H:
				case ITEMID_ExpUp72H:
					AddString(0, "30% Additional Experience", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_HPUp12H:
					AddString(0, "+10 HP Regen", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MPUp12H:
					AddString(0, "+10 Mana Regen", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MPDown12H:
					AddString(0, "Reduces 25% Mana Usage", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_SPDown12H:
					AddString(0, "Reduces 25% Stamina Usage", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_WitchHat:
				case ITEMID_CartolaHat:
					AddString(0, "Halloween Item", D3DCOLOR_ARGB(255, 180, 100, 175));
					AddString(1, "");
					AddString(0, "+10 HP Regen\n+10 Add HP", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_KingStone:
					if (m_cItemWrapper.sItem.eMixTypeName == ITEMCRAFTTYPE_TGFKingFury)
					{
						AddString(0, "King Fury Item", D3DCOLOR_ARGB(255, 255, 248, 0));
						AddString(1, "");
					}
					else if (m_cItemWrapper.sItem.eMixTypeName == ITEMCRAFTTYPE_TGFLordBabel)
					{
						AddString(0, "Lord Babel Item", D3DCOLOR_ARGB(255, 255, 248, 0));
						AddString(1, "");
					}
					AddString(0, FormatString("Killed in %d Minute%s", m_cItemWrapper.sItem.tTime, m_cItemWrapper.sItem.tTime > 1 ? "s" : ""), D3DCOLOR_ARGB(255, 125, 180, 175));
					AddString(1, "");
					break;
				case ITEMID_ThirdEye1H:
				case ITEMID_ThirdEye24H:
				case ITEMID_ThirdEye48H:
				case ITEMID_ThirdEye72H:
					AddString(0, "One Additional Drop", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_PhoenixEgg:
					AddString(0, "Summons a random \nPhoenix Pet", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_GravityStone72H:
					AddString(0, "Gives +1000 Weight", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_TeleportCore:
					AddString(0, "Teleport to a field", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_AgingStone:
					AddString(0, "Decrease 30% chance\nof fail aging", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_CopperOre:
					AddString(0, "Prevents Items \nfrom breaking", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_CleanItem:
					AddString(0, "Cleans Mix/Age \nfrom an item", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_Fireworks:
					AddString(0, "Lets Celebrate!", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_HairPotionA:
				case ITEMID_HairPotionB:
				case ITEMID_HairPotionC:
				case ITEMID_HairPotionD:
				case ITEMID_HairPotionE:
				case ITEMID_HairPotionF:
				case ITEMID_HairPotionG:
				case ITEMID_HairPotionH:
				case ITEMID_HairPotionI:
				case ITEMID_HairPotionJ:
				case ITEMID_HairPotionK:
				case ITEMID_HairPotionL:
				case ITEMID_HairPotionM:
				case ITEMID_HairPotionN:
				case ITEMID_HairPotionO:
				case ITEMID_HairPotionP:
				case ITEMID_HairPotionQ:
				case ITEMID_HairPotionR:
				case ITEMID_HairPotionS:
					AddString(0, "Change your hair!", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_BigHeadHappyness:
					AddString(0, "Add +50 Attack Rating", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_BigHeadSadness:
					AddString(0, "Add +10 MP Regen/MP", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_BigHeadShyness:
					AddString(0, "Add +100 Defense", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_BigHeadLove:
					AddString(0, "Add +10 HP Regen/HP", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_BigHeadAngry:
					AddString(0, "Add +50 HP/MP/STM", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_BigHeadSurprised:
					AddString(0, "Add +2% Block Rating", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_BigHeadSensual:
					AddString(0, "Add +2 Critical", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_TopazStone:
					AddString(0, "Mature the equipped\nitem to 100% instantly", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_TurquoiseStone:
					AddString(0, "A weak mature stone", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_EmeraldStone:
					AddString(0, "Trains 10% \nAll skills T1~T3", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_SheepHat:
					AddString(0, "+150 Defense", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_GiraffeHat:
					AddString(0, "Add +75 Attack Rating", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_SoccerHat:
					AddString(0, "Add +2 Move Speed", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_XMasRedHat:
					AddString(0, "Add +50 MP/STM", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_RicartenCore:
					AddString(0, "Teleport to Ricarten Town", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_NaviskoCore:
					AddString(0, "Teleport to Navisko Town", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_AtlantisCore:
					AddString(0, "Teleport to Atlantis Town", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_PillaiCore:
					AddString(0, "Teleport to Phillai Town", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_UnionCore:
					AddString(0, "Teleport to a Player", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					if (m_cItemWrapper.sItem.szItemName[lstrlenA(m_cItemWrapper.sItem.szItemName) + 1] != 0)
					{
						AddString(0, FormatString("%s", m_cItemWrapper.sItem.szItemName + lstrlenA(m_cItemWrapper.sItem.szItemName) + 1), D3DCOLOR_ARGB(255, 110, 165, 250));
						AddString(1, "");
					}
					break;
				case ITEMID_MightPotionFighter:
					AddString(0, "5% Damage Boost\nagainst Fighter\n", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MightPotionMechanician:
					AddString(0, "5% Damage Boost\nagainst Mechanician\n", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MightPotionPikeman:
					AddString(0, "5% Damage Boost\nagainst Pikeman\n", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MightPotionArcher:
					AddString(0, "5% Damage Boost\nagainst Archer\n", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MightPotionKnight:
					AddString(0, "5% Damage Boost\nagainst Knight\n", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MightPotionAtalanta:
					AddString(0, "5% Damage Boost\nagainst Atalanta\n", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MightPotionMagician:
					AddString(0, "5% Damage Boost\nagainst Magician\n", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_MightPotionPriestess:
					AddString(0, "5% Damage Boost\nagainst Priestess\n", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_DeadlyEdge:
					AddString(0, "Add critical rating by +5% \nin PVP areas", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_AvailOfEvade:
					AddString(0, "Add evasion rating by +5% \nin PVP areas", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_BolsterRecovery:
					AddString(0, "HP MP SP Recovery\nfor party", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_Restoration:
					AddString(0, "Resurrection Scroll", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");
					break;
				case ITEMID_DefianceStoneFire:
					AddString(0, "Decrease Damage by 50% \nof Fire Crystal Tower", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Fire Attribute", D3DCOLOR_ARGB(255, 255, 0, 0));
					AddString(1, "");
					break;
				case ITEMID_DefianceStoneIce:
					AddString(0, "Decrease Damage by 50% \nof Ice Crystal Tower", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Ice Attribute", D3DCOLOR_ARGB(255, 255, 0, 0));
					AddString(1, "");
					break;
				case ITEMID_DefianceStoneLight:
					AddString(0, "Decrease Damage by 50% \nof Lightning Crystal Tower", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Duration: 60seconds", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, "");

					AddString(0, "Light Attribute", D3DCOLOR_ARGB(255, 255, 0, 0));
					AddString(1, "");
					break;
				case ITEMID_LucidyForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 2), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 0), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 500), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_SerenoForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 4), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 0), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 500), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_FadeoForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 7), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 0), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 500), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_SparkyForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 10), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 0), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 500), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_RaidentForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 15), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 0), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 700), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_TransparoForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 25), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 0), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 900), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_MurkyForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 40), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 10), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 1800), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_DevineForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 60), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 10), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 2400), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_CelestoForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 80), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 10), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 3600), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_MirageForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 100), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 10), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 4800), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_InfernaForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 120), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 10), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 6000), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_EnigmaForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 140), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 10), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 7200), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_BellumForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 160), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 10), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 8400), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_OredoForce:
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d", 180), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Add Attack Power:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%d%%", 10), D3DCOLOR_ARGB(255, 240, 215, 150));
					AddString(0, "Duration:", D3DCOLOR_ARGB(255, 245, 240, 218));
					AddString(1, FormatString("%ds", 9600), D3DCOLOR_ARGB(255, 240, 215, 150));
					break;
				case ITEMID_SoccerShirt:
					AddString(0, "Won't work with costumes", D3DCOLOR_ARGB(255, 255, 0, 0));
					AddString(1, "");

					AddString(0, " ");
					AddString(1, " ");
					break;
				}
			}
		}
		void Window::DrawItemInfoBox(int iX, int iY, int iWidth, int iHeight)
		{
			//Draw Item Info Box Background
			if (m_pRenderTargetMask)
			{
				if (GRAPHICDEVICE->SetRenderTarget(m_pRenderTargetMask))
				{
					//Clear Render Target
					GRAPHICDEVICE->Clear(TRUE, TRUE, FALSE);

					//Draw Background
					GRAPHICENGINE->DrawRectangle(Rectangle2D(0, 0, iWidth, iHeight), m_cBackgroundColor1.Get(), m_cBackgroundColor2.Get());

					//Drawing Mask Border
					UI::ImageRender::Render(m_pImageMaskLeftTop, 0, 0, m_pImageMaskLeftTop->GetWidth(), m_pImageMaskLeftTop->GetHeight(), -1);
					UI::ImageRender::Render(m_pImageMaskRightTop, iWidth - m_pImageMaskRightTop->GetWidth(), 0, m_pImageMaskRightTop->GetWidth(), m_pImageMaskRightTop->GetHeight(), -1);
					UI::ImageRender::Render(m_pImageMaskLeftBottom, 0, iHeight - m_pImageMaskLeftBottom->GetHeight(), m_pImageMaskLeftBottom->GetWidth(), m_pImageMaskLeftBottom->GetHeight(), -1);
					UI::ImageRender::Render(m_pImageMaskRightBottom, iWidth - m_pImageMaskRightTop->GetWidth(), iHeight - m_pImageMaskLeftBottom->GetHeight(), m_pImageMaskRightBottom->GetWidth(), m_pImageMaskRightBottom->GetHeight(), -1);

					//Back Old Render Target
					GRAPHICDEVICE->UnsetRenderTarget();
				}

				//Set Sprite Effect...
				UI::ImageRender::SetEffect(m_pEffectMask);
				m_pEffectMask->SetTechnique("Mask");

				if (m_pEffectMask->Begin() >= 0)
				{
					//Render the Render Target and mask it on effect
					UI::ImageRender::Render(m_pRenderTargetMask->GetTexture(), iX, iY - 10, m_pRenderTargetMask->GetWidth(), m_pRenderTargetMask->GetHeight(), 0, 0, D3DCOLOR_XRGB(255, 255, 255), FALSE);

					m_pEffectMask->End();
				}
				UI::ImageRender::SetEffect(NULL);
			}
		}
	}
}