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
void FriendsPage();
void FriendsPageMenu(int);
void SearchPage(int);
void SearchPageMenu(int);
void AddFriendMenu(int, char[20]);
void ViewFriends(char[100][255], int, int, int);
void ViewFriendProfile(char[20],int);
void PostOnWall(char[50]);
void ViewFriendProfileMenu(int, char[50], int);
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
	//CreatePostOnWall("hassan", "Ali", "Hello");
	//printf("|%d|", GetLastIdForWallPost("test"));
	//printf("|%ld|", GetTotalWallPosts("hassan"));
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
	if (!(FileExists(test, false))) {
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
	if (FileExists(test, false)) {
		RegisterPage(1);
	}
	else {

	
	char data[500] = "";

	sprintf_s(data, "%s\n%s\n%s", userdata.password, userdata.name, userdata.email);

	CreateFile(test, data);
	//getchar();
	Homepage(1);
	}
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
	if (MsgCode == 2) {
		EqualLineText("User added as your friend");
		NewLine();
	}
	if (MsgCode == 3) {
		EqualLineText("You already are friends with this user");
		NewLine();
	}
	if (MsgCode == 4) {
		EqualLineText("Post created on your wall!");
		NewLine();
	}
	EqualLine(false, true); printf("%s - %s's profile", AppTitle, Cname); EqualLine(true, true);
	char test[100] = "Data//";
	strcat(test, Cusername);
	strcat(test, ".wall");
	
	if (!(FileExists(test, false))) {
		printf("No posts on your wall!");
	}
	else {
		DisplayWallPosts(Cusername, true);
	}

	EqualLine(true, true);
	int tpost = GetTotalWallPosts(Cusername);
	char ArrMenu[4][50];
	strcpy_s(ArrMenu[0], "Post on your profile");
	strcpy_s(ArrMenu[1], "see your friends");
	strcpy_s(ArrMenu[2], "search someone");
	strcpy_s(ArrMenu[3], "Exit");
	ProfilePageMenu(CreateMenu(ArrMenu[0], 4, 50, true, true), tpost+10);
}

void ProfilePageMenu(int x, int max_post) {
	//printf("Your choice %d", x);
	switch (x) {
	case 1:
		PostOnWall(Cusername);
		break;

	case 2:
		FriendsPage();
		break;

	case 3:
		SearchPage(0);
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

void show_post(char userwall[50], int num) {
	clearscreen();
	char user[20], post[255]; int tpost = GetTotalWallPosts(Cusername);
	strcpy(user, Cusername);
	GetWallPost((num-10)*2, user, post, tpost);
	EqualLine(false, true); printf("Viewing %s's post on your profile", user); EqualLine(true, true);
	printf("%s : \n%s", user, post);
	EqualLine(true, true);
	printf("no replies");
}

void FriendsPage() {
	clearscreen();
	int tf = GetTotalFriends(Cusername);
	EqualLine(false, true); printf("%s's Friends (%d)", Cname, tf); EqualLine(true, true);
	if (tf == 0) {
		printf("You don't have any friends :(");
		EqualLine(true, true);
	
	char ArrMenu[3][50];
	strcpy_s(ArrMenu[0], "Search someone");
	strcpy_s(ArrMenu[1], "Go back");
	strcpy_s(ArrMenu[2], "Exit");
	FriendsPageMenu(CreateMenu(ArrMenu[0], 3, 50, true, true));

	} else {
		char friends[100][255];
		int total, limit, choice;
		ShowAllFriends(Cusername,friends,&total,&limit,&choice);
		ViewFriends(friends, total, limit, choice);
	}
}
void FriendsPageMenu(int x) {
	switch (x) {
	case 1:
		SearchPage(0);
		break;

	case 2:
		ProfilePage(0);
		break;

	case 3:
		exit(EXIT_SUCCESS);
		break;
	}
}

void SearchPage(int x = 0) {
	clearscreen();
	switch (x) {
	case 1:
		EqualLine(false, true);
		printf("You can't search yourself!");
		NewLine();
		break;
	}
	EqualLine(false, true); printf("Zalim Community - Search"); EqualLine(true, true);
	char user[20];
	printf("Enter Name : ");
	fflush(stdin);
	scanf("%s", user);
	getchar();
	//InDataFolder(user);
	if (FileExists(user, true)) {
		if (strcmp(user,Cusername) == 0) {
			SearchPage(1);
		}
		else {
			printf("User Found!\n");
			char ArrMenu[3][50];
			strcpy_s(ArrMenu[0], "Add as friend");
			strcpy_s(ArrMenu[1], "Go back");
			strcpy_s(ArrMenu[2], "Exit");
			AddFriendMenu(CreateMenu(ArrMenu[0], 3, 50, true, true), user);
		}
		
	}
	else {
	printf("No Such User");
	EqualLine(true, true);
	char ArrMenu[3][50];
	strcpy_s(ArrMenu[0], "Search Again");
	strcpy_s(ArrMenu[1], "Go back");
	strcpy_s(ArrMenu[2], "Exit");
	SearchPageMenu(CreateMenu(ArrMenu[0], 3, 50, true, true));
	//getchar();
	}
}

void SearchPageMenu(int x) {
	switch (x) {
	case 1:
		SearchPage(0);
		break;

	case 2:
		ProfilePage(0);
		break;

	case 3:
		exit(EXIT_SUCCESS);
		break;
	}
}
void AddFriendMenu(int x, char user[20]) {
	switch (x) {
	case 1:
		if (AddFriend(Cusername, user)) {
			ProfilePage(2);
		}
		else {
			ProfilePage(3);
		}
		break;
	case 2:
		ProfilePage(0);
		break;
	case 3:
		exit(EXIT_SUCCESS);
		break;
	}
}

void ViewFriends(char friends[100][255], int total, int limit, int choice) {
	printf("\n%d,%d,%d", total, limit, choice);
	for (int i = 0; i < (total - 3); i++) {
		ViewFriendProfile(friends[i],0);
	}
	if (choice == (total - 2)) {
		SearchPage(0);
	}
	if (choice == (total - 1)) {
		ProfilePage(0);
	}
	if (choice == total) {
		exit(EXIT_SUCCESS);
	}
}

void ViewFriendProfile(char user[20], int MsgCode=0) {
	clearscreen();
	if (MsgCode == 1) {

		EqualLineText("Error - Invalid Choice");
		NewLine();
	}
	if (MsgCode == 2) {
		EqualLineText("Post Created!");
		NewLine();
	}
	
	EqualLine(false, true); printf("%s - %s's profile (your friend)", AppTitle, user); EqualLine(true, false);
	char test[100] = "Data//";
	strcat(test, user);
	strcat(test, ".wall");	
	int i = 0;
	if (!(FileExists(test, false))) {
		printf("\nNo posts on %s's wall!", user);
	}
	else {
		int tpost = GetTotalWallPosts(user);
	//	printf("%d posts on %s's wall!", tpost, user);
		EqualLine(true, true);
		//display posts
		//for (i = 0; i < (tpost * 2); i += 2) {
		//	char  u[20],post[255];
		//	strcpy(u, user);
		//	//strcpy(user, Cusername);
		//	GetWallPost(i, u, post, tpost);
		//	printf("%d. (%s) : \n%s\n", ((i / 2) + 10), u, post);
		//}
		DisplayWallPosts(user, false);
	}

	EqualLine(true, true);
	int tpost = GetTotalWallPosts(user);
	char ArrMenu[3][50];
	strcpy_s(ArrMenu[0], "Post on his profile");
	strcpy_s(ArrMenu[1], "back");
	strcpy_s(ArrMenu[2], "Exit");
	ViewFriendProfileMenu(CreateMenu(ArrMenu[0], 3, 50, true, true),user, tpost+10);//, ((i / 2) + 10);
}

void ViewFriendProfileMenu(int x, char u[50], int max_post) {
	switch (x) {
	case 1:
		PostOnWall(u);
		break;
	case 2:
		ProfilePage(0);
		break;
	case 3:
		exit(EXIT_SUCCESS);
		break;
	default:
		if (x >= 10 && x < max_post) {
			show_post(x);
		}
		else {
			ViewFriendProfile(u,1);
		}
		if (x > 20) {
			//invalid choice
			ViewFriendProfile(u, 1);
		}
	}
}

void PostOnWall(char u[50]) {
	char post[255];
	clearscreen();
	EqualLine(false, true); printf("Post on %s's Profile!", u); EqualLine(true, true);
	printf("Enter your post (255 max) : ");
	fgets(post, 255, stdin);
	CreatePostOnWall(u, Cusername, post);
	if (strcmp(u, Cusername) == 0) {
		ProfilePage(4);
	}
	else {
		ViewFriendProfile(u, 2);
	}
}