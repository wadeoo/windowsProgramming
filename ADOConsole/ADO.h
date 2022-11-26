//#pragma once
#ifndef ADO_H
#define ADO_H

#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")

//数据库类型
enum dbType_enum{
	SqlServer,
	MySql,
	Access
};


class ADO //ADORNW
{
public:
	ADO(int t=3); //默认连接access数据库
	~ADO();
public:
	::_ConnectionPtr m_pConnection;//连接API
	::_RecordsetPtr m_pRecordset;//数据集对象

	////选择数据库的选择，未完善
	//const static int type_SqlSever = 1;
	//const static int type_MySql = 2;
	//const static int type_Access = 3;
	
public:
	int InitConn(char* username, char* password, char* database);
	int Exit();//关闭连接

	void ShowCurrentRS(bool bWithName);//显示当前的数据集
	void ShowColumnNames(char* table);

	int GetTableInfo(char* table);//获得整张表的信息
	int Query(char* table,char* pCondition);
	int Add(char *table, char** pContent, int Cnum);//添加表的信息,表名，数据库顺序的列的内容，列的数量
	int Delete(char* table, char* pConditon);//删除表的信息
	bool Update(char* table, char* pContent, char* pCondition);

	//获取表的全部列数
	int GetColNum(char* table);
	//获取某张表全部记录的数量
	int GetRSNum(char* table);

	//执行sql语句
	int QuerySQL(char* sql);
	int ExcuteSQL(char* sql);
	

private:
	int generateConnString(_bstr_t database);
	dbType_enum m_dbType;
	_bstr_t m_username;
	_bstr_t m_password;
};

#endif