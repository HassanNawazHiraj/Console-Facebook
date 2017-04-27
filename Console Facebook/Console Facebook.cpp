#include "stdafx.h"
#include "helper.h"
#include <string.h>
#include <stdlib.h>

struct USD {
	char username[50];
	char password[50];
	char email[50];
	char name[50];
} usd;
char AppTitle[] = "Zalim Community";
void Homepage();
void RegisterPage(int);
void LoginPage();
void AboutPage();
void HomepageMenu(int);

int main()
{
	
	Homepage();
	
	//fflush(stdin);
	getchar();
	return 0;
}


void AboutPage() {
	clearscreen();
	EqualLine(false,true); printf("%s %s", AppTitle, "- About"); EqualLine(true,true);
	
	printf("Program Created By :\t Hasasn Nawaz");
	NewLine();
	printf("Version : 0.1 beta");
	EqualLine(true, true);
	char Menu[2][10];
	strcpy_s(Menu[0], "Go Back");
	strcpy_s(Menu[1], "Exit");
	int x = CreateMenu(Menu[0], 2, 10, false);
	(x == 1) ? Homepage() : exit(EXIT_SUCCESS);
}

void LoginPage() {
	printf("test");
}

void RegisterPage(int ErrorCode=0) {
	struct USD userdata;
	 clearscreen();
	if (ErrorCode == 1) {

		EqualLineText("Error - Username already exists");
		NewLine();
	}
	EqualLine(false, true); printf("%s %s", AppTitle, "- Register"); EqualLine(true, true);

	NewLine();
	char ArrRegister[4][50];
	strcpy_s(ArrRegister[0], "Name");
	strcpy_s(ArrRegister[1], "Username");
	strcpy_s(ArrRegister[2], "Password");
	strcpy_s(ArrRegister[3], "Email");
	char result[4][50];
	MultiInputs(ArrRegister[0], result[0], 4, 50, true);
	getchar();
	//populate userdata
	strcpy(userdata.name, result[0]);
	strcpy(userdata.username, result[1]);
	strcpy(userdata.password, result[2]);
	strcpy(userdata.email, result[3]);


	//for (int i = 0; i < 4; i++) {
	//	CreateFile("test.txt", result[i]);
	//}
	//char *test = "Data/users/";
	//strcat(test, userdata.username);

	if (FileExists(userdata.username)) {
		RegisterPage(1);
	}
	
	CreateFile(userdata.username, userdata.name);
	getchar();

}

void HomepageMenu(int choice) {
	switch (choice) {
	case 1:
		RegisterPage();
		break;
	case 2:
		LoginPage();
		break;
	case 3:
		AboutPage();
		break;
	case 4:
		exit(EXIT_SUCCESS);
	default:
		printf("Invalid Choice");
		exit(EXIT_FAILURE);
	}

}

void Homepage() {
	clearscreen();
	EqualLineText(AppTitle);
	//Defining Menu
	char ArrMenu[4][50];
	strcpy_s(ArrMenu[0], "Create a new account");
	strcpy_s(ArrMenu[1], "Login");
	strcpy_s(ArrMenu[2], "About");
	strcpy_s(ArrMenu[3], "Exit");
	HomepageMenu(CreateMenu(ArrMenu[0], 4, 50, true));

}

