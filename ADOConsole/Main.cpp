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
void ReadingDB(); //读取数据库操作
void AddDB(); //增加数据操作
void HandingDB(); //数据处理操作
int main()
{
	HandingDB();
	adoconnect.ExitConnect();
	return 0;
}

//读取数据库
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

//增加数据
void AddDB()
{
	char m_tel[20], m_Number[20], m_age[20], m_Name[20], m_address[20];
	bool m_flag = true; //判断增加操作是否成功的标志
	printf("请输入要增加的Number\n");
	scanf("%s", &m_Number);
	printf("请输入要增加的Name\n");
	scanf("%s", m_Name);
	printf("请输入要增加的Age\n");
	scanf("%s", &m_age);
	printf("请输入要增加的Address\n");
	scanf("%s", m_address);
	printf("请输入要增加的Tel\n");
	scanf("%s", &m_tel);
	try{
		//增加数据到数据库操作
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
	if (m_flag) //判断操作成功的输出语句
		printf("增加操作成功\n");
	else
		printf("增加操作失败\n");
	ReadingDB(); //从新读取数据库，并且显示
}

//删除数据
void DeleteDB(){

}

//修改数据
void ModifyDB(){
	CString strSql;
	char m_tel[20], m_Number[20], m_age[20], m_Name[20], m_address[20],chosenI[20];
	bool m_flag = true; //判断增加操作是否成功的标志
	printf("请输入要修改的数据的序号(1,2,3,...)\n");
	scanf("%s", &chosenI);
	printf("请输入新的Number\n");
	scanf("%s", &m_Number);
	printf("请输入新的Name\n");
	scanf("%s", m_Name);
	printf("请输入新的Age\n");
	scanf("%s", &m_age);
	printf("请输入新的Address\n");
	scanf("%s", m_address);
	printf("请输入新的Tel\n");
	scanf("%s", &m_tel);
	try{
		strSql.Format("update ");
	}
	catch (_com_error e)
	{
		m_flag = false;
		printf(e.ErrorMessage());
	}
	if (m_flag) //判断操作成功的输出语句
		printf("增加操作成功\n");
	else
		printf("增加操作失败\n");
	ReadingDB(); //从新读取数据库，并且显示
}

//查找数据
void SearchDB(){

}

//处理函数
void HandingDB()
{
	ReadingDB(); //读取数据库，并且显示
	char m_str[10], m_char;
	while (1)
	{
		printf("\n操作输入:\nQ:退出  A:增加数据 D:删除数据 M:修改数据 S:查找数据\n");
		scanf("%s", m_str);
		sscanf(m_str, "%c", &m_char); //将m_str转化为字符，并保存在m_char中
		if ('Q' == m_char || 'q' == m_char)
			break; //退出程序
		if ('A' == m_char || 'a' == m_char)
			AddDB(); //增加数据
		if ('D' == m_char || 'd' == m_char)
			DeleteDB(); //删除数据
		if ('M' == m_char || 'm' == m_char)
			ModifyDB(); //修改数据
		if ('S' == m_char || 's' == m_char)
			SearchDB(); //查找数据
	}

}