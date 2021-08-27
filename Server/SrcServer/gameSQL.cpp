#include "StdAfx.h"
#define SQLSOR_CPP
#include "gamesql.h"

#ifdef _W_SERVER


int Record_TempLogFile(char *szMessage);


SQLDATA::SQLDATA()
{

}
SQLDATA::~SQLDATA()
{

}

int SQLDATA::Start_ODBC()
{
	char *svr_name;
	char *user_name;
	char *user_pswd;

	int r;

	if (Odbc_Config.Dsn[0])
	{
		svr_name = Odbc_Config.Dsn;
		user_name = Odbc_Config.Name;
		user_pswd = Odbc_Config.Password;
	}
	else
	{
		svr_name = "c8master";
		user_name = "c8master";
		user_pswd = "joddo";
	}


	r = SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &env_hdl);

	if (r == SQL_ERROR) return 0;
	SQLSetEnvAttr(env_hdl, SQL_ATTR_ODBC_VERSION, (void*)SQL_OV_ODBC3, SQL_IS_INTEGER);

	r = SQLAllocHandle(SQL_HANDLE_DBC, env_hdl, &conn_hdl);

	if (r == SQL_ERROR) return 0;


	r = SQLConnect(conn_hdl, (unsigned char*)svr_name, SQL_NTS, (unsigned char*)user_name, SQL_NTS, (unsigned char*)user_pswd, SQL_NTS);

	if (r == SQL_ERROR) return 0;

	r = SQLAllocHandle(SQL_HANDLE_STMT, conn_hdl, &stmt_hdl);

	return 1;
}

int SQLDATA::End_ODBC()
{
	int r;

	if (stmt_hdl != NULL)
	{
		r = SQLFreeHandle(SQL_HANDLE_STMT, stmt_hdl);

		if (r == SQL_ERROR)
			return 0;
	}

	if (conn_hdl != NULL)
	{
		r = SQLDisconnect(conn_hdl);

		if (r == SQL_ERROR)
			return 0;
		r = SQLFreeHandle(SQL_HANDLE_DBC, conn_hdl);

		if (r == SQL_ERROR)
			return 0;
	}

	if (env_hdl != NULL)
	{
		r = SQLFreeHandle(SQL_HANDLE_ENV, env_hdl);
		if (r == SQL_ERROR) return 0;
	}
	return 1;
}

int	SQLDATA::LogOn(char *szID, char *szPassword)
{
	char id[128] = { 0, };
	char pass[128] = { 0, };
	char sell, block;

	int r;

	if (!Odbc_Config.Dsn[0])
	{
		BYTE	ch;
		char TableName[32];

		ch = (BYTE)szID[0];
		TableName[0] = 0;

		if (ch >= 'a' && ch <= 'z')
		{
			TableName[0] = ch - 0x20;
			TableName[1] = 0;
		}
		else
		{
			if (ch >= 'A' && ch <= 'Z')
			{
				TableName[0] = ch;
				TableName[1] = 0;
			}
			else
			{
				if (ch >= '0' && ch <= '9')
					lstrcpy(TableName, "[0GameUser]");
				else
					lstrcpy(TableName, "[9GameUser]");
			}
		}

		if (!TableName[0])
			return -1;

		wsprintf(stmt_buf, "SELECT * FROM %sGameUser WHERE userid='%s'", TableName, szID);

		r = SQLExecDirect(stmt_hdl, (unsigned char*)stmt_buf, SQL_NTS);
		if (r == SQL_ERROR)
			return 0;

		r = SQLBindCol(stmt_hdl, 2, SQL_C_CHAR, &pass, 9, NULL);
		r = SQLBindCol(stmt_hdl, 11, SQL_C_UTINYINT, &sell, 1, NULL);
		r = SQLBindCol(stmt_hdl, 12, SQL_C_UTINYINT, &block, 1, NULL);


		if (SQLFetch(stmt_hdl) == SQL_NO_DATA_FOUND)
			return -1;

		SQLFreeStmt(stmt_hdl, SQL_CLOSE);

		if (lstrcmpi(szPassword, pass) != 0)
			return -2;
		if (Odbc_Config.CloseAccount && sell != 1)
			return -3;
		if (block)
			return -3;
	}

	else
	{
		wsprintf(stmt_buf, "SELECT * FROM %s WHERE %s='%s'", Odbc_Config.Table, Odbc_Config.Table_Id, szID);
		r = SQLExecDirect(stmt_hdl, (unsigned char*)stmt_buf, SQL_NTS);
		if (r == SQL_ERROR)
			return 0;

		r = SQLBindCol(stmt_hdl, Odbc_Config.Table_Password, SQL_C_CHAR, &pass, 16, NULL);
		if (Odbc_Config.Table_Play)
			r = SQLBindCol(stmt_hdl, Odbc_Config.Table_Play, SQL_C_UTINYINT, &sell, 1, NULL);
		else
			sell = 1;

		if (SQLFetch(stmt_hdl) == SQL_NO_DATA_FOUND)
			return -1;

		SQLFreeStmt(stmt_hdl, SQL_CLOSE);

		if (lstrcmpi(szPassword, pass) != 0)
			return -2;
		if (Odbc_Config.CloseAccount && sell != 1)
			return -3;
	}

	return TRUE;
}



SQLDATA		SqlData;


int SqlLogOn(char *szID, char *szPass)
{
	int val;
	SqlData.Start_ODBC();
	val = SqlData.LogOn(szID, szPass);
	SqlData.End_ODBC();

	return val;
}
#endif


int	InitODBC()
{
	return TRUE;
}
int	CloseODBC()
{
	return TRUE;

}
time_t SystemTimeToTime_T(SYSTEMTIME st)
{
	FILETIME ft;
	SystemTimeToFileTime(&st, &ft);

	//LONGLONG nLL;
	ULARGE_INTEGER ui;
	ui.LowPart = ft.dwLowDateTime;
	ui.HighPart = ft.dwHighDateTime;
	//nLL = (ft.dwHighDateTime << 32) + ft.dwLowDateTime;
	time_t pt = (long)((LONGLONG)(ui.QuadPart - 116444736000000000) / 10000000);
	return pt;
}

#ifdef _W_SERVER

char *AccountDBName = "AccountDb";
char *AccountDbIP = "127.0.0.1";
char *AccountDbID = "sa";
char *AccountDbPwd = "12345678";

int AdoSql_CharSave(char *szUserId, char *szCharName, int Type, int Level, INT64 exp64, int BattlePoint, int DeathPoint)
{
	char query[1024] = { 0 };

	cADO *pAdo = new cADO;

	if (pAdo != NULL)
	{
		if (pAdo->Connect(AccountDBName, AccountDbIP, AccountDbID, AccountDbPwd))
		{
			wsprintf(query, "SELECT * FROM [Character] WHERE CharName = '%s'", szCharName);

			if (pAdo->ExecuteSelect(query))
			{
				char szbuf[32] = { 0 };
				pAdo->GetStringValue("CharName", szbuf, 31);

				if (lstrcmp(szbuf, szCharName) == 0)
				{
					STRINGFORMAT(query, "UPDATE [Character] SET MxLevel = '%d',MxExp = %I64d,Battle_Point = '%d',Death_Point = '%d' WHERE CharName = '%s'", Level, exp64, BattlePoint, DeathPoint, szCharName);
					pAdo->ExecuteNonQuery(query);
				}
				else
				{
					STRINGFORMAT(query, "INSERT INTO [Character]([UserId],[CharName],[Type],[MxLevel],[MxExp],[Battle_Point],[Death_Point]) VALUES('%s','%s','%d','%d','%I64d','%d','%d')", szUserId, szCharName, Type, Level, exp64, BattlePoint, DeathPoint);
					pAdo->ExecuteNonQuery(query);
				}
			}
		}
		pAdo->Close();
		delete pAdo;
		return TRUE;
	}
	return FALSE;
}
int AdoSql_LoadBattlePoint(char *szCharName, short *BattlePoint, short *DeathPoint)
{
	char query[1024] = { 0 };

	cADO *pAdo = new cADO;

	if (pAdo != NULL)
	{
		if (pAdo->Connect(AccountDBName, AccountDbIP, AccountDbID, AccountDbPwd))
		{
			wsprintf(query, "SELECT * FROM [Character] WHERE CharName = '%s'", szCharName);

			if (pAdo->ExecuteSelect(query))
			{
				char szbuf[32] = { 0 };
				pAdo->GetStringValue("CharName", szbuf, 31);

				if (lstrcmp(szbuf, szCharName) == 0)
				{
					*BattlePoint = pAdo->GetIntValue("Battle_Point");
					*DeathPoint = pAdo->GetIntValue("Death_Point");
				}
			}
		}
		pAdo->Close();
		delete pAdo;
		return TRUE;
	}
	return FALSE;
}
int AdoSql_LogOn(char *szuserid, char *szpassword, time_t *DisuseDay, int *VipLevel, time_t *VipTime)
{
	if (szuserid[0] == '\0')
		return -1;

	if (szpassword[0] == '\0')
		return -2;

	char TableName[8] = { 0 };

	if (szuserid[0] >= 'a' && szuserid[0] <= 'z')
	{
		TableName[0] = szuserid[0];
		TableName[1] = '\0';
	}
	else if (szuserid[0] >= 'A' && szuserid[0] <= 'Z')
	{
		TableName[0] = szuserid[0];
		TableName[1] = '\0';
	}
	else
	{
		TableName[0] = '0';
		TableName[1] = '\0';
	}

	char query[256] = { 0 };

	wsprintf(query, "SELECT * FROM [%sGameUser] WHERE userid = '%s'", TableName, szuserid);

	int Result = 0;

	cADO *pAdo = new cADO;

	if (pAdo != NULL)
	{
		if (pAdo->Connect(AccountDBName, AccountDbIP, AccountDbID, AccountDbPwd))
		{
			if (pAdo->ExecuteSelect(query))
			{
				char szbuf[32] = { 0 };

				pAdo->GetStringValue("Passwd", szbuf, 31);

				if (lstrcmp(szbuf, szpassword) == 0)
				{
					time_t cTimer = pAdo->GetTimeValue("DisuseDay");
					time_t dTimer;

					time(&dTimer);

					if (dTimer <= cTimer)
					{
						*DisuseDay = cTimer;

						pAdo->GetStringValue("BlockChk", szbuf, 2);

						if (lstrcmp(szbuf, "0") == 0)
						{
							Result = 1;
						}
						else
							Result = -18;
					}
					else
						Result = -5;
				}
				else
					Result = -2;

				*VipLevel = pAdo->GetIntValue("VipLevel");
				*VipTime = pAdo->GetTimeValue("VipTime");
			}
		}
		pAdo->Close();
		delete pAdo;
	}
	return Result;
}


cADO::cADO()
{
	hr = CoInitialize(NULL);
	isConn = FALSE;
}
cADO::~cADO()
{
	Close();
	CoUninitialize();
}
int cADO::Connect(char *DbName, char *DbIp, char *DbId, char *DbPassword)
{
	if (isConn == TRUE)
		return TRUE;
	if (DbName == NULL)
		return FALSE;

	try
	{
		char ConnStr[256] = { 0 };

		wsprintf(ConnStr, "Provider=SQLOLEDB.1;Persist Security Info=True;User ID=%s;Password=%s;Initial Catalog=%s;Data Source=%s", DbId, DbPassword, DbName, DbIp);
		// 创建连接
		conn.CreateInstance(__uuidof(Connection));
		conn->ConnectionString = ConnStr;
		conn->Open("", "", "", adConnectUnspecified);
		// 创建命令
		command.CreateInstance(__uuidof(Command));
		command->ActiveConnection = conn;
		// 创建记录集
		rs.CreateInstance(__uuidof(Recordset));
		// 表示已经建立连接
		isConn = TRUE;

		return TRUE;
	}
	catch (_com_error e)
	{
		if (conn->State)
		{
			conn->Close();
			conn = NULL;
		}
		return FALSE;
	}
}
// 执行数据
int cADO::ExecuteNonQuery(char *query)
{
	try
	{
		// 开始事物
		//conn->BeginTrans();
		command->CommandText = query;
		command->Execute(NULL, NULL, adCmdText);
		//conn->CommitTrans();
		return TRUE;
	}
	catch (_com_error e)
	{
		//conn->RollbackTrans();
		Close();
		return FALSE;
	}
}
// 查询数据
int cADO::ExecuteSelect(char *query)
{
	try
	{
		command->CommandText = query;
		rs = command->Execute(NULL, NULL, adCmdText);
		if (rs != NULL)
			return TRUE;
		return FALSE;
	}
	catch (_com_error e)
	{
		Close();
		return FALSE;
	}
}
// 移动到下一条记录
int cADO::MoveNext()
{
	try
	{
		rs->MoveNext();
		if (rs->rsEOF)
			return FALSE;
		else
			return TRUE;
	}
	catch (_com_error e)
	{
		return FALSE;
	}
}
int cADO::MoveFirst()
{
	if (rs->State)
		rs->MoveFirst();
	return TRUE;
}
int cADO::MoveLast()
{
	if (rs->State)
		rs->MoveLast();
	return TRUE;
}
int cADO::GetBoolValue(char *ItemName)
{
	BOOL bRet = FALSE;
	_variant_t v;

	try
	{
		v = rs->GetCollect(ItemName);
		bRet = v.boolVal;
		return bRet;
	}
	catch (_com_error e)
	{
		return FALSE;
	}
}
unsigned int cADO::GetUIntValue(char *ItemName)
{
	unsigned int bUint;
	_variant_t v;

	try
	{
		v = rs->GetCollect(ItemName);
		if (v.vt != VT_NULL)
			bUint = v.uintVal;
		else
			bUint = 0;
		return bUint;
	}
	catch (_com_error e)
	{
		return 0;
	}
}
int cADO::GetIntValue(char *ItemName)
{
	int iRet;
	_variant_t v;

	try
	{
		v = rs->GetCollect(ItemName);
		if (v.vt != VT_NULL)
			iRet = v.intVal;
		else
			iRet = 0;
		return iRet;
	}
	catch (_com_error e)
	{
		return 0;
	}
}
unsigned long cADO::GetULongValue(char *ItemName)
{
	unsigned long uLRet;
	_variant_t v;

	try
	{
		v = rs->GetCollect(ItemName);
		if (v.vt != VT_NULL)
			uLRet = v.ulVal;
		else
			uLRet = 0;
		return uLRet;
	}
	catch (_com_error e)
	{
		return 0;
	}
}
long cADO::GetLongValue(char *ItemName)
{
	long lRet;
	_variant_t v;

	try
	{
		v = rs->GetCollect(ItemName);
		if (v.vt != VT_NULL)
			lRet = v.lVal;
		else
			lRet = 0;
		return lRet;
	}
	catch (_com_error e)
	{
		return 0;
	}
}
double cADO::GetDoubleValue(char *ItemName)
{
	double dRet;
	_variant_t v;

	try
	{
		v = rs->GetCollect(ItemName);
		if (v.vt != VT_NULL)
			dRet = v.dblVal;
		else
			dRet = 0.0f;
		return dRet;
	}
	catch (_com_error e)
	{
		return 0.0f;
	}
}
float cADO::GetFloatValue(char *ItemName)
{
	float fRet;
	_variant_t v;

	try
	{
		v = rs->GetCollect(ItemName);
		if (v.vt != VT_NULL)
			fRet = v.fltVal;
		else
			fRet = 0.f;
		return fRet;
	}
	catch (_com_error e)
	{
		return 0.f;
	}
}
int cADO::GetStringValue(char *ItemName, char *value, int size)
{
	_variant_t v;
	try
	{
		v = rs->GetCollect(ItemName);
		lstrcpy(value, (char *)_bstr_t(v));
		return TRUE;
	}
	catch (_com_error e)
	{
		return FALSE;
	}
}
time_t cADO::GetTimeValue(char *ItemName)
{
	_variant_t v;

	try
	{
		v = rs->GetCollect(ItemName);

		if (v.vt != NULL)
		{
			SYSTEMTIME st;
			VariantTimeToSystemTime(v, &st);
			return SystemTimeToTime_T(st);;
		}
		return 0;

	}
	catch (_com_error e)
	{
		return 0;
	}
}
int cADO::Close()
{
	if (isConn == FALSE)
		return TRUE;
	try
	{
		conn->Close();
		isConn = FALSE;
		return TRUE;
	}
	catch (_com_error e)
	{
		return FALSE;
	}
}

#endif
