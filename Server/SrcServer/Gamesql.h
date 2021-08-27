
#include "..\\nettype.hpp"

#ifdef _W_SERVER

#include <sql.h>
#include <sqlext.h>
#include <odbcss.h>

class SQLDATA
{
public:
	SQLHENV env_hdl;
	SQLHDBC conn_hdl;
	SQLHSTMT stmt_hdl;

	char stmt_buf[512];
	char errmsg[512];

    SQLDATA();
    ~SQLDATA();

    int Start_ODBC();
    int End_ODBC();

	int	LogOn( char *szID , char *szPassword );

};


#endif

struct	ODBC_CONFIG 
{
	char	Dsn[32];			//���� ���񽺸�
	char	Name[32];			//������ ID
	char	Password[32];		//������ ��ȣ

	char	Table[32];			//���̺� �̸�
	char	Table_Id[32];		//���̺� ����
	int		Table_Password;		//���̺� ��ȣ ��
	int		Table_Play;			//���̺� �㰡 ��

	int		CloseAccount;		//�׽�Ʈ ������ ���

};

extern	ODBC_CONFIG	Odbc_Config;


int	InitODBC();
int	CloseODBC();
int SqlLogOn(char *szID , char *szPass );


#ifdef _W_SERVER

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF","rsEOF")

int AdoSql_LogOn(char *szuserid,char *szpassword,time_t *DisuseDay,int *VipLevel,time_t *VipTime);
int AdoSql_CharSave(char *szUserId,char *szCharName,int Type,int Level,INT64 exp64,int BattlePoint,int DeathPoint);
int AdoSql_LoadBattlePoint(char *szCharName,short *BattlePoint,short *DeathPoint);


class cADO
{
public:
	cADO();
	~cADO();
public:
	int Connect(char *DbName,char *DbIp,char *DbId,char *DbPassword);
	int ExecuteNonQuery(char *query);
	int ExecuteSelect(char *query);
	int MoveNext();
	int MoveFirst();
	int MoveLast();
	BOOL GetBoolValue(char *ItemName);
	unsigned int GetUIntValue(char *ItemName);
	int GetIntValue(char *ItemName);
	unsigned long GetULongValue(char *ItemName);
	long GetLongValue(char *ItemName);
	double GetDoubleValue(char *ItemName);
	float GetFloatValue(char *ItemName);
	int GetStringValue(char *ItemName,char *value,int size);
	time_t GetTimeValue(char *ItemName);
	int Close();
public:
	int isConn;
private:
	HRESULT hr;
	_ConnectionPtr	conn;
	_CommandPtr		command;
	_RecordsetPtr	rs;
};

#endif



