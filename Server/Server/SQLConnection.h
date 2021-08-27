#pragma once

#include <objbase.h>
#include <vector>
#include <comdef.h>
#include <sqltypes.h>
#include <sql.h>
#include <sqlext.h>

#define MAX_PARAMS		10000
#define MAX_QUERY_SIZE	2048

#define SQLCONNECTION	(SQLConnection::GetConnection)

enum EDatabaseID
{
	DATABASEID_None,
	DATABASEID_GameDB,
	DATABASEID_GameDB_2,
	DATABASEID_GameDB_3,
	DATABASEID_UserDB,
	DATABASEID_UserDB_2,
	DATABASEID_ServerDB,
	DATABASEID_LogDB,
	DATABASEID_SkillDB,
	DATABASEID_EventDB,
	DATABASEID_ClanDB,
	DATABASEID_ClanDB_2,
	DATABASEID_ClanDB_3,
	DATABASEID_ClanDB_4,
};

enum EDatabaseDataType
{
	PARAMTYPE_Integer,
	PARAMTYPE_String,
	PARAMTYPE_Float,
	PARAMTYPE_Int64,
	PARAMTYPE_Short,
	PARAMTYPE_Time,
	PARAMTYPE_Binary,
	PARAMTYPE_Null = 5000,
};

struct DatabaseStructureData
{
	EDatabaseID					eDatabaseID;
	char						* pszDatabaseName;
};

class SQLConnection
{
private:
	DatabaseStructureData						* GetDatabaseData(EDatabaseID eDatabaseID);
	SQLHANDLE									m_hEnv;
	SQLHANDLE									m_hConnection;
	SQLHANDLE									m_hStatement;
	EDatabaseID									m_eID;
	char										m_szDatabaseName[64];

	char										m_szQuery[MAX_QUERY_SIZE];

	CRITICAL_SECTION							m_sCriticalSection;

	BOOL										m_bOpen = FALSE;
	BOOL										m_bPrepared = FALSE;

	bool										m_baBlock[MAX_PARAMS];
	SQLINTEGER									m_iaBlock[MAX_PARAMS];
	SQLINTEGER									* BlockNext();
	void										BlockFree();

public:

	void										Init(EDatabaseID eDatabaseID, const char *pszHost, const char *pszUser, const char *pszPasswd);
	void										Shutdown();

	BOOL										SQLTimeStampToSystemTime(SYSTEMTIME * psSystemTime, SQL_TIMESTAMP_STRUCT * psSQLTimeStamp);

	BOOL										Open();
	BOOL										Prepare(const char * pszQuery);
	BOOL										Execute();
	BOOL										Execute(const char * pszQuery);

	BOOL										BindParameterInput(int iPosition, EDatabaseDataType eDataType, void * pParameter, int iSize = 0);
	BOOL										GetData(int iPosition, EDatabaseDataType eDataType, void * pParameter, int iSize = 0);
	BOOL										GetColumnName(int iPosition, void * pParameter, int iSize);
	BOOL										GetColumnCount(int & iCount);
	EDatabaseDataType							GetColumnType(const char * pszTableName, const char * pszColumnName);
	BOOL										Fetch();
	BOOL										Close();
	BOOL										Clear();

	static SQLConnection						* GetConnection(EDatabaseID eDatabaseID);

	SQLConnection();
	virtual ~SQLConnection();
};
