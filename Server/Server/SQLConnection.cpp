#include "stdafx.h"
#include "SQLConnection.h"

std::vector<SQLConnection*> vSQLConnection;

BOOL show_errorSQL(unsigned int handletype, const SQLHANDLE& handle)
{
	static SQLCHAR sqlstateSqlError[1024];
	static SQLCHAR messageSqlError[1024];
	static char szBufSQLError[2048];
	ZeroMemory(szBufSQLError, 2048);
	ZeroMemory(sqlstateSqlError, 1024);
	ZeroMemory(messageSqlError, 1024);
	if (SQL_SUCCESS == SQLGetDiagRecA(handletype, handle, 1, sqlstateSqlError, NULL, messageSqlError, 1024, NULL))
	{
		STRINGFORMAT(szBufSQLError, "Message: %s\nSQLSTATE: %s\n", messageSqlError, sqlstateSqlError);
		WRITEDBG(szBufSQLError);
		return TRUE;
	}
	return FALSE;
}

DatabaseStructureData saDatabaseData[]
{
	{ DATABASEID_GameDB,	"GameDB" },
	{ DATABASEID_GameDB_2,	"GameDB" },
	{ DATABASEID_GameDB_3,	"GameDB" },
	{ DATABASEID_UserDB,	"UserDB" },
	{ DATABASEID_UserDB_2,	"UserDB" },
	{ DATABASEID_ServerDB,	"ServerDB" },
	{ DATABASEID_LogDB,		"LogDB" },
	{ DATABASEID_SkillDB,	"SkillDB" },
	{ DATABASEID_EventDB,	"EventDB" },
	{ DATABASEID_ClanDB,	"ClanDB" },
	{ DATABASEID_ClanDB_2,	"ClanDB" },
	{ DATABASEID_ClanDB_3,	"ClanDB" },
	{ DATABASEID_ClanDB_4,	"ClanDB" },
};
SQLConnection::SQLConnection()
{

}
SQLConnection::~SQLConnection()
{

}
DatabaseStructureData * SQLConnection::GetDatabaseData(EDatabaseID eDatabaseID)
{
	for (auto & v : saDatabaseData)
	{
		if (v.eDatabaseID == eDatabaseID)
			return &v;
	}

	return NULL;
}
SQLINTEGER * SQLConnection::BlockNext()
{
	for (int i = 0; i < MAX_PARAMS; i++)
	{
		if (m_baBlock[i] == false)
		{
			m_baBlock[i] = true;
			return &m_iaBlock[i];
		}
	}

	return NULL;
}

void SQLConnection::BlockFree()
{
	for (int i = 0; i < MAX_PARAMS; i++)
		m_baBlock[i] = false;
}

void SQLConnection::Init(EDatabaseID eDatabaseID, const char *pszHost, const char *pszUser, const char *pszPasswd)
{
	//Copy database name to class
	STRINGCOPY(m_szDatabaseName, GetDatabaseData(eDatabaseID)->pszDatabaseName);
	m_eID = eDatabaseID;

	//Try alloc Handle SQL ODBC
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_ENV, SQL_NULL_HANDLE, &m_hEnv))
		show_errorSQL(SQL_HANDLE_ENV, m_hStatement);

	//Set Version ODBC
	if (SQL_SUCCESS != SQLSetEnvAttr(m_hEnv, SQL_ATTR_ODBC_VERSION, (SQLPOINTER)SQL_OV_ODBC3, 0))
		return;

	//Try alloc handle connection
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_DBC, m_hEnv, &m_hConnection))
		show_errorSQL(SQL_HANDLE_DBC, m_hStatement);

	//Set connection timeout
	SQLSetConnectAttrA(m_hConnection, SQL_LOGIN_TIMEOUT, (SQLPOINTER)5, SQL_IS_INTEGER);

	char szStringConnectionSQL[512];
	SQLCHAR strconn[512];
	ZeroMemory(szStringConnectionSQL, 512);

	//Set string connection

	//PC
	STRINGFORMAT(szStringConnectionSQL, "Persist Security Info=False; Integrated Security=False; Driver=%s; Server=%s; Database=%s; Uid=%s; Pwd=%s;", "{SQL Server Native Client 11.0}", pszHost, m_szDatabaseName, pszUser, pszPasswd);

	//CacktoPC
//	STRINGFORMAT( szStringConnectionSQL, 512, "Persist Security Info=False; Integrated Security=False; Driver=%s; Server=%s; Database=%s; Uid=%s; Pwd=%s;", "{SQL Server Native Client 10.0}", "CACKTO\\SQLEXPRESS", szDatabaseName, "sa", "pt123@" );

	//Igor
//	STRINGFORMAT( szStringConnectionSQL, 512, "Persist Security Info=False; Integrated Security=False; Driver=%s; Server=%s; Database=%s; Uid=%s; Pwd=%s;", "{SQL Server Native Client 10.0}", "DESKTOP-U8VJKKJ\\SQLEXPRESS", szDatabaseName, "sa", "123456" );

	memcpy(strconn, szStringConnectionSQL, 512);

	SQLCHAR retconstring[1024];

	//Connect to Database
	SQLDriverConnectA(m_hConnection, NULL, strconn, lstrlenA((char*)strconn), retconstring, 1024, NULL, SQL_DRIVER_NOPROMPT);

	//Create Statement handler
	if (SQL_SUCCESS != SQLAllocHandle(SQL_HANDLE_STMT, m_hConnection, &m_hStatement))
		show_errorSQL(SQL_HANDLE_DBC, m_hStatement);

	SQLSetStmtAttr(m_hStatement, SQL_ATTR_CURSOR_SCROLLABLE, (SQLPOINTER)SQL_SCROLLABLE, SQL_IS_INTEGER);

	//Create mutex
	InitializeCriticalSection(&m_sCriticalSection);

	BlockFree();

	vSQLConnection.push_back(this);
}
void SQLConnection::Shutdown()
{
	if (m_bOpen)
		Clear();

	//Unlock Mutex
	LeaveCriticalSection(&m_sCriticalSection);

	vSQLConnection.pop_back();
}
BOOL SQLConnection::SQLTimeStampToSystemTime(SYSTEMTIME * psSystemTime, SQL_TIMESTAMP_STRUCT * psSQLTimeStamp)
{
	if (!psSystemTime || !psSQLTimeStamp)
		return FALSE;

	psSystemTime->wYear = psSQLTimeStamp->year;
	psSystemTime->wMonth = psSQLTimeStamp->month;
	psSystemTime->wDayOfWeek = 0;
	psSystemTime->wDay = psSQLTimeStamp->day;
	psSystemTime->wHour = psSQLTimeStamp->hour;
	psSystemTime->wMinute = psSQLTimeStamp->minute;
	psSystemTime->wSecond = psSQLTimeStamp->second;
	psSystemTime->wMilliseconds = (WORD)psSQLTimeStamp->fraction;

	return TRUE;
}
BOOL SQLConnection::Open()
{
	//Lock Mutex
	EnterCriticalSection(&m_sCriticalSection);

	m_bOpen = TRUE;

	return TRUE;
}
BOOL SQLConnection::Prepare(const char * pszQuery)
{
	if (!m_bOpen)
	{
		WRITEDBG("[SQLConnection::Prepare()] : %s [%s]", pszQuery, m_bOpen ? "TRUE" : "FALSE");
		return FALSE;
	}

	//Copy Query
	STRINGCOPY(m_szQuery, pszQuery);

	//Check SQLI
	for (int i = 0; i < _countof(m_szQuery); i++)
	{
		//End string? break it
		if (m_szQuery[i] == 0)
			break;

		//Have quote mark? SQLI, return error
		if (m_szQuery[i] == 0x27)
		{
			//Query Not secure
			WRITEDBG("Query not secure!");
			return FALSE;
		}
	}

	//Prepare Query error? return
	if (SQLPrepareA(m_hStatement, (SQLCHAR*)m_szQuery, SQL_NTS) == SQL_ERROR)
	{
		WRITEDBG("SQLPrepareA() - %s", m_szQuery);
		show_errorSQL(SQL_HANDLE_STMT, m_hStatement);
		return FALSE;
	}

	m_bPrepared = TRUE;

	//Success
	return TRUE;
}

BOOL SQLConnection::Execute()
{
	if (!m_bOpen || !m_bPrepared)
	{
		WRITEDBG("[SQLConnection::Execute()] : %s [%s,%s]", m_szQuery, m_bOpen ? "TRUE" : "FALSE", m_bPrepared ? "TRUE" : "FALSE");
		return FALSE;
	}

	SQLRETURN iRetCode = SQL_SUCCESS;

	//Try Execute query
	if ((iRetCode = SQLExecute(m_hStatement)) == SQL_ERROR)
	{
		WRITEDBG("error %s - %s", m_szDatabaseName, m_szQuery);
		show_errorSQL(SQL_HANDLE_STMT, m_hStatement);
		return FALSE;
	}

	return TRUE;
}
BOOL SQLConnection::Execute(const char * pszQuery)
{
	if (!m_bOpen)
	{
		WRITEDBG("[SQLConnection::Execute()] : %s [%s,%s]", m_szQuery, m_bOpen ? "TRUE" : "FALSE", m_bPrepared ? "TRUE" : "FALSE");
		return FALSE;
	}

	SQLRETURN iRetCode = SQL_SUCCESS;

	//Try Execute query
	if ((iRetCode = SQLExecDirectA(m_hStatement, (SQLCHAR*)pszQuery, SQL_NTS)) == SQL_ERROR)
	{
		WRITEDBG("error %s - %s", m_szDatabaseName, m_szQuery);
		show_errorSQL(SQL_HANDLE_STMT, m_hStatement);
		return FALSE;
	}

	return TRUE;
}

BOOL SQLConnection::BindParameterInput(int iPosition, EDatabaseDataType eDataType, void * pParameter, int iSize)
{
	if (!m_bOpen || !m_bPrepared)
	{
		WRITEDBG("[SQLConnection::BindParameterInput()] : %s [%s,%s]", m_szQuery, m_bOpen ? "TRUE" : "FALSE", m_bPrepared ? "TRUE" : "FALSE");
		return FALSE;
	}

	int iType = 0;
	int iSQLType = 0;
	int iLen = 0;

	SQLINTEGER * piInputOutput = BlockNext();

	//Set Data Type
	switch (eDataType)
	{
	case PARAMTYPE_Integer:
		iType = SQL_C_LONG;
		iSQLType = SQL_INTEGER;
		*piInputOutput = 0;
		break;
	case PARAMTYPE_String:
		iType = SQL_C_CHAR;
		iSQLType = SQL_VARCHAR;
		iLen = lstrlenA((char*)pParameter);
		*piInputOutput = SQL_NTS;
		break;
	case PARAMTYPE_Float:
		iType = SQL_C_FLOAT;
		iSQLType = SQL_REAL;
		*piInputOutput = 0;
		break;
	case PARAMTYPE_Int64:
		iType = SQL_C_SBIGINT;
		iSQLType = SQL_BIGINT;
		*piInputOutput = 0;
		break;
	case PARAMTYPE_Time:
		iType = SQL_C_TIMESTAMP;
		iSQLType = SQL_TYPE_TIMESTAMP;
		*piInputOutput = 0;
		break;
	case PARAMTYPE_Binary:
		iType = SQL_C_BINARY;
		iSQLType = SQL_BINARY;
		iLen = iSize;
		*piInputOutput = iSize;
		break;
	default:
		break;
	}

	//Bind parameters
	if (SQLBindParameter(m_hStatement, iPosition, SQL_PARAM_INPUT, iType, iSQLType, iLen, 0, pParameter, 0, piInputOutput) == SQL_ERROR)
	{
		WRITEDBG("SQLBindParameter() %s - %s", m_szDatabaseName, m_szQuery);
		show_errorSQL(SQL_HANDLE_STMT, m_hStatement);
		return FALSE;
	}

	return TRUE;
}
BOOL SQLConnection::GetData(int iPosition, EDatabaseDataType eDataType, void * pParameter, int iSize)
{
	if (!m_bOpen || !m_bPrepared)
	{
		WRITEDBG("[SQLConnection::GetData()] : %s [%s,%s]", m_szQuery, m_bOpen ? "TRUE" : "FALSE", m_bPrepared ? "TRUE" : "FALSE");
		return FALSE;
	}

	int iType = 0;
	SQLINTEGER iDataSize = 0;
	void * pParam = pParameter;
	int iSizeParam = iSize;
	SQL_TIMESTAMP_STRUCT	sTimeStamp;

	//Set Data Type
	switch (eDataType)
	{
	case PARAMTYPE_Integer:
		iType = SQL_C_LONG;
		break;
	case PARAMTYPE_Short:
		iType = SQL_C_SHORT;
		break;

	case PARAMTYPE_String:
		iType = SQL_C_CHAR;
		break;
	case PARAMTYPE_Float:
		iType = SQL_C_FLOAT;
		break;
	case PARAMTYPE_Int64:
		iType = SQL_C_SBIGINT;
		break;
	case PARAMTYPE_Time:
		iType = SQL_C_TYPE_TIMESTAMP;
		pParam = &sTimeStamp;
		iSizeParam = 23;
		break;
	case PARAMTYPE_Binary:
		iType = SQL_C_BINARY;
		break;
	default:
		break;
	}

	//Get Data
	if (SQLGetData(m_hStatement, iPosition, iType, pParam, iSizeParam, &iDataSize) == SQL_ERROR)
	{
		WRITEDBG("error %d - %s - %s", iPosition, m_szDatabaseName, m_szQuery);
		show_errorSQL(SQL_HANDLE_STMT, m_hStatement);
		return FALSE;
	}

	if (eDataType == PARAMTYPE_Time)
		SQLTimeStampToSystemTime((SYSTEMTIME*)pParameter, &sTimeStamp);

	return TRUE;
}
BOOL SQLConnection::GetColumnName(int iPosition, void * pParameter, int iSize)
{
	if (!m_bOpen || !m_bPrepared)
	{
		WRITEDBG("[SQLConnection::GetColumnName()] : %s [%s,%s]", m_szQuery, m_bOpen ? "TRUE" : "FALSE", m_bPrepared ? "TRUE" : "FALSE");
		return FALSE;
	}

	SQLSMALLINT cbSize = 0;
	SQLSMALLINT cbDataType = 0;
	SQLUINTEGER cbColumn = 0;
	SQLSMALLINT cbScale = 0;
	SQLSMALLINT uNullType = 0;

	if (SQLDescribeColA(m_hStatement, iPosition, (SQLCHAR*)pParameter, iSize, &cbSize, &cbDataType, &cbColumn, &cbScale, &uNullType) == SQL_ERROR)
	{
		WRITEDBG("error %d - %s - %s", iPosition, m_szDatabaseName, m_szQuery);
		show_errorSQL(SQL_HANDLE_STMT, m_hStatement);
		return FALSE;
	}

	return TRUE;
}
BOOL SQLConnection::GetColumnCount(int & iCount)
{
	if (!m_bOpen || !m_bPrepared)
	{
		WRITEDBG("[SQLConnection::GetColumnCount()] : %s [%s,%s]", m_szQuery, m_bOpen ? "TRUE" : "FALSE", m_bPrepared ? "TRUE" : "FALSE");
		return FALSE;
	}

	iCount = 0;

	SQLSMALLINT cbCount = 0;

	if (SQLNumResultCols(m_hStatement, &cbCount) == SQL_ERROR)
	{
		WRITEDBG("error %s - %s", m_szDatabaseName, m_szQuery);
		show_errorSQL(SQL_HANDLE_STMT, m_hStatement);
		return FALSE;
	}

	iCount = (int)cbCount;

	return TRUE;
}
EDatabaseDataType SQLConnection::GetColumnType(const char * pszTableName, const char * pszColumnName)
{
	EDatabaseDataType i = PARAMTYPE_Null;

	char szResult[64] = { 0 };

	if (Prepare("SELECT DATA_TYPE FROM INFORMATION_SCHEMA.COLUMNS WHERE TABLE_NAME=? AND COLUMN_NAME=?"))
	{
		BindParameterInput(1, PARAMTYPE_String, (char*)pszTableName, STRLEN(pszTableName));
		BindParameterInput(2, PARAMTYPE_String, (char*)pszColumnName, STRLEN(pszColumnName));

		if (Execute() && Fetch())
		{
			GetData(1, PARAMTYPE_String, szResult, _countof(szResult));

			if (STRINGCOMPAREI(szResult, "varchar"))
				i = PARAMTYPE_String;
			else if (STRINGCOMPAREI(szResult, "int"))
				i = PARAMTYPE_Integer;
			else if (STRINGCOMPAREI(szResult, "real"))
				i = PARAMTYPE_Float;
			else if (STRINGCOMPAREI(szResult, "bigint"))
				i = PARAMTYPE_Int64;
		}
	}

	return i;
}
BOOL SQLConnection::Fetch()
{
	if (!m_bOpen || !m_bPrepared)
	{
		WRITEDBG("[SQLConnection::Fetch()] : %s [%s,%s]", m_szQuery, m_bOpen ? "TRUE" : "FALSE", m_bPrepared ? "TRUE" : "FALSE");
		return FALSE;
	}

	//Fetch ( Next Row )
	if (!SQL_SUCCEEDED(SQLFetch(m_hStatement)))
		return FALSE;

	return TRUE;
}
BOOL SQLConnection::Close()
{
	if (!m_bOpen)
		return FALSE;

	Clear();

	m_bOpen = FALSE;

	//Unlock Mutex
	LeaveCriticalSection(&m_sCriticalSection);
	return TRUE;
}

BOOL SQLConnection::Clear()
{
	SQLCancel(m_hStatement);
	SQLFreeStmt(m_hStatement, SQL_CLOSE);
	SQLFreeStmt(m_hStatement, SQL_UNBIND);
	SQLFreeStmt(m_hStatement, SQL_RESET_PARAMS);

	BlockFree();

	//Clear Query
	ZeroMemory(m_szQuery, _countof(m_szQuery));

	m_bPrepared = FALSE;

	return TRUE;
}

SQLConnection * SQLConnection::GetConnection(EDatabaseID eDatabaseID)
{
	//Find connection pointer
	for (const auto v : vSQLConnection)
	{
		//Same DatabaseID? return pointer of class
		if (v->m_eID == eDatabaseID)
			return v;
	}
	return NULL;
}