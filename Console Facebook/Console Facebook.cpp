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
float AppVersion = 0.5;
void Homepage(int);
void RegisterPage(int);
void LoginPage(int);
void AboutPage();
void HomepageMenu(int);
void ProfilePage(int);
void ProfilePageMenu(int, int);
void ShowPost(char[50], int, int);
void FriendsPage();
void FriendsPageMenu(int);
void SearchPage(int);
void SearchPageMenu(int);
void AddFriendMenu(int, char[20]);
void ViewFriends(char[100][255], int, int, int);
void ViewFriendProfile(char[20],int);
void PostOnWall(char[50]);
void ViewFriendProfileMenu(int, char[50], int);
void ShowPostMenu(int, char[50], int);
void PostCommentOnWall(char [50], int );
static char Cname[50];
static char Cemail[50];
static char Cusername[50];
int main()
{
	//system("color F9");
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
	ZalimColor(); EqualLine(false, true); printf("%s %s", AppTitle, "- About"); EqualLine(true, true); WhiteColor(true);
	
	printf("Program Created By :\t Hasasn Nawaz");
	NewLine();
	printf("Version : %.1f beta", AppVersion);
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
		ErrorColor();
		EqualLineText("Error - Wrong Username/Password");
		WhiteColor(true);
		NewLine();
	}
	ZalimColor(); EqualLine(false, true); printf("%s %s", AppTitle, "- Login"); EqualLine(true, true); WhiteColor(true);
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

		ErrorColor(); EqualLineText("Error - Username already exists"); WhiteColor(true);
		NewLine();
	}
	ZalimColor(); EqualLine(false, true); printf("%s %s", AppTitle, "- Register"); EqualLine(true, true); WhiteColor(true);

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

	CreateFile1(test, data);
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
		SuccessColor(); EqualLineText("User created successfully!"); WhiteColor(true);
		NewLine();
	}


	ZalimColor();
	EqualLineText(AppTitle);
	WhiteColor(true);
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

		ErrorColor(); EqualLineText("Error - Invalid Choice"); WhiteColor(true);
		NewLine();
	}
	if (MsgCode == 2) {
		SuccessColor(); EqualLineText("User added as your friend"); WhiteColor(true);
		NewLine();
	}
	if (MsgCode == 3) {
		InfoTextColor(); EqualLineText("You already are friends with this user"); WhiteColor(true);
		NewLine();
	}
	if (MsgCode == 4) {
		SuccessColor(); EqualLineText("Post created on your wall!"); WhiteColor(true);
		NewLine();
	}
	if (MsgCode == 5) {
		SuccessColor(); EqualLineText("Comment Posted!"); WhiteColor(true);
		NewLine();
	}
	ZalimColor();
	EqualLine(false, true); printf("%s - %s's profile", AppTitle, Cname); EqualLine(true, true);
	WhiteColor(true);
	char test[100] = "Data//";
	strcat(test, Cusername);
	strcat(test, ".wall");
	InfoTextColor();
	EqualLine(false, true);
	if (!(FileExists(test, false))) {
		 printf("No posts on your wall!");
	}
	else {
		DisplayWallPosts(Cusername, true);
	}

	EqualLine(true, true);
	WhiteColor(true);
	int tpost = GetTotalWallPosts(Cusername);
	char ArrMenu[5][50];
	strcpy_s(ArrMenu[0], "Post on your profile");
	strcpy_s(ArrMenu[1], "see your friends");
	strcpy_s(ArrMenu[2], "search someone");
	strcpy_s(ArrMenu[3], "Logout");
	strcpy_s(ArrMenu[4], "Exit");
	ProfilePageMenu(CreateMenu(ArrMenu[0], 5, 50, true, true), tpost+10);
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
		strcpy(Cusername, "");
		strcpy(Cname, "");
		strcpy(Cemail, "");
		Homepage(0);
		break;

	case 5:
		exit(EXIT_FAILURE);
		break;

	default :
		if (x >= 10 && x < max_post) {
			ShowPost(Cusername,x,0);
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

void ShowPost(char userwall[50], int num, int MsgCode) {
	clearscreen();
	switch (MsgCode) {
	case 1:
		SuccessColor(); EqualLineText("Post Liked!"); WhiteColor(true);
		NewLine();
		break;
	case 2:
		InfoTextColor(); EqualLineText("You Already Liked this post"); WhiteColor(true);
		NewLine();
		
		break;
	}
	char user[20], post[255]; int tpost = GetTotalWallPosts(userwall);
	strcpy(user, userwall);
	char poster[50]; int likes;
	CommentStruct c[10];
	GetWallPost(num-10, user, poster, post, tpost, &likes, c);
	ZalimColor();
	EqualLine(false, true); (strcmp(Cusername, userwall) == 0) ? printf("Viewing %s's post on your profile", poster) : printf("Viewing %s's post on %s's profile", poster, userwall); EqualLine(true, true);
	WhiteColor(true);
	printf("%s (%d likes) : \n", poster,likes);
	WhiteColor(false); printf("%s", post); WhiteColor(true);
	EqualLine(true, true);
	// Comments & replies
	int j = 0;


	if ((strcmp(c[0].user, "") == 0) && (strcmp(c[0].comment, "") == 0)) {
		InfoTextColor(); printf("No Comments on this post"); WhiteColor(true);
	}
	else {
		while (j <= 4) {
			if ((strcmp(c[j].user, "") == 0) && (strcmp(c[j].comment, "") == 0)) {
				
			}
			else {
				// read comments
				printf("%s : \n", c[j].user);
				WhiteColor(false); printf("%s\n", c[j].comment); WhiteColor(true);
			}
			j++;
		}
	}

	EqualLine(true, true);
	char ArrMenu[4][50];
	strcpy_s(ArrMenu[0], "Comment on this post");
	strcpy_s(ArrMenu[1], "Like this post");
	strcpy_s(ArrMenu[2], "Go back");
	strcpy_s(ArrMenu[3], "Exit");
	ShowPostMenu(CreateMenu(ArrMenu[0], 4, 50, true, true), userwall, num);


}

void ShowPostMenu(int x, char user[50], int num) {
	switch (x) {
	case 1:
		PostCommentOnWall(user, num);
		break;

	case 2:
		if (LikePost(num - 10, user, Cusername)) {
			ShowPost(user, num, 1);
		}
		else {
			ShowPost(user, num, 2);
		}
		//printf("exec");
		break;

	case 3:
		(strcmp(user, Cusername) == 0) ? ProfilePage(0) : ViewFriendProfile(user, 0);
		break;

	case 4:
		exit(EXIT_SUCCESS);
		break;

	}
}



void FriendsPage() {
	clearscreen();
	int tf = GetTotalFriends(Cusername);
	ZalimColor(); EqualLine(false, true); printf("%s's Friends (%d)", Cname, tf); EqualLine(true, true); WhiteColor(true);
	if (tf == 0) {
		InfoTextColor();  WhiteColor(false);  printf("You don't have any friends :(");
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
		//EqualLine(false, true);
		//printf("");
		//NewLine();
		ErrorColor();  EqualLineText("You can't search yourself!"); WhiteColor(true);
		break;
	}
	ZalimColor(); EqualLine(false, true); printf("Zalim Community - Search"); EqualLine(true, true); WhiteColor(true);
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
		ErrorColor();  printf("No Such User"); WhiteColor(true);
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
//	printf("\n%d,%d,%d", total, limit, choice);
	for (int i = 0; i < (total - 3); i++) {
		if(i+1 == choice) ViewFriendProfile(friends[i],0);
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

		ErrorColor();  EqualLineText("Error - Invalid Choice"); WhiteColor(true);
		NewLine();
	}
	if (MsgCode == 2) {
		SuccessColor(); EqualLineText("Post Created!"); WhiteColor(true);
		NewLine();
	}
	if (MsgCode == 3) {
		SuccessColor(); EqualLineText("Comment Posted!"); WhiteColor(true);
		NewLine();
	}
	
	ZalimColor(); EqualLine(false, true); printf("%s - %s's profile (your friend)", AppTitle, user); EqualLine(true, false); WhiteColor(true);
	char test[100] = "Data//";
	strcat(test, user);
	strcat(test, ".wall");	
	int i = 0;
	if (!(FileExists(test, false))) {
		InfoTextColor();
		printf("\nNo posts on %s's wall!", user);
		WhiteColor(true);
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
			ShowPost(u,x,0);
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
	ZalimColor(); EqualLine(false, true); printf("Post on %s's Profile!", u); EqualLine(true, true); WhiteColor(true);
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

void PostCommentOnWall(char u[50], int num) {
	char comment[80];
	clearscreen();
	ZalimColor(); EqualLine(false, true); printf("Comment on %s's Post!", u); EqualLine(true, true); WhiteColor(true);
	printf("Enter your Comment (80 max) : ");
	fgets(comment, 80, stdin);
	//CreatePostOnWall(u, Cusername, post);
	CreateCommentOnPost(u, Cusername, comment, num-10);
	if (strcmp(u, Cusername) == 0) {
		ShowPost(u, num, 0);
	}
	else {
		//ViewFriendProfile(u, 3);
		ShowPost(u, num, 0);
	}
}