#include "stdafx.h"
#include "helper.h"
#include <string.h>
#include <stdlib.h>

struct UserData {
	char username[50];
	char password[50];
	char email[50];
	char name[50];
} ud;

char AppTitle[] = "Zalim Community";
void Homepage(int);
void RegisterPage(int);
void LoginPage(int);
void AboutPage();
void HomepageMenu(int);
void ProfilePage(int);
void ProfilePageMenu(int, int);
void show_post(int);
static char Cname[50];
static char Cemail[50];
static char Cusername[50];
int main()
{
	
	Homepage(0);
	
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
	int x = CreateMenu(Menu[0], 2, 10, false, false);
	(x == 1) ? Homepage(0) : exit(EXIT_SUCCESS);
}

void LoginPage(int ErrorCode=0) {
	struct UserData userdata;
	struct UserData returndata;
	clearscreen();
	if (ErrorCode == 1) {
		EqualLineText("Error - Wrong Username/Password");
		NewLine();
	}
	EqualLine(false, true); printf("%s %s", AppTitle, "- Login"); EqualLine(true, true);
	NewLine();
	char ArrLogin[2][50];
	char ArrResult[2][50];
	strcpy_s(ArrLogin[0], "Username");
	strcpy_s(ArrLogin[1], "Password");
	MultiInputs(ArrLogin[0], ArrResult[0], 2, 50, true);
	getchar();
	strcpy_s(userdata.username, ArrResult[0]);
	strcpy_s(userdata.password, ArrResult[1]);

	//check wither the file exists or not
	char test[100] = "Data//";
	strcat(test, userdata.username);
	if (!(FileExists(test))) {
		LoginPage(1);
	} else {


	char logindata[3][50];
	Login(test,logindata);
	strcpy_s(returndata.password, logindata[0]);
	strcpy_s(returndata.name, logindata[1]);
	strcpy_s(returndata.email, logindata[2]);

	if (!(strcmp(returndata.password,userdata.password))) {
		printf("success");
		strcpy_s(Cusername, userdata.username);
		strcpy_s(Cemail, returndata.email);
		strcpy_s(Cname, returndata.name);
		ProfilePage(0);
	}
	else {
		LoginPage(1);
	}

	}
}

void RegisterPage(int ErrorCode = 0) {
	struct UserData userdata;
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
	strcpy_s(userdata.name, result[0]);
	strcpy_s(userdata.username, result[1]);
	strcpy_s(userdata.password, result[2]);
	strcpy_s(userdata.email, result[3]);


	//for (int i = 0; i < 4; i++) {
	//	CreateFile("test.txt", result[i]);
	//}
	//char *test = "Data/users/";
	//strcat(test, userdata.username);
	char test[100] = "Data//";
	strcat(test, userdata.username);
	if (FileExists(test)) {
		RegisterPage(1);
	}
	char data[500] = "";

	sprintf_s(data, "%s\n%s\n%s", userdata.password, userdata.name, userdata.email);

	CreateFile(test, data);
	//getchar();
	Homepage(1);
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

void Homepage(int MsgCode = 0) {
	clearscreen();

	if (MsgCode == 1) {
		EqualLineText("User created successfully!");
		NewLine();
	}

	EqualLineText(AppTitle);
	//Defining Menu
	char ArrMenu[4][50];
	strcpy_s(ArrMenu[0], "Create a new account");
	strcpy_s(ArrMenu[1], "Login");
	strcpy_s(ArrMenu[2], "About");
	strcpy_s(ArrMenu[3], "Exit");
	HomepageMenu(CreateMenu(ArrMenu[0], 4, 50, true, false));

}

void ProfilePage(int MsgCode = 0) {
	clearscreen();
	if (MsgCode == 1) {

		EqualLineText("Error - Invalid Choice");
		NewLine();
	}
	EqualLine(false, true); printf("%s - %s's profile", AppTitle, Cname); EqualLine(true, true);
	char test[100] = "Data//";
	strcat(test, Cusername);
	strcat(test, ".wall");
	int i = 0;
	if (!(FileExists(test))) {
		printf("No posts on your wall!");
	}
	else {
		int tpost = GetTotalWallPosts(Cusername);
		printf("%d posts on your wall!", tpost);
		EqualLine(true, true);
		//display posts
		for (i = 0; i < (tpost*2); i+=2) {
			char user[20], post[255];
			strcpy(user, Cusername);
			GetWallPost(i, user, post, tpost);
			printf("%d. (%s) : \n%s\n",((i/2)+10), user, post);
		}
	}

	EqualLine(true, true);
	char ArrMenu[4][50];
	strcpy_s(ArrMenu[0], "Post on your profile");
	strcpy_s(ArrMenu[1], "see your friends");
	strcpy_s(ArrMenu[2], "search someone");
	strcpy_s(ArrMenu[3], "Exit");
	ProfilePageMenu(CreateMenu(ArrMenu[0], 4, 50, true, true), ((i/2)+10));
}

void ProfilePageMenu(int x, int max_post) {
	//printf("Your choice %d", x);
	switch (x) {
	case 1:

		break;

	case 2:

		break;

	case 3:

		break;

	case 4:
		exit(EXIT_FAILURE);
		break;

	default :
		if (x >= 10 && x < max_post) {
			show_post(x);
		}
		else {
			ProfilePage(1);
		}
		if (x > 20) {
			//invalid choice
			ProfilePage(1);
		}
	}
}

void show_post(int num) {
	clearscreen();
	char user[20], post[255]; int tpost = GetTotalWallPosts(Cusername);
	strcpy(user, Cusername);
	GetWallPost((num-10)*2, user, post, tpost);
	EqualLine(false, true); printf("Viewing %s's post on your profile", user); EqualLine(true, true);
	printf("%s : \n%s", user, post);
	EqualLine(true, true);
	printf("no replies");
}

