//#pragma once
#ifndef ADO_H
#define ADO_H


#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")


class ADO //ADORandW
{
public:
	ADO(int t);
	ADO();//Ĭ������access���ݿ�
	~ADO();
public:
	::_ConnectionPtr m_pConnection;//����API
	::_RecordsetPtr m_pRecordset;//���ݼ�����

	//ѡ�����ݿ��ѡ��δ����
	const static int type_SqlSever = 1;
	const static int type_MySql = 2;
	const static int type_Access = 3;
public:
	int InitConn(char* username, char* password, char* database);
	int Exit();//�ر�����

	void ShowCurrentRS(bool bWithName);//��ʾ��ǰ�����ݼ�
	void ShowColumnNames(char* table);

	int GetTableInfo(char* table);//������ű����Ϣ
	int Query(char* table,char* pCondition);
	int Add(char *table, char** pContent, int Cnum);//��ӱ����Ϣ,���������ݿ�˳����е����ݣ��е�����
	int Delete(char* table, char* pConditon);//ɾ�������Ϣ
	bool Update(char* table, char* neirong, char* pCondition);

	//��ȡ���ȫ������
	int GetColNum(char* table);
	//��ȡĳ�ű�ȫ����¼������
	int GetRSNum(char* table);

	//ִ��sql���
	int QuerySQL(char* sql);
	int ExcuteSQL(char* sql);
	

private:
	int m_GenerateConnString(_bstr_t database);
	int m_type;
	_bstr_t m_username;
	_bstr_t m_password;
};

#endif