#pragma once

class CItemInfoBox
{
public:
	CItemInfoBox();
	virtual ~CItemInfoBox();

	void Init();

	void SetCompareItem(const ItemData * pcCompareItemData, BOOL bEquippedItem);
	void ClearCompareItem();

	void PrepareShowItem(ItemData * pcItemData, BOOL bShowBuyPrice, BOOL bShowSellPrice, BOOL bShowChecksums);

	void Render();

	void Update(float fTime);
protected:
	void FormatItemInfo(ItemData * pcItemData);
	void FormatItemTimeInfo(ItemData * pcItemData);
	void AddString(int iSide, const std::string & strString, DWORD dwColor = -1, BOOL bBold = FALSE);
	void AddCompareString(const std::string & strString, DWORD dwColor = -1);
	void AppendLineText(std::string str, int iSide = -1, int iLineCount = -1);
	void SetLineColor(DWORD dwColor, int iSide = -1, int iLineCount = -1);
	void DrawItemInfoBox(int iX, int iY, int iWidth, int iHeight);
private:
	//Images Box
	UI::LPIMAGE m_pImageMaskLeftTop;
	UI::LPIMAGE	m_pImageMaskRightTop;
	UI::LPIMAGE	m_pImageMaskLeftBottom;
	UI::LPIMAGE	m_pImageMaskRightBottom;

	UI::LPIMAGE	m_pImageBorderLeftTop;
	UI::LPIMAGE	m_pImageBorderRightTop;
	UI::LPIMAGE	m_pImageBorderTop;
	UI::LPIMAGE	m_pImageBorderLeftBottom;
	UI::LPIMAGE	m_pImageBorderRightBottom;
	UI::LPIMAGE	m_pImageBorderBottom;
	UI::LPIMAGE	m_pImageBorderLeft;
	UI::LPIMAGE	m_pImageBorderRight;

	//Aging
	UI::LPIMAGE	m_pImageAgingBar;
	UI::LPIMAGE	m_pImageAgingBarGage;
	UI::LPIMAGE	m_pImageAgingBarNum;

	//Icons
	UI::LPIMAGE	m_pImageIconArmor;
	UI::LPIMAGE	m_pImageIconRobe;
	UI::LPIMAGE	m_pImageIconWeaponOneHand;
	UI::LPIMAGE	m_pImageIconWeaponTwoHand;

	//Socket
	UI::LPIMAGE	m_pImageSocketBackground;
	UI::LPIMAGE	m_paSocket[6];
	UI::LPIMAGE	m_paSocketGems[15];

	DX::LPRENDERTARGET m_pRenderTargetMask = NULL;
	DX::LPEFFECT m_pEffectMask;

	int	m_iSocketGem[2];
	int	m_iSocketCount = 0;

	BOOL m_bFadeToColor = TRUE;
	float m_fProgress = 0.0f;

	std::vector<UI::LPTEXT> m_vLeftText, m_vRightText, m_vCompareText;
	std::vector<int> m_vRowCompare;
	UI::LPTEXT m_pTextAging, m_paSocketText[2][2];

	BOOL m_bCompareItem = FALSE;
	BOOL m_bIsEquippedItem = FALSE;
	BOOL m_bCantUseItem = FALSE;
	BOOL m_bIsPerfectItem = FALSE;

	BOOL m_bIsViewingPerfectItem = FALSE;

	ItemData m_cItemWrapper;
	ItemData m_cItemCompare;

	UI::Color m_cBackgroundColor1;
	UI::Color m_cBackgroundColor2;
};