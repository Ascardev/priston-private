#include "StdAfx.h"
#define __AUTH_CPP__

#pragma comment(lib,"ws2_32.lib")


#include "../clanmenu/tjclanDEF.h"
#include "..\\..\\HoBaram\\HoTextFile.h"
#include "..\\clanmenu\\cE_CViewClanInfo.h"

#include "..\\clanmenu\\tjclanDEF.h"
#include "..\\clanmenu\\tjclan.h"


#include "auth.h"
#include "isaocheck.h"

extern char szConnServerName[16];


BOOL workfound;		//일할게 없으면 0임.


int AUTH_QUE_nums = 0;			//큐 갯수넣음.
CRITICAL_SECTION g_cs;

AUTH_QUE *AUTH_que;
AUTHLINKTBL aAuthLinkTbl[AUTHLINKTBL_MAX];

DWORD WINAPI AUTH_MainLoop(void* pVoid);

static BOOL AUTH_proc(int mode, int quenum, int threadindex);


//ktj : 클랜 멤버인지 알아낸다.  : AUTH_QUE_CMD_CL_MAKE
int AUTH_proc_isClanMember(int quenum, int threadindex);
int AUTH_proc_isClanMember_Result(int quenum, int threadindex);

//ktj : 클랜 만들기 : AUTH_QUE_CMD_CL_MAKE
int AUTH_proc_ClanMake(int quenum, int threadindex);
int AUTH_proc_ClanMake_Result(int quenum, int threadindex);
//ktj : 클랜 멤버 만들기 : AUTH_QUE_CMD_CL_MEMBER_MAKE
int AUTH_proc_Mmake(int quenum, int threadindex);
int AUTH_proc_Mmake_Result(int quenum, int threadindex);

//ktj : 클랜데이타를 읽는다. : AUTH_QUE_CMD_CL_MEMBER_MAKE
int AUTH_proc_ReadClan(int quenum, int threadindex);
int AUTH_proc_ReadClan_Result(int quenum, int threadindex);


//ktj : 클랜을 해체한다.    AUTH_QUE_CMD_BreakUP
int AUTH_proc_BreakUP(int quenum, int threadindex);
int AUTH_proc_BreakUP_Result(int quenum, int threadindex);


//ktj : 특정아디 추방.    AUTH_QUE_CMD_BreakUP
int AUTH_proc_Banishiment(int quenum, int threadindex);
int AUTH_proc_Banishiment_Result(int quenum, int threadindex);

//ktj : 창고권한.    AUTH_QUE_CMD_WarhouseR
int AUTH_proc_WarhouseR(int quenum, int threadindex);
int AUTH_proc_WarhouseR_Result(int quenum, int threadindex);


//ktj :클랜결성 완료용 AUTH_QUE_CMD_updateFlag
int AUTH_proc_updateFlag(int quenum, int threadindex);
int AUTH_proc_updateFlag_Result(int quenum, int threadindex);



//ktj :클랜탈퇴 AUTH_QUE_CMD_Secession
int AUTH_proc_Secession(int quenum, int threadindex);
int AUTH_proc_Secession_Result(int quenum, int threadindex);



//ktj :클랜마크읽기 AUTH_QUE_CMD_MarkREAD
int AUTH_proc_MarkREAD(int quenum, int threadindex);
int AUTH_proc_MarkREAD_Result(int quenum, int threadindex);

//ygy : 다른 클랜마크읽기

int AUTH_proc_MarkREAD2(int quenum, int threadindex);
int AUTH_proc_MarkREAD2_Result(int quenum, int threadindex);

//ygy : 계정이 클랜장으로 등록되어 있는지 체크
int AUTH_proc_isCheckClanJang(int quenum, int threadindex);
int AUTH_proc_isCheckClanJang_Result(int quenum, int threadindex);

//ygy : 클랜이름이 중복되었는지 체크
int AUTH_proc_isCheckClanName(int quenum, int threadindex);
int AUTH_proc_isCheckClanName_Result(int quenum, int threadindex);

//ygy : 초기 화면 관련 플래그
int AUTH_proc_isPFlag(int quenum, int threadindex);
int AUTH_proc_isPFlag_Result(int quenum, int threadindex);

//ygy :이임관련 플래그
int AUTH_proc_isKPFlag(int quenum, int threadindex);
int AUTH_proc_isKPFlag_Result(int quenum, int threadindex);

//ygy : 클랜마크번호로 클랜 정보 갖어오기
int AUTH_proc_ReadClanInfo(int quenum, int threadindex);
int AUTH_proc_ReadClanInfo_Result(int quenum, int threadindex);

//ygy : cldata 업데이트
int AUTH_proc_Updatcldata(int quenum, int threadindex);
int AUTH_proc_Updatcldata_Result(int quenum, int threadindex);
//ygy : notice
int AUTH_proc_ReadNotice(int quenum, int threadindex);
int AUTH_proc_ReadNotice_Result(int quenum, int threadindex);

//이임
int AUTH_proc_LeaveClan(int quenum, int threadindex);
int AUTH_proc_LeaveClan_Result(int quenum, int threadindex);

//부클랜장 임명
int AUTH_proc_AppointSubChip(int quenum, int threadindex);
int AUTH_proc_AppointSubChip_Result(int quenum, int threadindex);

//부클랜장 해임
int AUTH_proc_ReleaseSubChip(int quenum, int threadindex);
int AUTH_proc_ReleaseSubChip_Result(int quenum, int threadindex);

//Wav파일 가져오기
int AUTH_proc_GetWavFile(int quenum, int threadindex);
int AUTH_proc_GetWavFile_Result(int quenum, int threadindex);





//호동Clan추가
int AUTH_proc_sodindex(int quenum, int threadindex);
int AUTH_proc_sodindex_Result(int quenum, int threadindex);

//호동Clan추가
int AUTH_proc_isCheckClanMember(int quenum, int threadindex);
int AUTH_proc_isCheckClanMember_Result(int quenum, int threadindex);

// function jump table
typedef int(*FUNC)(int, int);
FUNC AUTH_proc_jmptbl[][AUTH_QUE_CMD_ALLNUM] = //3
{
	{
		NULL,						// AUTH_QUE_COMMAND_NONE,
		AUTH_proc_isClanMember,
		AUTH_proc_ClanMake,			//클랜 만들기
		AUTH_proc_Mmake,			//클랜 멤버만들기
		AUTH_proc_ReadClan,			//클랜데이타를 읽는다.
		AUTH_proc_BreakUP,			//클랜을 해체한다.
		AUTH_proc_Banishiment,		//클랜원추방
		AUTH_proc_WarhouseR,
		AUTH_proc_updateFlag,		//클랜이 완전결성된것으로 업데이트됨.

		AUTH_proc_Secession,		//클랜탈퇴


		AUTH_proc_MarkREAD,
		AUTH_proc_isCheckClanJang,		//클랜짱 등록되어 있는지 체크
		AUTH_proc_isCheckClanName,      //클랜이름 중복인지 체크
		AUTH_proc_isPFlag,		     //초기화면 플래그
		AUTH_proc_ReadClanInfo,
		AUTH_proc_MarkREAD2,
		AUTH_proc_Updatcldata,
		AUTH_proc_ReadNotice,
		AUTH_proc_LeaveClan,
		AUTH_proc_isKPFlag, //이임관련 플래그
		AUTH_proc_AppointSubChip,//부클랜장 임명
		AUTH_proc_ReleaseSubChip,//부클랜장 해임
		AUTH_proc_GetWavFile,//wav파일 가져오기
		AUTH_proc_sodindex,
		AUTH_proc_isCheckClanMember, //호동Clan추가

	},
	{
		NULL,
		AUTH_proc_isClanMember_Result,
		AUTH_proc_ClanMake_Result,		//시작 result
		AUTH_proc_Mmake_Result,		//끝   result
		AUTH_proc_ReadClan_Result,			//클랜데이타를 읽는다.
		AUTH_proc_BreakUP_Result,
		AUTH_proc_Banishiment_Result,
		AUTH_proc_WarhouseR_Result,
		AUTH_proc_updateFlag_Result,

		AUTH_proc_Secession_Result,	//클랜탈퇴

		AUTH_proc_MarkREAD_Result,
		AUTH_proc_isCheckClanJang_Result,
		AUTH_proc_isCheckClanName_Result,      //클랜이름 중복인지 체크
		AUTH_proc_isPFlag_Result,
		AUTH_proc_ReadClanInfo_Result,
		AUTH_proc_MarkREAD2_Result,
		AUTH_proc_Updatcldata_Result,
		AUTH_proc_ReadNotice_Result,
		AUTH_proc_LeaveClan_Result,
		AUTH_proc_isKPFlag_Result,
		AUTH_proc_AppointSubChip_Result, //부클랜장 임명
		AUTH_proc_ReleaseSubChip_Result,//부클랜장 해임
		AUTH_proc_GetWavFile_Result,//Wav파일 가져오기
		AUTH_proc_sodindex_Result,
		AUTH_proc_isCheckClanMember_Result, //호동Clan추가
	}
};

//ktj : AUTH_proc_jmptbl[mode][command]로 사용되며
//		모드는 0:인증, 1은 인증후 리턴값에 대한 함수에 접근해 사용됨.
//		예)인증 시		AUTH_proc_jmptbl[0][AUTH_QUE_COMMAND_AUTH]사용
//			인증리턴후 	AUTH_proc_jmptbl[1][AUTH_QUE_COMMAND_AUTH]사용



//AUTH_QUE 관련 데이타 처리함수 ======================================
int AUTH_QUE_AppendTail(AUTH_QUE *pNow, int type);
AUTH_QUE*  AUTH_QUE_getTop(int type);
int AUTH_QUE_Remove(AUTH_QUE *pNow);
int AUTH_QUE_Count(int type);
int AUTH_addQue(AUTH_QUE *que);


// AUTH DB 큐 링크 테이블의 맨뒤에 한개 추가．
int AUTH_QUE_AppendTail(AUTH_QUE *pNow, int type)
{
	AUTH_QUE *pOldTail;
	// 가장 최후의 한 개 전．이것 뒤에 추가한다．
	pOldTail = aAuthLinkTbl[type].QueTail.pPrev;
	// 금 최후이였다나 뿔 다음은 자신
	pOldTail->pNext = pNow;

	// 최후의 한 개전을 자신에게 한다．
	aAuthLinkTbl[type].QueTail.pPrev = pNow;

	// 자신의 한 개전은 금 최후이였다나 나루터．
	pNow->pPrev = pOldTail;
	// 자신의 다음은 가장 최후
	pNow->pNext = &aAuthLinkTbl[type].QueTail;

	return TRUE;
}


// DB 큐 링크 테이블의 선두를 돌려 준다．
AUTH_QUE*  AUTH_QUE_getTop(int type)
{
	// MUTEX LOCK

	// 톱에 연결되고る 남자 하인을 조사한다．
	// 그것은 최후 꼬리이였다．だっ 대구 아무것도 없다．
	if (aAuthLinkTbl[type].QueTop.pNext == &aAuthLinkTbl[type].QueTail) {
		return NULL;
	}

	// 이것이다．
	return aAuthLinkTbl[type].QueTop.pNext;
}

// 링크에서는 두 동물이 쉬는 장소．
int AUTH_QUE_Remove(AUTH_QUE *pNow)
{
	AUTH_QUE *pOldNext, *pOldPrev;

	pOldNext = pNow->pNext;
	pOldPrev = pNow->pPrev;
	pNow->pNext = NULL;
	pNow->pPrev = NULL;
	// 연결할지 얻는다．
	pOldNext->pPrev = pOldPrev;
	pOldPrev->pNext = pOldNext;

	return TRUE;
}

// 링크를 센다.
int AUTH_QUE_Count(int type)
{
	int iCount = 0;
	AUTH_QUE *pNow;
	// 선두의 위치
	pNow = aAuthLinkTbl[type].QueTop.pNext;
	// 있을 때까지 센다．
	for (; pNow->pNext; pNow = pNow->pNext) {
		iCount++;
	}

	return iCount;
}
int AUTH_addQue(AUTH_QUE *que)
{
	AUTH_QUE *pNew;
	EnterCriticalSection(&g_cs);

	pNew = AUTH_QUE_getTop(AUTHLINKTBL_FREE);
	if (pNew == NULL)
	{
		LeaveCriticalSection(&g_cs);
		return -1;
	}

	pNew->command = que->command;
	pNew->fdid = que->fdid;
	pNew->result = AUTH_ERROR_OTHER;

	pNew->query_time = 10;
	lstrcpy(pNew->cdkey, que->cdkey);
	lstrcpy(pNew->isaokey, que->isaokey);
	lstrcpy(pNew->password, que->password);
	lstrcpy(pNew->ip_address, que->ip_address);
	lstrcpy(pNew->id, que->id);
	lstrcpy(pNew->expl, que->expl);
	lstrcpy(pNew->clanName, que->clanName);
	lstrcpy(pNew->charId, que->charId);
	lstrcpy(pNew->ClanZang_ID, que->ClanZang_ID);
	lstrcpy(pNew->ClanZang_ChaName, que->ClanZang_ChaName);
	lstrcpy(pNew->gserver, que->gserver);
	lstrcpy(pNew->ClanWon_ID, que->ClanWon_ID);
	lstrcpy(pNew->ClanWon_ChaName, que->ClanWon_ChaName);
	lstrcpy(pNew->Mark, que->Mark);
	lstrcpy(pNew->Gubun, que->Gubun);
	lstrcpy(pNew->PFlag, que->PFlag);

	pNew->howmanyTime = que->howmanyTime;
	pNew->nNum = que->nNum;
	pNew->ci = que->ci;
	pNew->job_code = que->job_code;
	pNew->level = que->level;
	pNew->joinlevel = que->joinlevel;
	pNew->joinjobcode = que->joinjobcode;
	lstrcpy(pNew->chipflag, que->chipflag);
	lstrcpy(pNew->szWavFileName, que->szWavFileName);


	pNew->status = AUTH_QUE_STATUS_EXIST;
	pNew->sod2index = que->sod2index;

	AUTH_QUE_Remove(pNew);

	AUTH_QUE_AppendTail(pNew, AUTHLINKTBL_START_WAIT);

	LeaveCriticalSection(&g_cs);

	return pNew->index;
}

DWORD WINAPI AUTH_MainLoop(void* pVoid)
{
	THREADstruct *thr = (THREADstruct *)pVoid;

	int cnt = 0;

	static struct timeval prev = { 0,0 };
	unsigned long thread_index = -1;
	int ret = 0;

	while (1)
	{
		Sleep(10);

		time_t myTime;
		time(&myTime);

		switch (thr->flag)
		{
		case FLAG_WAIT:
			time(&myTime);


			thr->state = FLAG_WAIT;

			SuspendThread((void *)thr->thrHandle);

			time(&myTime);
			//fd2("쓰레드메인루프 FLAG_WAIT 끝. %d ", myTime);
			break;

		case FLAG_EXIT:
			goto _EXIT;

		case FLAG_EXEC:
			thr->state = FLAG_EXEC;

			workfound = FALSE;
			EnterCriticalSection(&g_cs);

			AUTH_QUE *que;
			que = AUTH_QUE_getTop(AUTHLINKTBL_START_WAIT);

			if (que != NULL)
			{
				workfound = TRUE;
				cnt = que->index;
			}
			else {
				workfound = FALSE;
			}


			if (!workfound)
			{
				LeaveCriticalSection(&g_cs);				//window only
				continue;
			}

			AUTH_que[cnt].status = AUTH_QUE_STATUS_BEGINAUTHPROC; //2

			AUTH_QUE_Remove(&AUTH_que[cnt]);
			AUTH_QUE_AppendTail(&AUTH_que[cnt], AUTHLINKTBL_WORKING);  //2

			LeaveCriticalSection(&g_cs);				//window only

			if (!AUTH_proc(0, cnt, thread_index))
			{
				//fd2( "auth_proc error [que:%d command:%d]\n", cnt, AUTH_que[cnt].command);
				break;
			}

			EnterCriticalSection(&g_cs);			//window only

			AUTH_QUE_Remove(&AUTH_que[cnt]);
			AUTH_QUE_AppendTail(&AUTH_que[cnt], AUTHLINKTBL_FINISH); //3

			AUTH_que[cnt].status = AUTH_QUE_STATUS_ENDOFAUTHPROC; //3
			LeaveCriticalSection(&g_cs);


			break;
		}
	}
_EXIT:
	thr->flag = FLAG_DEAD;

	ExitThread(TRUE);
	return TRUE;
}
BOOL AUTH_proc(int mode, int quenum, int threadindex)
{

	if (mode == 0)
		mode = 0;

	if (mode == 1)
		mode = 1;

	FUNC	func;
	BOOL	ret = FALSE;

	if (quenum < 0 || quenum > AUTH_QUE_nums)
	{
		//fd2( "err: quenum \n");
		return FALSE;
	}

	if (AUTH_que[quenum].command <= AUTH_QUE_CMD_NONE || AUTH_que[quenum].command >= AUTH_QUE_CMD_ALLNUM)
	{
		//fd2( "err: command \n");
		return FALSE;
	}

	func = AUTH_proc_jmptbl[mode][AUTH_que[quenum].command];
	if (func)
	{
		ret = func(quenum, threadindex);
	}
	else
	{
		//fd2( "err: no such function\n");
	}
	//if( !ret)
		//fd2("err func:\n");
	return ret;

}

WebDB_Thread::WebDB_Thread()
{

}
WebDB_Thread::~WebDB_Thread()
{
	AUTH_close();
}
void WebDB_Thread::init()
{
}

void WebDB_Thread::main()
{
	AUTH_getResultLoop();
}


void WebDB_Thread::end()
{

}
int WebDB_Thread::AUTH_init(int Num)
{
	//fd2( "AUTH_init()함수 start" );

	AUTH_QUE_nums = Num;

	int i;

	AUTH_que = new AUTH_QUE[AUTH_QUE_nums];

	if (AUTH_que == NULL)
	{
		//fd2("can not allocatte memory %d\n","new memory");
		return FALSE;
	}

	for (i = 0; i < (int)AUTH_QUE_nums; i++)
	{
		AUTH_que[i].status = AUTH_QUE_STATUS_NONE;
		AUTH_que[i].command = AUTH_QUE_CMD_NONE;
		AUTH_que[i].index = i;
		AUTH_que[i].fdid = -1;
		AUTH_que[i].cdkey[0] = '\0';
		AUTH_que[i].isaokey[0] = '\0';
		AUTH_que[i].password[0] = '\0';

		AUTH_que[i].result = AUTH_ERROR_OTHER;
	}

	InitializeCriticalSection(&g_cs);

	for (i = 0; i < AUTHLINKTBL_MAX; i++)
	{
		aAuthLinkTbl[i].QueTop.pNext = &aAuthLinkTbl[i].QueTail;
		aAuthLinkTbl[i].QueTop.pPrev = NULL;

		aAuthLinkTbl[i].QueTail.pPrev = &aAuthLinkTbl[i].QueTop;
		aAuthLinkTbl[i].QueTail.pNext = NULL;
	}

	for (i = 0; i < (int)AUTH_QUE_nums; i++)
		AUTH_QUE_AppendTail(&AUTH_que[i], AUTHLINKTBL_FREE);


	DWORD dwSendMsgId;
	ThreadS.thrHandle = 0;
	ThreadS.flag = 0;

	ThreadS.cnt = 0;
	DWORD thrHandle = (unsigned long)CreateThread(NULL, 0, AUTH_MainLoop, (void*)&ThreadS, 0, &dwSendMsgId);
	ThreadS.thrHandle = thrHandle;

	if (ThreadS.thrHandle == 0)
		return 0;


	//fd2( "AUTH_init()함수 end" );

	return TRUE;
}
int WebDB_Thread::AUTH_close(void)
{
	TerminateThread((void*)ThreadS.thrHandle, 0);

	delete AUTH_que;
	AUTH_que = NULL;

	DeleteCriticalSection(&g_cs);

	//fd2( "AUTH_close()함수 " );
	return TRUE;
}
void WebDB_Thread::Suspend()
{
	//fd2("중지함수 Suspend() 00 ");
	ThreadS.flag = FLAG_WAIT;

	//fd2("중지함수 Suspend() 11 ");
}

void WebDB_Thread::Resume()      //재개
{
	//fd2("재개함수 Resume() 들어감 ");

	if (ThreadS.flag == FLAG_EXEC) return; //flag가 실행상태이면 그냥 간다.


	//fd2("재개함수 Resume() while 시작 ");
	while (1) {
		//fd2("재개함수 Resume() while 중 ");

		if (ThreadS.flag == FLAG_WAIT) {

			//fd2("재개함수 Resume() while 중 break; ");


			break;  //flag가 대기상태일때만 수행함.
		}
	}

	ThreadS.flag = FLAG_EXEC;				//활동재개(주의:플래그를 ResumeThread()앞에쓸것 컴이 너무빠르면 쓰레드가 엉킬위험있음.)
	ResumeThread((void *)ThreadS.thrHandle);

	//fd2("재개함수 Resume()  끝");
}
int WebDB_Thread::AUTH_getResultLoop(void)
{
	int i;
	static	int cnt = 0;

	AUTH_QUE *que;
	cnt = -1;

	EnterCriticalSection(&g_cs);				//window only

	for (i = 0; i < AUTH_QUE_nums; i++)
	{
		que = AUTH_QUE_getTop(AUTHLINKTBL_FINISH); //처리가 끝난 큐를 가져온다.
		if (que != NULL)
		{
			cnt = que->index;	// 배열 번호

			AUTH_QUE_Remove(que);
			if (!AUTH_proc(1, cnt, -1)) {
				//eprint( "auth_proc error [%d]\n", cnt);
			}
			AUTH_que[cnt].status = AUTH_QUE_STATUS_NONE;
			// 하늘 링크에
			AUTH_QUE_AppendTail(&AUTH_que[cnt], AUTHLINKTBL_FREE);
		}
		else {
			break;
		}
	}
	LeaveCriticalSection(&g_cs);					//window only
	return  TRUE;
}

int WebDB_Thread::ReadNotice(char *userid, char *chaname, char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AuthQueTmp));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReadNotice;

	STRINGCOPY(AuthQueTmp.ClanZang_ID, userid);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, chaname);

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_ReadNotice(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadNotice(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadNotice(int quenum, int threadindex)
{
	char *chaname, *gserver, *userid;
	int knret = 1, iBadMsg = 0;

	userid = AUTH_que[quenum].ClanZang_ID;
	chaname = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;


	//fd2("AUTH_proc_ReadClanInfo %s ", AUTH_que[quenum].Mark);

	knret = iCheck.ReadNotice(userid, chaname, gserver, AUTH_que[quenum].ret_Buf);


	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
int AUTH_proc_ReadNotice_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadNotice_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReadNotice_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		ANSdata.ret_val = iResultCode;
		break;
	case 1:
		ANSdata.ret_val = iResultCode;
		lstrcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 100:
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}

	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}

int AUTH_proc_ReadClanInfo(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClanInfo(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReadClanInfo(int quenum, int threadindex)
{
	char *szMarkNum;
	CLANINFO* claninfo;
	int knret = 1, iBadMsg = 0;
	char* clnaName;

	szMarkNum = AUTH_que[quenum].Mark;
	claninfo = AUTH_que[quenum].ci;

	//fd2("AUTH_proc_ReadClanInfo %s ", AUTH_que[quenum].Mark);

	knret = iCheck.ReadClanInfo(szMarkNum, AUTH_que[quenum].ret_Buf);
	if (knret == 1)
	{
		char* clanINFO_result(char *marknum, char *szInfo, CLANINFO* ci);
		clnaName = clanINFO_result(AUTH_que[quenum].Mark, AUTH_que[quenum].ret_Buf, claninfo);
		knret = iCheck.read_ClanImage2(clnaName, AUTH_que[quenum].Mark, claninfo);
		if (knret == 1)
			claninfo->nStatus = 2;
		else
			claninfo->nStatus = 3;
	}
	else
		claninfo->nStatus = 3;

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
int AUTH_proc_ReadClanInfo_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClanInfo_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadClanInfo_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	int clanINFO_result2(int ret_code, char *marknum, CLANINFO *ci);

	clanINFO_result2(iResultCode, AUTH_que[quenum].Mark, AUTH_que[quenum].ci);

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}


int WebDB_Thread::ReadClanInfo(char *clanNum, CLANINFO *ci)
{
	static int cnt = 0;
	//fd2("ReadClanInfo:  클랜마크번호 %s  (cnt %d )",   clanNum,  cnt);
	cnt++;


	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReadClanInfo;

	STRINGCOPY(AuthQueTmp.Mark, clanNum);

	AuthQueTmp.ci = ci;

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}

int WebDB_Thread::isCheckClanMember(char *pszServerName, char *pszUserName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isCheckClanMember;

	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, pszUserName);
	STRINGCOPY(AuthQueTmp.gserver, pszServerName);

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;

}

int AUTH_proc_isCheckClanMember_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanMember_Result(quenum, threadindex);
}

int AUTH_proc_isCheckClanMember(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanMember(quenum, threadindex);
}



int WebDB_Thread::AUTH_proc_isCheckClanMember(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver;
	int knret = 1, iBadMsg = 0;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;

	knret = iCheck.isCheckClanMember(gserver, ClanZang_ChaName);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;

	return TRUE;
}

int WebDB_Thread::AUTH_proc_isCheckClanMember_Result(int quenum, int threadindex)
{
	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		ANSdata.ret_val = iResultCode;
		break;
	case 1:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}
	return TRUE;
}
int AUTH_proc_isClanMember(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isClanMember(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isClanMember(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver;
	int knret = 1, iBadMsg = 0;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;

	knret = iCheck.isClanMember(ClanZang_ID, gserver, ClanZang_ChaName, AUTH_que[quenum].ret_Buf);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_isClanMember_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isClanMember_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isClanMember_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;	// 디폴트는 기타의 에러

	switch (iResultCode)
	{
	case 0:
		ANSdata.ret_val = iResultCode;
		lstrcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 1:
		ANSdata.ret_val = iResultCode;
		lstrcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 5:
	case 4:
	case 3:
	case 2:
		ANSdata.ret_val = iResultCode;
		lstrcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 100:
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}

	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}

int AUTH_proc_isPFlag(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isPFlag(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isPFlag(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver, *PFlag, *Gubun, *ClanName;
	int knret = 1, iBadMsg = 0;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	PFlag = AUTH_que[quenum].PFlag;
	Gubun = AUTH_que[quenum].Gubun;
	ClanName = AUTH_que[quenum].clanName;

	knret = iCheck.isPFlag(ClanZang_ID, ClanName, ClanZang_ChaName, gserver, PFlag, Gubun);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_isPFlag_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isPFlag_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isPFlag_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		ANSdata.ret_val = iResultCode;
		break;
	case 1:
		ANSdata.ret_val = iResultCode;
		break;
	case 100:
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}

	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}

int WebDB_Thread::isPFlag(char *userid, char *clName, char *chName, char *gserver, char *PFlag, char *Gubun)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isPFlag;

	STRINGCOPY(AuthQueTmp.Gubun, Gubun);
	STRINGCOPY(AuthQueTmp.ClanZang_ID, userid);
	STRINGCOPY(AuthQueTmp.clanName, clName);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, chName);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.PFlag, PFlag);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int WebDB_Thread::isCheckClanJang(char *ClanZang_ID, char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isCheckClanJang;

	STRINGCOPY(AuthQueTmp.ClanZang_ID, ClanZang_ID);
	STRINGCOPY(AuthQueTmp.gserver, gserver);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_isCheckClanJang(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanJang(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanJang(int quenum, int threadindex)
{
	char* ClanZang_ID, *gserver;
	int knret = 1, iBadMsg = 0;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	gserver = AUTH_que[quenum].gserver;


	knret = iCheck.isCheckClanJang(ClanZang_ID, gserver);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_isCheckClanJang_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanJang_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanJang_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = ANSdata.ret_val;
		break;
	case 101:
	case 102:
	case 103:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}

	ANSdata.ret_val = iResultCode;
	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val );


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int WebDB_Thread::isCheckClanName(char *ClanName, char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isCheckClanName;

	STRINGCOPY(AuthQueTmp.clanName, ClanName);
	STRINGCOPY(AuthQueTmp.gserver, gserver);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_isCheckClanName(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanName(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanName(int quenum, int threadindex)
{
	char* ClanName, *gserver;
	int knret = 1, iBadMsg = 0;

	ClanName = AUTH_que[quenum].clanName;
	gserver = AUTH_que[quenum].gserver;

	knret = iCheck.isCheckClanName(ClanName, gserver);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_isCheckClanName_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isCheckClanName_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isCheckClanName_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = ANSdata.ret_val;
		break;
	case 101:
	case 102:
	case 103:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}

	ANSdata.ret_val = iResultCode;
	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val );


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}

int AUTH_proc_ClanMake(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ClanMake(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ClanMake(int quenum, int threadindex)
{
	char* ClanZang_ID, *ClanZang_ChaName, *gserver, *ClanName, *expl;
	int knret = 1, iBadMsg = 0;
	DWORD chtype;
	int level;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	ClanName = AUTH_que[quenum].clanName;
	expl = AUTH_que[quenum].expl;
	gserver = AUTH_que[quenum].gserver;
	chtype = AUTH_que[quenum].job_code;
	level = AUTH_que[quenum].level;

	knret = iCheck.makeClan(ClanZang_ID, gserver, ClanZang_ChaName, ClanName, expl, chtype, level, AUTH_que[quenum].ret_Buf);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_ClanMake_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ClanMake_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ClanMake_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1:
		iResultCode = AUTH_que[quenum].result;
		lstrcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 3:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = ANSdata.ret_val;
		break;
	case 101:
	case 102:
	case 103:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}


	ANSdata.ret_val = iResultCode;
	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val );


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int AUTH_proc_Mmake(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Mmake(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Mmake(int quenum, int threadindex)
{
	char *clanName, *memId, *memCharId;
	char *ClanZang_ID, *ClanZang_ChaName, *gserver, *ClanWon_ID, *ClanWon_ChaName, *chipflag;
	int knret = 1, iBadMsg = 0;
	int level = 0;
	int joinlevel;
	DWORD job_code;


	clanName = AUTH_que[quenum].clanName;
	memId = AUTH_que[quenum].id;
	memCharId = AUTH_que[quenum].charId;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	ClanWon_ID = AUTH_que[quenum].ClanWon_ID;
	ClanWon_ChaName = AUTH_que[quenum].ClanWon_ChaName;
	level = AUTH_que[quenum].level;
	job_code = AUTH_que[quenum].joinjobcode;
	joinlevel = AUTH_que[quenum].joinlevel;
	chipflag = AUTH_que[quenum].chipflag;

	knret = iCheck.joinClanMember(ClanZang_ID, gserver, ClanZang_ChaName, clanName, ClanWon_ChaName, ClanWon_ID, level, job_code, joinlevel, chipflag);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;

	return TRUE;
}


int AUTH_proc_Mmake_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Mmake_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Mmake_Result(int quenum, int threadindex)
{
	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 3:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 4:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 101:
	case 102:
	case 103:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}

	ANSdata.ret_val = iResultCode;

	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return 1;
}
int AUTH_proc_ReadClan(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClan(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadClan(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver;
	int knret = 1, iBadMsg = 0;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;

	knret = iCheck.read_ClanData(ClanZang_ID, gserver, ClanZang_ChaName, AUTH_que[quenum].ret_Buf);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_ReadClan_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReadClan_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_ReadClan_Result(int quenum, int threadindex)
{
	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1:
		iResultCode = AUTH_que[quenum].result;
		lstrcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	case 100:
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	case 101:
	case 102:
		lstrcpy(ANSdata.ret_Buf, AUTH_que[quenum].ret_Buf);
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}

	ANSdata.ret_val = iResultCode;
	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}

int AUTH_proc_BreakUP(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_BreakUP(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_BreakUP(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver, *ClanName;
	int knret = 1, iBadMsg = 0;

	ClanName = AUTH_que[quenum].clanName;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;

	knret = iCheck.BreakUPClan(ClanZang_ID, gserver, ClanZang_ChaName, ClanName);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;

	return TRUE;
}


int AUTH_proc_BreakUP_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_BreakUP_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_BreakUP_Result(int quenum, int threadindex)
{
	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 101:
	case 102:
	case 103:
	case 104:
		break;


	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}
	ANSdata.ret_val = iResultCode;
	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int AUTH_proc_Secession(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Secession(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Secession(int quenum, int threadindex)
{
	char *clanName, *secession_id, *gserver, *clanzang;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	clanzang = AUTH_que[quenum].ClanWon_ChaName;
	gserver = AUTH_que[quenum].gserver;
	secession_id = AUTH_que[quenum].ClanWon_ID;

	knret = iCheck.Secession(secession_id, gserver, clanzang, clanName);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_Secession_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Secession_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Secession_Result(int quenum, int threadindex)
{
	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 3:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
	case ISAO_ERR_TCP_CONNECT:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 101:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}

	ANSdata.ret_val = iResultCode;
	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int AUTH_proc_Banishiment(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Banishiment(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Banishiment(int quenum, int threadindex)
{
	char *clanName, *ClanWon, *gserver, *ClanZang_ID, *ClanZang_ChaName;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	ClanWon = AUTH_que[quenum].ClanWon_ChaName;

	knret = iCheck.Banishiment(ClanZang_ID, gserver, ClanZang_ChaName, clanName, ClanWon);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_Banishiment_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Banishiment_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_Banishiment_Result(int quenum, int threadindex)
{
	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 3:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 101:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}

	ANSdata.ret_val = iResultCode;
	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int AUTH_proc_WarhouseR(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_WarhouseR(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_WarhouseR(int quenum, int threadindex)
{
	char *clanName, *banish_id;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	banish_id = AUTH_que[quenum].expl;

	knret = iCheck.WarhouseRight(clanName, banish_id);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_WarhouseR_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_WarhouseR_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_WarhouseR_Result(int quenum, int threadindex)
{
	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 100:
	case 101:
	case 102:
		break;

	case AUTH_OK:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}
	ANSdata.ret_val = iResultCode;
	//fd2("창고권한 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int AUTH_proc_updateFlag(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_updateFlag(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_updateFlag(int quenum, int threadindex)
{
	char *clanName, *banish_id;
	int knret = 1, iBadMsg = 0;

	clanName = AUTH_que[quenum].clanName;
	banish_id = AUTH_que[quenum].expl;

	knret = iCheck.updateFlag(clanName);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_updateFlag_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_updateFlag_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_updateFlag_Result(int quenum, int threadindex)
{
	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 100:
	case 101:
	case 102:
		break;

	case AUTH_OK:
		iResultCode = AUTH_que[quenum].result;
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}

	ANSdata.ret_val = iResultCode;
	//fd2("창고권한 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;
	return TRUE;
}
int AUTH_proc_MarkREAD(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD(int quenum, int threadindex)
{
	char *Mark, *clanname;
	int knret = 1, iBadMsg = 0;

	Mark = AUTH_que[quenum].Mark;
	clanname = AUTH_que[quenum].clanName;

	knret = iCheck.read_ClanImage(clanname, Mark);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_MarkREAD_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD_Result(int quenum, int threadindex)
{
	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;

	iResultCode = AUTH_que[quenum].result;


	switch (iResultCode)
	{
	case 1:

		iResultCode = AUTH_que[quenum].result;
		break;
	case 2:
		iResultCode = AUTH_que[quenum].result;
		break;

	case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 101:
	case 102:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}
	ANSdata.ret_val = iResultCode;
	//fd2("창고권한 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int AUTH_proc_MarkREAD2(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD2(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD2(int quenum, int threadindex)
{
	char *Mark, *clanname;
	int knret = 1, iBadMsg = 0;

	Mark = AUTH_que[quenum].Mark;
	clanname = AUTH_que[quenum].clanName;

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_MarkREAD2_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_MarkREAD2_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_MarkREAD2_Result(int quenum, int threadindex)
{
	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 1:

		iResultCode = AUTH_que[quenum].result;
		break;
	case 2:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 100:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1004:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 101:
	case 102:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}
	ANSdata.ret_val = iResultCode;
	//fd2("창고권한 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int AUTH_proc_Updatcldata(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Updatcldata(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_Updatcldata(int quenum, int threadindex)
{
	char *id, *chaname, *gserver;
	int knret = 1, iBadMsg = 0;

	id = AUTH_que[quenum].ClanZang_ID;
	chaname = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;

	knret = iCheck.isClanMember(id, gserver, chaname, AUTH_que[quenum].ret_Buf);
	if ((knret == 0) || (knret == 2) || (knret == 1) || (knret == 3) || (knret == 4) || (knret == 5))
	{
		void ParsingIsClanMember(char* data, int myposition);
		ParsingIsClanMember(AUTH_que[quenum].ret_Buf, knret);
		if ((knret == 2) || (knret == 1) || (knret == 5))
		{
			knret = iCheck.read_ClanData(id, gserver, chaname, AUTH_que[quenum].ret_Buf);
			if (knret == 1)
			{
				void ParsigClanWon(char* data);
				ParsigClanWon(AUTH_que[quenum].ret_Buf);
				knret = iCheck.read_ClanImage(chaname, cldata.ClanMark);
			}
		}
	}


	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;

	return 1;
}

int AUTH_proc_Updatcldata_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_Updatcldata_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_Updatcldata_Result(int quenum, int threadindex)
{
	char szData[128];
	char GServer;
	char szNum[64];
	char szFile[256];
	char szFile2[256];
	ZeroMemory(szNum, sizeof(szNum));
	ZeroMemory(szFile, sizeof(szFile));
	ZeroMemory(szFile2, sizeof(szFile2));

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		iResultCode = AUTH_que[quenum].result;
		break;
	case 1:
		iResultCode = AUTH_que[quenum].result;
		GServer = cldata.ClanMark[0];
		lstrcpy(szNum, &cldata.ClanMark[3]);
		wsprintf(szFile, "%s\\%s\\%c_%s.%s", SAVE_DIR, szConnServerName, GServer, szNum, SAVE_EXE);
		wsprintf(szFile2, "%s\\%s\\%c_%s_16.%s", SAVE_DIR, szConnServerName, GServer, szNum, SAVE_EXE);

		DELET(cldata.hClanMark16);
		DELET(cldata.hClanMark);

		cldata.hClanMark16 = LoadDibSurfaceOffscreen(szFile2);
		cldata.hClanMark = LoadDibSurfaceOffscreen(szFile);

		break;
	case 100:
		ANSdata.ret_val = iResultCode;
		break;
	case	1004:
		ANSdata.ret_val = iResultCode;
		break;
	case 101:
	case 102:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}

	ANSdata.ret_val = iResultCode;
	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	void g_UpdateCldata_Close();
	g_UpdateCldata_Close();

	return TRUE;
}

int WebDB_Thread::Updatcldata(char *id, char *gserver, char *chaname)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));


	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_Updatcldata;

	STRINGCOPY(AuthQueTmp.ClanZang_ID, id);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, chaname);
	STRINGCOPY(AuthQueTmp.gserver, gserver);


	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}

int WebDB_Thread::isClanMember(char *ClanZang_id, char* gserver, char* ClanZang_ChaName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isClanMember;

	STRINGCOPY(AuthQueTmp.ClanZang_ID, ClanZang_id);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName);
	STRINGCOPY(AuthQueTmp.gserver, gserver);

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}

int WebDB_Thread::joinClanMember(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char* ClanName, char* ClanWon, char* ClanWon_ID, int level, DWORD chtype, int joinlevel, char *chipflag)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AuthQueTmp));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_CL_MEMBER_MAKE;

	STRINGCOPY(AuthQueTmp.ClanZang_ID, ClanZang_ID);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName);
	STRINGCOPY(AuthQueTmp.clanName, ClanName);
	STRINGCOPY(AuthQueTmp.ClanWon_ChaName, ClanWon);
	STRINGCOPY(AuthQueTmp.ClanWon_ID, ClanWon_ID);
	STRINGCOPY(AuthQueTmp.chipflag, chipflag);

	AuthQueTmp.level = level;
	AuthQueTmp.joinlevel = joinlevel;
	AuthQueTmp.joinjobcode = (int)chtype;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int WebDB_Thread::make_Clan(char *ClanZang_ID, char* gserver, char* ClanZang_ChaName, char* ClanName, char *explanation, DWORD chtype, int level)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_CL_MAKE;

	STRINGCOPY(AuthQueTmp.ClanZang_ID, ClanZang_ID);
	STRINGCOPY(AuthQueTmp.expl, explanation);
	STRINGCOPY(AuthQueTmp.clanName, ClanName);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName);
	STRINGCOPY(AuthQueTmp.gserver, gserver);

	AuthQueTmp.level = level;
	AuthQueTmp.job_code = chtype;

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int WebDB_Thread::ReadClan(char *ClanZang_ID, char* gserver, char* ClanZang_ChaName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReadClan;

	STRINGCOPY(AuthQueTmp.ClanZang_ID, ClanZang_ID);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName);


	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int WebDB_Thread::BreakUP_Clan(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char *ClanName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_BreakUP;

	STRINGCOPY(AuthQueTmp.ClanZang_ID, ClanZang_ID);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName);
	STRINGCOPY(AuthQueTmp.clanName, ClanName);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("BreakUP_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int WebDB_Thread::Banishiment(char *ClanZang_ID, char *gserver, char *ClanZang_ChaName, char *ClanName, char *ClanWon)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_Banishiment;

	STRINGCOPY(AuthQueTmp.clanName, ClanName);
	STRINGCOPY(AuthQueTmp.ClanZang_ID, ClanZang_ID);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, ClanZang_ChaName);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.ClanWon_ChaName, ClanWon);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("BreakUP_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int WebDB_Thread::Secession(char* clanzang, char* gserver, char* SecessionID, char* claname)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_Secession;

	STRINGCOPY(AuthQueTmp.clanName, claname);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.ClanWon_ChaName, SecessionID);
	STRINGCOPY(AuthQueTmp.ClanWon_ID, clanzang);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("BreakUP_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int WebDB_Thread::Warhouse_right(char *clanName, char *right_str)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_WarhouseR;


	STRINGCOPY(AuthQueTmp.clanName, clanName);
	STRINGCOPY(AuthQueTmp.expl, right_str);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("Warhouse_right() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_LeaveClan(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_LeaveClan(quenum, threadindex);
}
int AUTH_proc_LeaveClan_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_LeaveClan_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_LeaveClan(int quenum, int threadindex)
{
	char *clanname, *chaname, *gserver;
	int knret = 1, iBadMsg = 0;

	chaname = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	clanname = AUTH_que[quenum].clanName;

	knret = iCheck.LeaveClan(clanname, chaname, gserver);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return 1;
}
int WebDB_Thread::AUTH_proc_LeaveClan_Result(int quenum, int threadindex)
{
	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 1:
	case 2:
	case 3:
	case 4:
	case 5:
	case 6:
	case 100:
		break;
	case 1004:
		break;
	default:
		iResultCode = AUTH_ERROR_OTHER;
		break;
	}

	ANSdata.ret_val = iResultCode;
	//fd2("창고권한 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int WebDB_Thread::LeaveClan(char *clanname, char *chaname, char *gserver)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AuthQueTmp));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_LeaveClan;

	STRINGCOPY(AuthQueTmp.clanName, clanname);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, chaname);

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int WebDB_Thread::updateFlag(char *clanName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_updateFlag;

	STRINGCOPY(AuthQueTmp.clanName, clanName);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("Warhouse_right() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int WebDB_Thread::MarkREAD(char *clanname, char *mark)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_MarkREAD;

	STRINGCOPY(AuthQueTmp.Mark, mark);
	STRINGCOPY(AuthQueTmp.clanName, clanname);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("Warhouse_right() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int WebDB_Thread::MarkREAD2(char *clanname, char *mark)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_MarkREAD2;

	STRINGCOPY(AuthQueTmp.Mark, mark);
	STRINGCOPY(AuthQueTmp.clanName, clanname);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("Warhouse_right() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}

extern BOOL bCheckHostNameandPort;

void WebDB_Thread::CheckHostNamePort(char *hostname, int port)
{
	if (hostname == NULL)
	{
		bCheckHostNameandPort = FALSE;
		return;
	}
	if (port == 0)
	{
		bCheckHostNameandPort = FALSE;
		return;
	}

	bCheckHostNameandPort = TRUE;
}

int WebDB_Thread::start_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address)
{
	return 0;
}
int WebDB_Thread::end_GOLDmoney(int fd, char *cdkey, char *accountid, char *passwd, char *ip_address)
{
	AUTH_QUE AuthQueTmp;

	AuthQueTmp.fdid = 100;

	AuthQueTmp.command = AUTH_QUE_CMD_CL_MEMBER_MAKE;

	STRINGCOPY(AuthQueTmp.cdkey, cdkey);
	STRINGCOPY(AuthQueTmp.isaokey, accountid);
	STRINGCOPY(AuthQueTmp.password, passwd);
	STRINGCOPY(AuthQueTmp.ip_address, ip_address);
	AuthQueTmp.howmanyTime = 100;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("끝내기 과금 에러 큐에 등록안됨. %s \n", accountid );
		return 0;
	}
	return 1;
}

char web_DBip0[64] = { 0, };
int  web_DBport0 = 0;
char web_DBip1[64] = { 0, };
int  web_DBport1 = 0;
int  nClanTicket = 0;



void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1)
{
	lstrcpy(web_DBip0, ip0);
	lstrcpy(web_DBip1, ip1);

	web_DBport0 = port0;
	web_DBport1 = port1;

}

void web_DB_ip_port_init(char *ip0, int port0, char *ip1, int port1, int ticket)
{
	lstrcpy(web_DBip0, ip0);
	lstrcpy(web_DBip1, ip1);

	web_DBport0 = port0;
	web_DBport1 = port1;
#ifdef __CLANSERVER__
	nClanTicket = 9999;
#else
	nClanTicket = ticket;
#endif
}
void web_DB_start(char *hostN0, int port0, char *hostN1, int port1);
void web_DB_start()
{
	char hostN0[] = "211.39.144.157";
	char hostN1[] = "211.39.144.158";

	int port0 = 80;
	int port1 = 80;

	web_DB_start(web_DBip0, web_DBport0, web_DBip1, web_DBport1);
}


BOOL bip_port_error = FALSE;

void web_DB_start(char *hostN0, int port0, char *hostN1, int port1)
{
	if ((hostN0 == NULL) || (port0 == 0) || (hostN1 == NULL) || (port1 == 0))
	{
		bip_port_error = TRUE;

		WebDB.AUTH_init(10);
		WebDB.ThreadS.flag = FLAG_WAIT;
		WebDB.Suspend();

		while (1)
		{
			if (WebDB.ThreadS.flag == FLAG_WAIT)
				break;
		}

		return;
	}
	static int cnt = 0;

	if (cnt == 1)
		return;
	cnt = 1;

	iCheck.init(1, 5);

	WebDB.CheckHostNamePort(hostN0, port0);

	iCheck.init_HostName_Port(hostN0, port0);
	iCheck.init_HostName_Port1(hostN1, port1);

	WebDB.AUTH_init(10);
	WebDB.ThreadS.flag = FLAG_WAIT;
	WebDB.Suspend();

	while (1)
	{
		if (WebDB.ThreadS.flag == FLAG_WAIT)
			break;
	}
}


int web_DB_state_FLAG_WAIT()
{
	if (WebDB.ThreadS.flag == FLAG_WAIT)
		return 1;

	return 0;
}


void web_DB_main()
{
	WebDB.main();
}

void web_DB_end()
{
	WebDB.end();
}

int AUTH_proc_isKPFlag(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isKPFlag(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_isKPFlag(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver, *PFlag, *Gubun, *ClanName;
	int knret = 1, iBadMsg = 0;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	PFlag = AUTH_que[quenum].PFlag;
	Gubun = AUTH_que[quenum].Gubun;
	ClanName = AUTH_que[quenum].clanName;

	knret = iCheck.isKPFlag(ClanZang_ID, ClanName, ClanZang_ChaName, gserver, PFlag, Gubun);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_isKPFlag_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_isKPFlag_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_isKPFlag_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch (iResultCode)
	{
	case 0:
		ANSdata.ret_val = iResultCode;
		break;
	case 1:
		ANSdata.ret_val = iResultCode;
		break;
	case 100:
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}

	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}

int WebDB_Thread::isKPFlag(char *userid, char *clName, char *chName, char *gserver, char *PFlag, char *Gubun)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_isKPFlag;          // 인증하다

	STRINGCOPY(AuthQueTmp.Gubun, Gubun);
	STRINGCOPY(AuthQueTmp.ClanZang_ID, userid);
	STRINGCOPY(AuthQueTmp.clanName, clName);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, chName);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.PFlag, PFlag);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}

int WebDB_Thread::AppointSubChip(char* userid, char* chaname, char* clanname, char *gserver, char* clanwon)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_AppointSubChip;

	STRINGCOPY(AuthQueTmp.ClanZang_ID, userid);
	STRINGCOPY(AuthQueTmp.clanName, clanname);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, chaname);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.ClanWon_ChaName, clanwon);;

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}



int AUTH_proc_AppointSubChip(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_AppointSubChip(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_AppointSubChip(int quenum, int threadindex)
{
	char *ClanZang_ID, *ClanZang_ChaName, *gserver, *ClanName;
	int knret = 1, iBadMsg = 0;
	char *clanwon;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	clanwon = AUTH_que[quenum].ClanWon_ChaName;
	ClanName = AUTH_que[quenum].clanName;

	knret = iCheck.AppointSubChip(gserver, clanwon);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}

int AUTH_proc_AppointSubChip_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_AppointSubChip_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_AppointSubChip_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		ANSdata.ret_val = iResultCode;
		break;
	case 3:
		ANSdata.ret_val = iResultCode;
		break;
	case 2:
		ANSdata.ret_val = iResultCode;
		break;
	case 1:
		ANSdata.ret_val = iResultCode;
		break;
	case 100:
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}

	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}


int WebDB_Thread::ReleaseSubChip(char* userid, char* chaname, char* clanname, char *gserver, char* clanwon)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_ReleaseSubChip;

	STRINGCOPY(AuthQueTmp.ClanZang_ID, userid);
	STRINGCOPY(AuthQueTmp.clanName, clanname);
	STRINGCOPY(AuthQueTmp.ClanZang_ChaName, chaname);
	STRINGCOPY(AuthQueTmp.gserver, gserver);
	STRINGCOPY(AuthQueTmp.ClanWon_ChaName, clanwon);;

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_ReleaseSubChip(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReleaseSubChip(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReleaseSubChip(int quenum, int threadindex)
{
	int knret = 1, iBadMsg = 0;
	char *gserver;
	char *clanwon;
	char *ClanZang_ID, *ClanZang_ChaName, *ClanName;

	ClanZang_ID = AUTH_que[quenum].ClanZang_ID;
	ClanZang_ChaName = AUTH_que[quenum].ClanZang_ChaName;
	gserver = AUTH_que[quenum].gserver;
	clanwon = AUTH_que[quenum].ClanWon_ChaName;
	ClanName = AUTH_que[quenum].clanName;

	knret = iCheck.ReleaseSubChip(gserver, clanwon);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}


int AUTH_proc_ReleaseSubChip_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_ReleaseSubChip_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_ReleaseSubChip_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;

	switch (iResultCode)
	{
	case 0:
		ANSdata.ret_val = iResultCode;
		break;
	case 1:
		ANSdata.ret_val = iResultCode;
		break;
	case 2:
		ANSdata.ret_val = iResultCode;
		break;
	case 100:
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}

	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);


	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int	WebDB_Thread::GetWavFile(char* FileName)
{
	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_GetWavFile;

	STRINGCOPY(AuthQueTmp.szWavFileName, FileName);

	time_t myTime;
	time(&myTime);
	AuthQueTmp.howmanyTime = myTime;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_GetWavFile(int quenum, int threadindex)
{
	return  WebDB.AUTH_proc_GetWavFile(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_GetWavFile(int quenum, int threadindex)
{
	int knret = 1, iBadMsg = 0;
	char *szFileName;

	szFileName = AUTH_que[quenum].szWavFileName;

	knret = iCheck.GetWavFile(szFileName);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
int AUTH_proc_GetWavFile_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_GetWavFile_Result(quenum, threadindex);
}

int WebDB_Thread::AUTH_proc_GetWavFile_Result(int quenum, int threadindex)
{
	char *aszAuthErrStr[] =
	{
	"OK",
	"Err CDKEY",
	"Err ISAO_ID",
	"Err PASSWORD",
	"Err EXPIRE",
	"Err LOCOUT",
	"Err ISAO_DB",
	"Err OTHER",
	""
	};

	char szData[128];

	if (AUTH_que[quenum].result == 0)
		szData[0] = '\0';
	else
		wsprintf(szData, "faild");

	char szBuffer[256];

	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
		wsprintf(szBuffer, "%s", aszAuthErrStr[AUTH_que[quenum].result]);
	else
		wsprintf(szBuffer, "ExtraCode=%d", AUTH_que[quenum].result);

	int iResultCode;
	iResultCode = AUTH_que[quenum].result;


	switch (iResultCode)
	{
	case 0:
		ANSdata.ret_val = iResultCode;
		break;
	case 1:
		ANSdata.ret_val = iResultCode;
		break;
	case 2:
		ANSdata.ret_val = iResultCode;
		break;
	case 100:
		ANSdata.ret_val = iResultCode;
		break;
	case 1004:
		ANSdata.ret_val = iResultCode;
		break;
	default:
		ANSdata.ret_val = AUTH_ERROR_OTHER;
		break;
	}

	//fd2("클랜멤버여부의 답변을 받음. :  ret_val %d  ", ANSdata.ret_val);



	if (0 <= AUTH_que[quenum].result && AUTH_que[quenum].result < AUTH_ERROR_END)
	{

	}
	else
		AUTH_que[quenum].result = AUTH_ERROR_OTHER;

	return TRUE;
}
int sod2INFOindex(char *UserId, char* CharName, char* GServer, int Index)
{
	WebDB.sod2INFOindex(UserId, CharName, GServer, Index);
	return TRUE;
}
int WebDB_Thread::sod2INFOindex(char *UserId, char* CharName, char* GServer, int Index)
{
	Resume();

	AUTH_QUE AuthQueTmp;
	ZeroMemory(&AuthQueTmp, sizeof(AUTH_QUE));

	AuthQueTmp.fdid = 100;
	AuthQueTmp.command = AUTH_QUE_CMD_SOD2;

	STRINGCOPY(AuthQueTmp.id, UserId);
	STRINGCOPY(AuthQueTmp.charId, CharName);
	STRINGCOPY(AuthQueTmp.gserver, GServer);
	AuthQueTmp.sod2index = Index;

	if (AUTH_addQue(&AuthQueTmp) < 0)
	{
		//fd2("make_Clan() 에러   : 큐에 등록안됨");
		return 0;
	}
	return 1;
}
int AUTH_proc_sodindex(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_sodindex(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_sodindex(int quenum, int threadindex)
{
	int knret = 1, iBadMsg = 0;
	knret = iCheck.read_sod2(AUTH_que[quenum].id, AUTH_que[quenum].charId, AUTH_que[quenum].gserver, AUTH_que[quenum].sod2index, AUTH_que[quenum].szSod2Buff);

	AUTH_que[quenum].result = knret;
	AUTH_que[quenum].badmsg = iBadMsg;
	return TRUE;
}
int AUTH_proc_sodindex_Result(int quenum, int threadindex)
{
	return WebDB.AUTH_proc_sodindex_Result(quenum, threadindex);
}
int WebDB_Thread::AUTH_proc_sodindex_Result(int quenum, int threadindex)
{
	cSinSod2.RecvWebData(AUTH_que[quenum].sod2index, AUTH_que[quenum].szSod2Buff);

	return TRUE;
}
