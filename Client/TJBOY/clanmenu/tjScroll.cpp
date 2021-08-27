#include "StdAfx.h"
#define TJSCROLL_CPP

#include "tjScroll.h"

extern int TJwheel; //ktj : �ٵ���Ÿ(tjclan.cpp)


int TJBscrollWheel(int wheel)		//�����:1  �̻���� 0
{
	if(wheel != 0) {			//ktj : wheel>0 �� ������ ������  wheel<0 �� �ڷ� ������
		if(tscr.lifef || tscr_CL.lifef ||tscr_Guide.lifef) {
			TJwheel = wheel;

			return 1;
		}
	}

	return 0;
}

void TJBscrollWheelClear()		//hoparty.cpp ������ ��Ÿ�Լ��� ����ϱ�
{
	TJwheel = 0;
	tscr.lifef = 0;

}

void TJBscrollWheelClear_ChatL()		//hoparty.cpp�� ���Ű�����Լ�
{
	TJwheel = 0;
	tscr_CL.lifef = 0;
	void chatList_Main_CHATLIST_END();
	chatList_Main_CHATLIST_END();
}

void TJBscrollWheelClear_Guide()
{
	TJwheel = 0;
	tscr_Guide.lifef = 0;
}

tSCROLL::tSCROLL()
{
}

tSCROLL::~tSCROLL()
{
}

//��ũ���� life����
void tSCROLL::Init(int flag)
{
	lifef= flag;
}


//t, b:��ũ���� top, bottom,    scrLineSu:��ũ���� ������ �ѱ���    viewLineSu: ��ȭ�鿡 ���̴¶����� ����
void tSCROLL::Init(int t, int b, int scrLineSu, int ViewLineSu)
{
	top = t; 
	bot = b;
	allLineSu = scrLineSu;
	viewLineSu = ViewLineSu;
	
	int scrLen = bot-top;					//���� �ѱ���
	step   = scrLen / (scrLineSu+1);		//�Ѱ��� ������ �ʿ��� ����

	lifef = 1;
}

int tSCROLL::topScrollLineNum(int point)
{
	if(lifef == 0) return -1;

	int curP = point - top;					//���� ��ũ�Ѷ��ξ��� ��ġ
	int currentScrllLineNum = curP/step;	//��ũ�Ѷ����Ѱ����� ��ġ�� �����ش�.
	if(currentScrllLineNum > allLineSu )
		currentScrllLineNum = allLineSu;


	//�ǾƷ���ũ�� �κ��� ���� �ö��� �ʰ� ���´�.
	int i = currentScrllLineNum + viewLineSu;
	if(i>allLineSu) {
		currentScrllLineNum  = allLineSu-viewLineSu;
	}
	
	return currentScrllLineNum;			//���� ȭ�鿡 ���� ������ ���ι�ȣ����(���� �����ؾ���)
}



int tSCROLL::ret_WHEELpoint(int wheelN, int point)
{
	if(lifef == 0) return point;

	if(wheelN<0) {				//�Ʒ��� ������
		point += step;
		if( (bot-9)<point )
			point = bot-9;
	}

	if(wheelN>0) {				//������ ������
		point -= step;

		if(top>point )
			point = top;
	}

	return point;			//�ٿ����θ�ŭ�� ����Ʈ��������
}