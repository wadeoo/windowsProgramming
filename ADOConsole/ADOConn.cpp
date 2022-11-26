#include"ADOConn.h"
#include<iostream>
using namespace std;
void ADOConn::OnInitADOConn(_bstr_t openString)
{
	::CoInitialize(NULL);//   初始化OLE/COM库环境   ，为访问ADO接口做准备
	//AfxOleInit();//used in MFC
	HRESULT hr;
	try
	{

		//hr = m_pConnection.CreateInstance("ADODB.Connection");///创建Connection对象
		hr = m_pConnection.CreateInstance(__uuidof(Connection));///创建Connection对象
		//hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Access.mdb", "", "", adModeUnknown);
		hr = m_pConnection->Open(openString, "","", adModeUnknown);
		if (SUCCEEDED(hr))
			cout << endl;
		cout << "连接数据库成功！" << endl;

	}
	catch (_com_error e)///捕捉异常
	{
		//CString errormessage;
		//errormessage.Format("连接数据库失败!\r\n错误信息:%s",e.ErrorMessage());
		//AfxMessageBox(errormessage);///显示错误信息
		cout << "连接数据库失败1！" << endl;


	}
}
_RecordsetPtr & ADOConn::GetRecordSet(_bstr_t bstrSQL,_bstr_t openString)
{
	try
	{
		//连接数据库，如果connection对象为空，则重新连接数据库
		if (m_pConnection == NULL)
			OnInitADOConn(openString);
		//创建记录集对象
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{

		cout << "连接数据库失败2！" << endl;

	}
	//返回记录集
	return m_pRecordset;
}
bool ADOConn::ExecuteSQL(_bstr_t bstrSQL,_bstr_t openString)
{
	try
	{
		//是否已经连接数据库
		if (m_pConnection == NULL)
			OnInitADOConn(openString);
		m_pConnection->Execute(bstrSQL, NULL, adCmdText);
		return true;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(e.Description());
		cout << "连接数据库失败3！" << endl;
		return false;
	}

}
void ADOConn::ExitConnect()
{
	//关闭记录集和连接
	if (m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
	//释放环境
	::CoUninitialize();//关闭ole/com库，释放资源
}
