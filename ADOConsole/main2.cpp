#include "ADO.h"
#include <iostream>
using namespace std;

ADO ado;
void readingOut();//读取操作 
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


	cout << "\n请输入要连接的数据库类型:\n 1(SqlServer), 2(MySql), 3(Access)" << endl;
	cin >> chosenDbNum;

	ado = ADO(chosenDbNum);

	cout << "\n请输入数据库文件名" << endl;
	cin >> databaseFileName;

	cout << "\n请输入用户名" << endl;
	cin >> username;

	cout << "\n请输入密码" << endl;
	cin >> password;

	if (ado.InitConn(username, password, databaseFileName)){
		cout << "数据库连接成功"<<endl;
	}
	else{
		cout << "数据库连接失败"<<endl;
	}



	

}