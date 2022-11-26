#include <stdio.h>
//由于引入ADO库文件时候，会产生警告 4146，但这个警告是没关系的，所以使用下一句代码屏蔽它
#pragma warning(disable: 4146)
//引入ADO库文件 注意C:\Program Files\Common Files\System\ado\msado15.dll这是指系统盘下，
//如果你的系统盘是D盘的话 那么应该是D:\Program Files\Common Files\System\ado\msado15.dll 
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")

_ConnectionPtr m_pCon; //申明Connection指针
_RecordsetPtr m_pRec; //申明Recordset指针
void Initialize(); //初始化资源操作 
void ReadingDB(); //读取数据库操作
void AddDB(); //增加数据操作
void UnInitialize(); //卸载资源操作
void HandingDB(); //数据处理操作

int main(int argc, char* argv[])
{
	Initialize(); //初始化
	HandingDB(); //处理函数
	UnInitialize(); //卸载资源
	return 0;
}

//初始化
void Initialize()
{
	::CoInitialize(NULL); //初始化OLE/COM库环境
	//****************************************************************************
	// _ConnectionPtr通常被用来创建一个数据连接或执行一条不返回任何结果的SQL语句，
	// 如一个存储过程。
	// _ConnectionPtr m_pCon(__uuidof(Connection)); 
	m_pCon.CreateInstance(__uuidof(Connection));
	//*****************************************************************************
	//****************************************************************************
	//_RecordsetPtr是一个记录集对象。与以上两种对象相比它对记录集提供了更多的控制功能，
	// 如记录锁定、游标控制等
	// _RecordsetPtr m_pRec(__uuidof(Recordset)); 
	m_pRec.CreateInstance(__uuidof(Recordset));
	//*****************************************************************************
	try
	{
		//连接数据库
		m_pCon->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Access.mdb","","",adModeUnknown);
	}
	catch(_com_error e)
	{
		printf(e.ErrorMessage()); //输出错误信息
	}
	try
	{
		m_pRec->Open("SELECT * FROM Lib",
			_variant_t((IDispatch*)m_pCon,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		//adOpenStatic: 静态 adOpenDynamic：动态 adLockOptimistic乐观封锁法 adCmdText：文本查询语句
	}
	catch(_com_error e)
	{
		printf(e.ErrorMessage()); //输出错误信息
	}
}
//读取数据库
void ReadingDB()
{
	printf("\nNumber Name age address tel\n");
	m_pRec->MoveFirst();
	while(!m_pRec->adoEOF)
	{
		printf((_bstr_t)(m_pRec->GetCollect("Number")));
		printf(" ");
		printf((_bstr_t)(m_pRec->GetCollect("Name")));
		printf(" ");
		printf((_bstr_t)(m_pRec->GetCollect("Age")));
		printf(" ");
		printf((_bstr_t)(m_pRec->GetCollect("Address")));
		printf(" ");
		printf((_bstr_t)(m_pRec->GetCollect("Tel")));
		printf("\n");
		m_pRec->MoveNext();
	}
	m_pRec->MoveFirst();
}

//增加数据
void AddDB()
{
	char m_tel[20],m_Number[20],m_age[20],m_Name[20],m_address[20];
	bool m_flag=true; //判断增加操作是否成功的标志
	printf("请输入要增加的Number\n");
	scanf("%s",&m_Number);
	printf("请输入要增加的Name\n");
	scanf("%s",m_Name);
	printf("请输入要增加的Age\n");
	scanf("%s",&m_age);
	printf("请输入要增加的Address\n");
	scanf("%s",m_address);
	printf("请输入要增加的Tel\n");
	scanf("%s",&m_tel);
	try{
		//增加数据到数据库操作
		m_pRec->AddNew(); 
		m_pRec->PutCollect("Number", atol(m_Number));
		m_pRec->PutCollect("Name", _variant_t(m_Name));
		m_pRec->PutCollect("Age", atol(m_age));
		m_pRec->PutCollect("Address", _variant_t(m_address));
		m_pRec->PutCollect("Tel", atol(m_tel));
		m_pRec->Update();
	}
	catch(_com_error e)
	{ 
		m_flag=false;
		printf(e.ErrorMessage());
	}
	if(m_flag) //判断操作成功的输出语句
		printf("增加操作成功\n");
	else
		printf("增加操作失败\n");
	ReadingDB(); //从新读取数据库，并且显示
}
//处理函数
void HandingDB()
{ 
	ReadingDB(); //读取数据库，并且显示
	char m_str[10],m_char;
	while(1)
	{
		printf("\n操作输入:\nQ 退出: A 增加数据\n");
		scanf("%s",m_str); 
		sscanf( m_str, "%c", &m_char ); //将m_str转化为字符，并保存在m_char中
		if('Q'==m_char||'q'==m_char)
			break; //退出程序
		if('A'==m_char||'a'==m_char)
			AddDB(); //增加数据
	}
}
void UnInitialize()
{
    if(m_pRec->State)
	{		
		m_pRec->Close();
	    m_pRec= NULL;
	}
	if(m_pCon->State)
	{
		m_pCon->Close();
	    m_pCon= NULL;
	}

}