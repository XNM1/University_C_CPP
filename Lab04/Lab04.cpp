// Lab04.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

struct AccountData {
	AccountData() {
		for (int i = 0; i < 127; i++) {
			accounts[i].login[i] = NULL;
		}
	}
	void Registration(char *login, char *pass) {
		int Index = Hash(login); bool EqvLogin = 1;
		if (accounts[Index].login != NULL) {
			for (int i = 0; i < strlen(login); ++i) {
				if (accounts[Index].login[i] != login[i]) {
					EqvLogin = 0;
					break;
				}
			}
			if (EqvLogin) {
				return;
			}
			for (int i = 0; i < strlen(login); ++i) {
				accounts[Index].login[i] = login[i];
			}
			accounts[Index].pass = HashPass(pass);
		}
	}
	bool Verification(char *login, char *pass) {
		int Index = Hash(login);
		if (accounts[Index].login != NULL) {
			for (int i = 0; i < strlen(login); ++i) {
				if (accounts[Index].login[i] != login[i]) {
					return 0;
				}
			}
			if (accounts[Index].pass != HashPass(pass)) {
				return 0;
			}
			else {
				return 1;
			}
		}
	}
private:
	struct Account {
		char login[32];
		int pass;
	};
	Account accounts[127];
	int Hash(char *login) {
		int Key = 0;
		for (int i = 0; i < strlen(login); i++) {
			Key += (int)login[i];
		}
		return Key % 127;
	}
	int HashPass(char *pass) {
		int Key = 0;
		for (int i = 0; i < strlen(pass); i++) {
			Key += (int)pass[i];
		}
		return Key;
	}
};

char* EnterPass() {
	char* Pass = (char*)calloc(32, sizeof(char));
	int i = 0;
	while (!_kbhit()) {
		char c = _getch();
		if (c == 8 && i > 0) {
			printf("%s", "\b \b");
			--i;
		}
		else if (c != 13 && i < 32) {
			printf("*");
			Pass[i] = c;
			++i;
		}
		else {
			Pass[i] = '\0';
			printf("\n");
			return Pass;
		}
	}
}

int main()
{
	AccountData Table1;
	char Login[32];
	printf("Login: ");
	gets_s(Login);
	printf("Password: ");
	Table1.Registration(Login, EnterPass());
	for (int i = 0; i < 3; i++) {
		printf("Login: ");
		gets_s(Login);
		printf("Password: ");
		if (Table1.Verification(Login, EnterPass())) {
			printf("Succes");
			break;
		}
	}
	getchar();
    return 0;
}