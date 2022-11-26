#include"ADOConn.h"
#include <stdio.h>
#include<iostream>
#include<string>
#include<atlstr.h>
using namespace std;
_bstr_t openString = "Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Access.mdb";
ADOConn adoconnect(openString);
_bstr_t mysql = "SELECT*FROM Lib";
_RecordsetPtr myrecord = adoconnect.GetRecordSet(mysql,openString);
void ReadingDB(); //��ȡ���ݿ����
void AddDB(); //�������ݲ���
void HandingDB(); //���ݴ������
int main()
{
	HandingDB();
	adoconnect.ExitConnect();
	return 0;
}

//��ȡ���ݿ�
void ReadingDB()
{
	printf("\nNumber Name age address tel\n");
	myrecord->MoveFirst();
	int i = 1;
	while (!myrecord->EndOfFile)
	{
		std::cout << i++ << ". ";
		printf((_bstr_t)(myrecord->GetCollect("Number")));
		printf(" ");
		printf((_bstr_t)(myrecord->GetCollect("Name")));
		printf(" ");
		printf((_bstr_t)(myrecord->GetCollect("Age")));
		printf(" ");
		printf((_bstr_t)(myrecord->GetCollect("Address")));
		printf(" ");
		printf((_bstr_t)(myrecord->GetCollect("Tel")));
		printf("\n");
		myrecord->MoveNext();
	}
	myrecord->MoveFirst();
}

//��������
void AddDB()
{
	char m_tel[20], m_Number[20], m_age[20], m_Name[20], m_address[20];
	bool m_flag = true; //�ж����Ӳ����Ƿ�ɹ��ı�־
	printf("������Ҫ���ӵ�Number\n");
	scanf("%s", &m_Number);
	printf("������Ҫ���ӵ�Name\n");
	scanf("%s", m_Name);
	printf("������Ҫ���ӵ�Age\n");
	scanf("%s", &m_age);
	printf("������Ҫ���ӵ�Address\n");
	scanf("%s", m_address);
	printf("������Ҫ���ӵ�Tel\n");
	scanf("%s", &m_tel);
	try{
		//�������ݵ����ݿ����
		myrecord->AddNew();
		myrecord->PutCollect("Number", atol(m_Number));
		myrecord->PutCollect("Name", _variant_t(m_Name));
		myrecord->PutCollect("Age", atol(m_age));
		myrecord->PutCollect("Address", _variant_t(m_address));
		myrecord->PutCollect("Tel", atol(m_tel));
		myrecord->Update();
	}
	catch (_com_error e)
	{
		m_flag = false;
		printf(e.ErrorMessage());
	}
	if (m_flag) //�жϲ����ɹ���������
		printf("���Ӳ����ɹ�\n");
	else
		printf("���Ӳ���ʧ��\n");
	ReadingDB(); //���¶�ȡ���ݿ⣬������ʾ
}

//ɾ������
void DeleteDB(){

}

//�޸�����
void ModifyDB(){
	CString strSql;
	char m_tel[20], m_Number[20], m_age[20], m_Name[20], m_address[20],chosenI[20];
	bool m_flag = true; //�ж����Ӳ����Ƿ�ɹ��ı�־
	printf("������Ҫ�޸ĵ����ݵ����(1,2,3,...)\n");
	scanf("%s", &chosenI);
	printf("�������µ�Number\n");
	scanf("%s", &m_Number);
	printf("�������µ�Name\n");
	scanf("%s", m_Name);
	printf("�������µ�Age\n");
	scanf("%s", &m_age);
	printf("�������µ�Address\n");
	scanf("%s", m_address);
	printf("�������µ�Tel\n");
	scanf("%s", &m_tel);
	try{
		strSql.Format("update ");
	}
	catch (_com_error e)
	{
		m_flag = false;
		printf(e.ErrorMessage());
	}
	if (m_flag) //�жϲ����ɹ���������
		printf("���Ӳ����ɹ�\n");
	else
		printf("���Ӳ���ʧ��\n");
	ReadingDB(); //���¶�ȡ���ݿ⣬������ʾ
}

//��������
void SearchDB(){

}

//������
void HandingDB()
{
	ReadingDB(); //��ȡ���ݿ⣬������ʾ
	char m_str[10], m_char;
	while (1)
	{
		printf("\n��������:\nQ:�˳�  A:�������� D:ɾ������ M:�޸����� S:��������\n");
		scanf("%s", m_str);
		sscanf(m_str, "%c", &m_char); //��m_strת��Ϊ�ַ�����������m_char��
		if ('Q' == m_char || 'q' == m_char)
			break; //�˳�����
		if ('A' == m_char || 'a' == m_char)
			AddDB(); //��������
		if ('D' == m_char || 'd' == m_char)
			DeleteDB(); //ɾ������
		if ('M' == m_char || 'm' == m_char)
			ModifyDB(); //�޸�����
		if ('S' == m_char || 's' == m_char)
			SearchDB(); //��������
	}

}