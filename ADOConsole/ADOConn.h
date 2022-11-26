#pragma once
#ifndef ADOCONN_H
#define ADOCONN_H
#pragma warning(disable: 4146)
#import "c:\Program Files\Common Files\System\ADO\msado15.dll" no_namespace rename("EOF", "EndOfFile")
class ADOConn
{
public:
	::_ConnectionPtr m_pConnection;
	::_RecordsetPtr m_pRecordset;
public:
	ADOConn(_bstr_t openString){ OnInitADOConn(openString); }
	//初始化-连接数据库
	void OnInitADOConn(_bstr_t openString);
	//执行查询，返回结果集
	::_RecordsetPtr & GetRecordSet(_bstr_t bstrSQL,_bstr_t openString);
	//执行sql语句，更新数据库
	bool ExecuteSQL(_bstr_t bstrSQL,_bstr_t openString);
	void ExitConnect();
};
#endif
