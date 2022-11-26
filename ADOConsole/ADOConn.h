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
	//��ʼ��-�������ݿ�
	void OnInitADOConn(_bstr_t openString);
	//ִ�в�ѯ�����ؽ����
	::_RecordsetPtr & GetRecordSet(_bstr_t bstrSQL,_bstr_t openString);
	//ִ��sql��䣬�������ݿ�
	bool ExecuteSQL(_bstr_t bstrSQL,_bstr_t openString);
	void ExitConnect();
};
#endif
