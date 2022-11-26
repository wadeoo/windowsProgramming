#include <stdio.h>
//��������ADO���ļ�ʱ�򣬻�������� 4146�������������û��ϵ�ģ�����ʹ����һ�����������
#pragma warning(disable: 4146)
//����ADO���ļ� ע��C:\Program Files\Common Files\System\ado\msado15.dll����ָϵͳ���£�
//������ϵͳ����D�̵Ļ� ��ôӦ����D:\Program Files\Common Files\System\ado\msado15.dll 
#import "C:\Program Files\Common Files\System\ado\msado15.dll" no_namespace rename("EOF", "adoEOF")

_ConnectionPtr m_pCon; //����Connectionָ��
_RecordsetPtr m_pRec; //����Recordsetָ��
void Initialize(); //��ʼ����Դ���� 
void ReadingDB(); //��ȡ���ݿ����
void AddDB(); //�������ݲ���
void UnInitialize(); //ж����Դ����
void HandingDB(); //���ݴ������

int main(int argc, char* argv[])
{
	Initialize(); //��ʼ��
	HandingDB(); //������
	UnInitialize(); //ж����Դ
	return 0;
}

//��ʼ��
void Initialize()
{
	::CoInitialize(NULL); //��ʼ��OLE/COM�⻷��
	//****************************************************************************
	// _ConnectionPtrͨ������������һ���������ӻ�ִ��һ���������κν����SQL��䣬
	// ��һ���洢���̡�
	// _ConnectionPtr m_pCon(__uuidof(Connection)); 
	m_pCon.CreateInstance(__uuidof(Connection));
	//*****************************************************************************
	//****************************************************************************
	//_RecordsetPtr��һ����¼���������������ֶ���������Լ�¼���ṩ�˸���Ŀ��ƹ��ܣ�
	// ���¼�������α���Ƶ�
	// _RecordsetPtr m_pRec(__uuidof(Recordset)); 
	m_pRec.CreateInstance(__uuidof(Recordset));
	//*****************************************************************************
	try
	{
		//�������ݿ�
		m_pCon->Open("Provider=Microsoft.Jet.OLEDB.4.0;Data Source=Access.mdb","","",adModeUnknown);
	}
	catch(_com_error e)
	{
		printf(e.ErrorMessage()); //���������Ϣ
	}
	try
	{
		m_pRec->Open("SELECT * FROM Lib",
			_variant_t((IDispatch*)m_pCon,true),
			adOpenStatic,
			adLockOptimistic,
			adCmdText);
		//adOpenStatic: ��̬ adOpenDynamic����̬ adLockOptimistic�ֹ۷����� adCmdText���ı���ѯ���
	}
	catch(_com_error e)
	{
		printf(e.ErrorMessage()); //���������Ϣ
	}
}
//��ȡ���ݿ�
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

//��������
void AddDB()
{
	char m_tel[20],m_Number[20],m_age[20],m_Name[20],m_address[20];
	bool m_flag=true; //�ж����Ӳ����Ƿ�ɹ��ı�־
	printf("������Ҫ���ӵ�Number\n");
	scanf("%s",&m_Number);
	printf("������Ҫ���ӵ�Name\n");
	scanf("%s",m_Name);
	printf("������Ҫ���ӵ�Age\n");
	scanf("%s",&m_age);
	printf("������Ҫ���ӵ�Address\n");
	scanf("%s",m_address);
	printf("������Ҫ���ӵ�Tel\n");
	scanf("%s",&m_tel);
	try{
		//�������ݵ����ݿ����
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
	if(m_flag) //�жϲ����ɹ���������
		printf("���Ӳ����ɹ�\n");
	else
		printf("���Ӳ���ʧ��\n");
	ReadingDB(); //���¶�ȡ���ݿ⣬������ʾ
}
//������
void HandingDB()
{ 
	ReadingDB(); //��ȡ���ݿ⣬������ʾ
	char m_str[10],m_char;
	while(1)
	{
		printf("\n��������:\nQ �˳�: A ��������\n");
		scanf("%s",m_str); 
		sscanf( m_str, "%c", &m_char ); //��m_strת��Ϊ�ַ�����������m_char��
		if('Q'==m_char||'q'==m_char)
			break; //�˳�����
		if('A'==m_char||'a'==m_char)
			AddDB(); //��������
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