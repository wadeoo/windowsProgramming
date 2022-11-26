#include "ADO.h"
#include<iostream>
#include<vector>
#include<iomanip>
using namespace std;


ADO::ADO(int t)
{
	switch (t)
	{
		case 1:
			m_dbType =SqlServer;//存储连接数据库的类型
			break;
		case 2:
			m_dbType =MySql;//存储连接数据库的类型
			break;
		case 3:
			m_dbType =Access;//存储连接数据库的类型
			break;
		default:
			break;
	}
	
}

ADO::~ADO(void)
{//防止万一忘记退出
	if (NULL != m_pConnection  && m_pConnection->State)
	{
		m_pConnection->Close();
		m_pConnection = NULL;
	}
	if (m_pRecordset != NULL && m_pRecordset->State){
		m_pRecordset->Close();
		m_pRecordset = NULL;
	}
}

int ADO::InitConn(char* username, char* password, char* database){
	::CoInitialize(NULL);//初始化COM环境 void
	//实例化连接和数据集
	m_pConnection.CreateInstance(__uuidof(Connection));
	m_pRecordset.CreateInstance(__uuidof(Recordset));

	//根据目前输入的数据，生成连接字符串
	if (!generateConnString(database)){
		printf("请输入ADO连接字符串");
		/*string conn;
		std::cin >> conn;
		m_pConnection->ConnectionString = conn.c_str();*/
	}

	//对数据库进行连接，
	try
	{
		m_pConnection->Open("", username, password, adModeUnknown);
	}
	catch (_com_error e)
	{
		printf(e.ErrorMessage());
		return 0;
	}
	return 1;
}

int ADO::GetTableInfo(char* tablename){//并将数据库中的信息读取到rs中


	if (m_pRecordset != NULL && m_pRecordset->State){
		m_pRecordset->Close();
	}
	_bstr_t table_name = tablename;
	_bstr_t sql_select = "select * from " + table_name;
	try
	{
		m_pRecordset->Open(sql_select,
			_variant_t((IDispatch*)m_pConnection, true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		//adOpenStatic: 静态 adOpenDynamic：动态 adLockOptimistic乐观封锁法 adCmdText：文本查询语句
	}
	catch (_com_error e)
	{
		printf(e.ErrorMessage());
	}
	return 0;
}


int ADO::QuerySQL(char* sql){
	if (m_pRecordset != NULL && m_pRecordset->State){
		m_pRecordset->Close();
	}
	try
	{
		m_pRecordset->Open((_bstr_t)sql,
			_variant_t((IDispatch*)m_pConnection, true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		//adOpenStatic: 静态 adOpenDynamic：动态 adLockOptimistic乐观封锁法 adCmdText：文本查询语句
	}
	catch (_com_error e)
	{
		printf(e.ErrorMessage());
		return 0;
	}
	return 1;
}
int ADO::ExcuteSQL(char* sql){
	if (m_pRecordset != NULL && m_pRecordset->State){
		m_pRecordset->Close();
	}
	try{
		m_pConnection->Execute((_bstr_t)sql, NULL, adCmdText);
	}
	catch (_com_error e)
	{
		printf(e.ErrorMessage());
		return 0;
	}
	return 1;
}



int ADO::Add(char *table, char** pContent, int Cnum)
{
	char** p = pContent;
	_bstr_t Content = pContent[0];//string
	Content = "'" + Content + "'";
	p++;
	for (int i = 1; i < Cnum; i++)
	{
		_bstr_t temp = *p;
		Content = Content + ",'" + temp + "'";
		p++;
	}
	try{
		m_pConnection->Execute((_bstr_t)"INSERT INTO [" + table + "] VALUES (" + Content + ")", NULL, adCmdText);
	}
	catch (_com_error e)
	{
		return 0;
	}
	return 1;
}


int ADO::Delete(char* table, char* condition){
	_bstr_t sTable = table;
	_bstr_t sCondition = condition;
	if (m_pRecordset != NULL && m_pRecordset->State){
		m_pRecordset->Close();
	}
	try
	{
		_bstr_t sql_delete = "delete from " + sTable + " where " + sCondition;
		m_pConnection->Execute(sql_delete, NULL, adCmdText);
	}
	catch (_com_error e)
	{
		printf(e.ErrorMessage());
		return 0;
	}
	return 1;
}

bool ADO::Update(char* table, char* content, char* condition)
{
	_bstr_t sTable = table;
	_bstr_t sContent = content;
	_bstr_t sCondition = condition;
	if (m_pRecordset != NULL && m_pRecordset->State){
		m_pRecordset->Close();
	}
	_bstr_t sql = "UPDATE [" + sTable + "] set " + sContent + " where " + sCondition;
	try
	{
		m_pConnection->Execute(sql, NULL, adCmdText);
		//ReadInfo();
	}
	catch (_com_error e)
	{
		printf(e.ErrorMessage());
		return false;
	}
	return true;
}


int ADO::Query(char* table, char* pCondition)
{
	_bstr_t sTable = table;
	_bstr_t sCondition = pCondition;
	if (m_pRecordset != NULL && m_pRecordset->State){
		m_pRecordset->Close();
	}
	_bstr_t sql = "select * from " + sTable + " where " + sCondition;
	try
	{
		m_pRecordset->Open(sql,
			_variant_t((IDispatch*)m_pConnection, true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		//adOpenStatic: 静态 adOpenDynamic：动态 adLockOptimistic乐观封锁法 adCmdText：文本查询语句
	}
	catch (_com_error e)
	{
		printf(e.ErrorMessage());
		return 0;
	}
	return 1;
}

int ADO::Exit(){//卸载连接
	if (m_pConnection->State){
		m_pConnection->Close();
		m_pConnection = NULL;
	}
	else{
		return -1;
	}

	if (m_pRecordset->State){
		m_pRecordset->Close();
		m_pRecordset = NULL;
	}
	else{
		return -2;
	}
	return 1;
}


void ADO::ShowCurrentRS(bool bWithName){
	int colsum = m_pRecordset->Fields->Count;
	vector<_bstr_t> column_name;
	try{
		for (int i = 0; i<colsum; i++){
			column_name.push_back(m_pRecordset->GetFields()->GetItem(_variant_t((long)i))->Name);
			//cout << setw(15) << m_pRecordset->GetFields()->GetItem(_variant_t((long)i))->Name;
		}
		cout << endl;
	}
	catch (_com_error e){
		printf(e.ErrorMessage());
	}

	if (bWithName)
	{
		for (int i = 0; i<colsum; i++){
			cout << setw(15) << m_pRecordset->GetFields()->GetItem(_variant_t((long)i))->Name;
		}
		cout << endl;
	}

	try{
		m_pRecordset->MoveFirst();
		vector<_bstr_t>::iterator itr;
		while (!m_pRecordset->adoEOF)
		{
			for (itr = column_name.begin(); itr != column_name.end(); itr++){
				try{
					cout << setw(14) << (_bstr_t)(m_pRecordset->GetCollect(*itr)) << " ";
				}
				catch (_com_error e){
					cout << setw(15) << "null";
				}
			}
			cout << endl;
			m_pRecordset->MoveNext();
		}
		m_pRecordset->MoveFirst();
	}
	catch (_com_error e){
		printf(e.ErrorMessage());
	}
}

void ADO::ShowColumnNames(char* table)
{
	int colsum = m_pRecordset->Fields->Count;
	GetTableInfo(table);
	vector<_bstr_t> column_name;
	try{
		for (int i = 0; i<colsum; i++){
			column_name.push_back(m_pRecordset->GetFields()->GetItem(_variant_t((long)i))->Name);
			cout << setw(15) << m_pRecordset->GetFields()->GetItem(_variant_t((long)i))->Name;
		}
		cout << endl;
	}
	catch (_com_error e){
		printf(e.ErrorMessage());
	}
}


int ADO::GetColNum(char* table)
{
	GetTableInfo(table);
	int colsum = m_pRecordset->Fields->Count;
	return colsum;
}

int ADO::GetRSNum(char* table)
{
	GetTableInfo(table);
	//ShowCurrentRS(false);
	int rlt = m_pRecordset->GetRecordCount();
	return rlt;
}



int ADO::generateConnString(_bstr_t database){
	if (m_dbType == SqlServer)
	{
		m_pConnection->ConnectionString = "";
		return -1;
	}
	else if (m_dbType == MySql)
	{
		_bstr_t conn = "Provider = msdaora; Data Source =" + database;
		m_pConnection->ConnectionString = conn;
		return 1;
	}
	else if (m_dbType = Access){
		_bstr_t conn = "Provider = Microsoft.Jet.OLEDB.4.0; Data Source = " + database;
		m_pConnection->ConnectionString = conn;
		return 1;
	}
	return -1;
}
