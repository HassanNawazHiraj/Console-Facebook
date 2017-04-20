#include "views.h"
#include "stdafx.h"
#include "helper.h"
#include <string.h>
#include <stdlib.h>

char AppTitle[] = "Zalim Community";
void Homepage();
void RegisterPage();
void LoginPage();
void AboutPage();
void HomepageMenu(int);


void AboutPage() {
	clrscr();
	EqualLineText(StringCombine(AppTitle," - About"));
	NewLine();
	printf("Program Created By :\t Hasasn Nawaz");
	NewLine();
	printf("Version : 0.1 beta");
	EqualLine(true, true);
	char Menu[2][10];
	strcpy_s(Menu[0], "Go Back");
	strcpy_s(Menu[1], "Exit");
	int x = CreateMenu(Menu[0], 2,10, false);
	(x == 1) ? Homepage() : exit(EXIT_SUCCESS);
}

void LoginPage() {

}

void RegisterPage() {

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
	clrscr();
	EqualLineText(AppTitle);
	//Defining Menu
	char ArrMenu[4][50];
	strcpy_s(ArrMenu[0], "Create a new account");
	strcpy_s(ArrMenu[1], "Login");
	strcpy_s(ArrMenu[2], "About");
	strcpy_s(ArrMenu[3], "Exit");
	HomepageMenu(CreateMenu(ArrMenu[0], 4, 50, true));

}

