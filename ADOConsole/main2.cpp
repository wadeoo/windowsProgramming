#include "ADO.h"
#include <iostream>
using namespace std;

ADO ado;
void readingOut();//��ȡ���� 
void mainHandling();

int main(){
	mainHandling();
	return 0;
}


void mainHandling(){
	int chosenDbNum;
	char* databaseFileName;
	char* username;
	char* password;


	cout << "\n������Ҫ���ӵ����ݿ�����:\n 1(SqlServer), 2(MySql), 3(Access)" << endl;
	cin >> chosenDbNum;

	ado = ADO(chosenDbNum);

	cout << "\n���������ݿ��ļ���" << endl;
	cin >> databaseFileName;

	cout << "\n�������û���" << endl;
	cin >> username;

	cout << "\n����������" << endl;
	cin >> password;

	if (ado.InitConn(username, password, databaseFileName)){
		cout << "���ݿ����ӳɹ�"<<endl;
	}
	else{
		cout << "���ݿ�����ʧ��"<<endl;
	}



	

}