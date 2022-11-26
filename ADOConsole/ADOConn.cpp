#include"ADOConn.h"
#include<iostream>
using namespace std;
void ADOConn::OnInitADOConn(_bstr_t openString)
{
	::CoInitialize(NULL);//   ��ʼ��OLE/COM�⻷��   ��Ϊ����ADO�ӿ���׼��
	//AfxOleInit();//used in MFC
	HRESULT hr;
	try
	{

		//hr = m_pConnection.CreateInstance("ADODB.Connection");///����Connection����
		hr = m_pConnection.CreateInstance(__uuidof(Connection));///����Connection����
		//hr = m_pConnection->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Access.mdb", "", "", adModeUnknown);
		hr = m_pConnection->Open(openString, "","", adModeUnknown);
		if (SUCCEEDED(hr))
			cout << endl;
		cout << "�������ݿ�ɹ���" << endl;

	}
	catch (_com_error e)///��׽�쳣
	{
		//CString errormessage;
		//errormessage.Format("�������ݿ�ʧ��!\r\n������Ϣ:%s",e.ErrorMessage());
		//AfxMessageBox(errormessage);///��ʾ������Ϣ
		cout << "�������ݿ�ʧ��1��" << endl;


	}
}
_RecordsetPtr & ADOConn::GetRecordSet(_bstr_t bstrSQL,_bstr_t openString)
{
	try
	{
		//�������ݿ⣬���connection����Ϊ�գ��������������ݿ�
		if (m_pConnection == NULL)
			OnInitADOConn(openString);
		//������¼������
		m_pRecordset.CreateInstance(_uuidof(Recordset));
		m_pRecordset->Open(bstrSQL, m_pConnection.GetInterfacePtr(), adOpenDynamic, adLockOptimistic, adCmdText);
	}
	catch (_com_error e)
	{

		cout << "�������ݿ�ʧ��2��" << endl;

	}
	//���ؼ�¼��
	return m_pRecordset;
}
bool ADOConn::ExecuteSQL(_bstr_t bstrSQL,_bstr_t openString)
{
	try
	{
		//�Ƿ��Ѿ��������ݿ�
		if (m_pConnection == NULL)
			OnInitADOConn(openString);
		m_pConnection->Execute(bstrSQL, NULL, adCmdText);
		return true;
	}
	catch (_com_error e)
	{
		//AfxMessageBox(e.Description());
		cout << "�������ݿ�ʧ��3��" << endl;
		return false;
	}

}
void ADOConn::ExitConnect()
{
	//�رռ�¼��������
	if (m_pRecordset != NULL)
		m_pRecordset->Close();
	m_pConnection->Close();
	//�ͷŻ���
	::CoUninitialize();//�ر�ole/com�⣬�ͷ���Դ
}
