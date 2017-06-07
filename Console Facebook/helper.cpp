#include "stdafx.h"
#include "helper.h"
#include <stdlib.h>
#include <string>
#include <iostream>
#include <windows.h>


/*
Used to display New Line
*/

void NewLine() {
	printf("\n");
}

void CreateFile1(char* filename, char* data) {

	FILE *fp = NULL;
	fp = fopen(filename, "w");
	fprintf(fp, "%s", data);
	fclose(fp);
}

void AppendFile(char* filename, char* data, bool idf, bool newline) {
	char test[255];
	if (idf) {
	strcpy(test, "Data//");
	strcat(test, filename);
	
	}
	else {
		strcpy(test, filename);
	}
	FILE *fp = NULL;
	fp = fopen(test, "a");
	(newline) ? fprintf(fp, "%s\n", data) : fprintf(fp, "%s", data);
	fclose(fp);
}

void Login(char* filename, char result[3][50]) {
	FILE *fp;
	char buff[255];

	fp = fopen(filename, "r");

	buff[0] = '\0';
	for (int i = 0; i < 3; i++) {
		fgets(buff, 255, (FILE*)fp);
		buff[strlen(buff) - 1] = '\0'; /* Remove \n at end*/

		strcpy(result[i], buff);
		buff[0] = '\0';
	}
	fclose(fp);

	
}

void GetWallPost(int number, char user[20], char poster[50], char post[255], int total, int* likes, CommentStruct c[10]) {
	
	FILE *fp;
//	char buff[255];
	char test[100] = "Data//";
	strcat(test, user);
	strcat(test, ".wall");
	fp = fopen(test, "r");
//	buff[0] = '\0';
	WallPostStruct w;
	for (int i = 0; i <= total; i++) {
		fread(&w, sizeof(w), 1, fp);
		if (i == number) {
			strcpy(poster, w.User);
			strcpy(post, w.Post);
			*likes = w.Likes;
			for (int j = 0; j < 10; j++) {
				c[j] = w.comments[j];
			}
			c = w.comments;
		}
		//fgets(buff, 255, (FILE*)fp);
		//if (buff[strlen(buff) - 1] == '\n') {
		//	buff[strlen(buff) - 1] = '\0'; /* Remove \n at end*/
		//}
		//else {
		//	buff[strlen(buff)] = '\0';
		//}
		//if (i == number) {
		//	strcpy(user, buff);
		//}
		//if (i == (number + 1)) {
		//	strcpy(post, buff);
		//}
		//
		//buff[0] = '\0';
	}
	fclose(fp);
}

int GetTotalWallPosts(char user[20]) {
	
	int count = 0;
	FILE *fp2;
	char buff[255];
	char test[100] = "Data//";
	strcat(test, user);
	strcat(test, ".wall");
	if (FileExists(test, false)) {
		fp2 = fopen(test, "r");
		buff[0] = '\0';
		fseek(fp2, 0, 2);
		long int res = ftell(fp2);
		fclose(fp2);
		return (int)res / sizeof(WallPostStruct);
	}
	return 0;
	/*  Old code for sequential file
	int count = 0;
	FILE *fp2;
	char buff[255];
	char test[100] = "Data//";
	strcat(test, user);
	strcat(test, ".wall");
	fp2 = fopen(test, "r");
	buff[0] = '\0';
	char ch = ' ';
	while (!feof(fp2))
	{
		ch = fgetc(fp2);
		if (ch == '\n')
		{
			count++;
		}
	}
	fclose(fp2);
	return (count+1)/2;
	*/
}

void ShowAllFriends(char user[20], char friends[100][255], int* total, int* limit, int* choice) {
	
	int totalf = GetTotalFriends(user);
	FILE *fp2;
	char buff[255];
	char test[100] = "Data//";
	strcat(test, user);
	strcat(test, ".friends");
	fp2 = fopen(test, "r");
	buff[0] = '\0';
	
	int i = 0;
	while (i<totalf)
	{
		fgets(buff, 255, (FILE*)fp2);
		buff[strlen(buff) - 1] = '\0';
		if (!(friends[i] == NULL)) {
			strcpy(friends[i], buff);
		}
		
		i++;
		buff[0] = '\0';
	}
	fclose(fp2);
//	friends[i] = "Search Someone";
	strcpy(friends[i], "search someone");
	strcpy(friends[i+1], "go back");
	strcpy(friends[i+2], "exit");
	
	*total = i+3;
	*limit = 255;
	*choice = CreateMenu(friends[0], i + 3, 255, true, false);
	
}

int GetTotalFriends(char user[20]) {
	
	int count = 0;
	
	char buff[255];
	char test[100] = "Data//";
	strcat(test, user);
	strcat(test, ".friends");

	if (!(FileExists(test, false))) {
		CreateFile1(test, "");
	}


	FILE *fp2;
	fp2 = fopen(test, "r");
	buff[0] = '\0';
	char ch = ' ';
	while (!feof(fp2))
	{
		ch = fgetc(fp2);
		if (ch == '\n')
		{
			count++;
		}
	}
	fclose(fp2);
	return (count);
}

/*
Used to display a line of equals signs (=)
NewLineBefore : add \n before lines of equal signs if true (default : false)
NewLineAfter  : add \n after lines of equal signs if true  (default : false)
*/
void EqualLine(bool NewLineBefore = false, bool NewLineAfter = false) {
	if (NewLineBefore == true) NewLine();
	printf("======================================================");
	if (NewLineAfter == true) NewLine();
}

const char * EqualLineReturn() {
	return "======================================================";
}

/* OutDated Function*/
/*
char * StringCombine(char* FirstString, char* SecondString) {
	
	// Allocate a seprate memory location for X in ram equal to size of firststring and second string
	// so that it will remain in memory when variable is returned.
	// Also empty its contents using '\0' to get rid of any garbage value
	char * x = (char *)malloc(sizeof(FirstString) + sizeof(SecondString) + 1);
	x[0] = '\0';
	//for (int i = 0; i < sizeof(x); i++) x[i] = '\0';
	strcat(x, FirstString);
	strcat(x, SecondString);
	return x;
}*/

void EqualLineText(char* x) {
	printf("%s\n%s\n%s", EqualLineReturn(), x, EqualLineReturn());
}

int CreateMenu(char* x,int limit,int total, bool NewLineBefore=true, bool IgnoreAdditionalChoice = false) {
	if (NewLineBefore) NewLine();
	WhiteColor(false);
	for (int i = 0; i < limit; i++) {
		printf("%d. %s\n", i+1,(x + (i * total)));
	}
	bool flag = true;
	int y;
	while (flag) {

		printf("Enter your choice: ");
		scanf_s("%d", &y);
		getchar();
		if (IgnoreAdditionalChoice) limit = 100;
		if (y > 0 && y <= limit) {
			flag = false;
		}
		else {
			printf("Invalid Option, Please Try Again\n");
		
	}
	}
	return y;
}

void MultiInputs(char* x, char* result ,int limit, int total, bool NewLineBefore = true) {
	if (NewLineBefore) NewLine();
	char output[10][50];
	for (int i = 0; i < limit; i++) {
		printf("Enter %s : ",  (x + (i * total)));
		scanf("%s", &output[i]);
		//bool flag = true;
		for (int j = 0; j < total; j++) {
			
				if ((!output[i][j] == '\0')) {
					*((result + (i * total))+j) = output[i][j];
				}
				else {
					*((result + (i * total)) + j) = '\0';
				}
			
		}

	}
	
}


void clearscreen()
{
	//for (int i = 0; i < 320; i++)
		//putchar('\n');
	system("cls");
}

int FileExists(char* filename, bool infolder = false) {
	char test[255];
	strcpy(test, filename);
	if (infolder) InDataFolder(test);
	struct stat buffer2;
	return (stat(test, &buffer2) == 0);
}

void InDataFolder(char* filename) {
	//printf("|%s|", filename);
	char test[255];
	//char test[100] = ;
	strcpy(test, "");
	strcat(test, "Data//");
	strcat(test, filename);
	strcpy(filename, test);
}

bool FriendExists(char user[20], char cmp_user[20]) {
	//int count = 0;

	char buff[255];
	char test[100] = "Data\\";
	strcat(test, user);
	strcat(test, ".friends");

	if (!(FileExists(test, false))) {
		CreateFile1(test, "");
	}


	FILE *fp2;
	fp2 = fopen(test, "r");
	buff[0] = '\0';
//	char ch = ' ';

	while (!feof(fp2))
	{
		fgets(buff, 255, fp2);
		if (buff[strlen(buff) - 1] == '\n') buff[strlen(buff) - 1] = '\0';
		if (strcmp(buff, cmp_user) == 0) {
			fclose(fp2);
			return true;
		}
	}
	fclose(fp2);
	return false;
}

bool UserExistsForLikes(char walluser[20], char liker[20], int num) {
	//int count = 0;

	char buff[255];
	char test[100];
	/*char test[100] = "Data\\";
	strcat(test, user);
	strcat(test, ".friends");*/
	snprintf(test, sizeof(test),"Data\\%s.l%d", walluser, num);
	if (!(FileExists(test, false))) {
		CreateFile1(test, "");
		return false;
	}


	FILE *fp2;
	fp2 = fopen(test, "r");
	buff[0] = '\0';
	//	char ch = ' ';

	while (!feof(fp2))
	{
		fgets(buff, 255, fp2);
		buff[strlen(buff) - 1] = '\0';
		if (strcmp(buff, liker) == 0) {
			fclose(fp2);
			return true;
		}
	}
	fclose(fp2);
	return false;
}

bool AddFriend(char* cuser, char* user) {

	//update cuser.friends file and user.friends file to add both as friend for each other
	char cuserext[255]; // username with extension .friends
	char userext[255];
	char xcuser[50];
	char xuser[50];
	strcpy(cuserext, cuser);
	strcpy(userext, user);
	strcat(cuserext, ".friends");
	strcat(userext, ".friends");
	strcpy(xcuser, cuser);
	strcpy(xuser, user);
	//strcat(xuser, "\n");
	//strcat(xcuser, "\n");
	if (FriendExists(cuser, user)) {
		return false;
	}
	else {
		AppendFile(cuserext, xuser, true, true);
		AppendFile(userext, xcuser, true, true);
	}
	return true;
}

int GetLastIdForWallPost(char user[50]) {
	char test[100];
	strcpy(test, "Data\\");
	strcat(test, user);
	strcat(test, ".wall");
	FILE* fp = fopen(test, "r");
	WallPostStruct p;
	if (fp == NULL) {
		return -1;
	}
	else {
		fseek(fp, -sizeof(WallPostStruct)-1, SEEK_END);
		fread(&p, sizeof(p), 1, fp);
	}
	fclose(fp);
	return p.PostId;
}

bool CreatePostOnWall(char walluser[50], char posteruser[50], char post[255]) {
	
	char test[100];
	strcpy(test, "Data\\");
	strcat(test, walluser);
	strcat(test, ".wall");
	WallPostStruct wallpost;
	wallpost.Likes = 0;
	wallpost.PostId = GetLastIdForWallPost(walluser) + 1;
	//inilize struct for checking later
	for (int i = 0; i < 10; i++) {
		wallpost.comments[i] = EmptyCommentStruct;
	}
	
	strcpy(wallpost.User, posteruser);
	strcpy(wallpost.Post, post);
	FILE* fp = fopen(test, "a");
	if (fp == NULL) {
		return false;
	}
	else {
		fwrite(&wallpost, sizeof(wallpost), 1, fp);
	}
	fclose(fp);
	return true;
}

bool CreateCommentOnPost(char walluser[50], char posteruser[50], char comment[80], int num) {
	char test[100];
	/*strcpy(test, "Data\\");
	strcat(test, walluser);
	strcat(test, ".wall");*/
	snprintf(test, sizeof(test), "Data\\%s.wall", walluser);
	WallPostStruct wallpost;
	//wallpost.Likes = 0;
	//wallpost.PostId = GetLastIdForWallPost(walluser) + 1;
	//inilize struct for checking later
//	for (int i = 0; i < 10; i++) {
	//	wallpost.comments[i] = EmptyCommentStruct;
	//}

	//strcpy(wallpost.User, posteruser);
	//strcpy(wallpost.Post, post);
	FILE* fp = fopen(test, "r+");
	if (fp == NULL) {
		return false;
	}
	
	fseek(fp, (num * sizeof(wallpost)) + num, 0);
	fread(&wallpost, sizeof(wallpost), 1, fp);
	int j = 0;
	while (!(((strcmp(wallpost.comments[j].comment, "") == 0)) && (strcmp(wallpost.comments[j].user, "") == 0))) {
	j++;
	}
	//j--;
	strcpy(wallpost.comments[j].user, posteruser);
	strcpy(wallpost.comments[j].comment, comment);
	rewind(fp);
	fseek(fp, (num * sizeof(wallpost)) + num, 0);
	fwrite(&wallpost, sizeof(wallpost), 1, fp);
	fclose(fp);
	return true;
}

void DisplayWallPosts(char u[50], bool OwnProfile) {
	int tpost = GetTotalWallPosts(u);
	(OwnProfile) ? printf("%d posts on your wall!", tpost) : printf("%d posts on %s's wall!", tpost,u);
	EqualLine(true, true);
	WhiteColor(true);
	//display posts
	/*
	for (int i = 0; i < (tpost * 2); i += 2) {
		char user[20], post[255];
		strcpy(user, u);
		GetWallPost(i, user, post, tpost);
		printf("%d. (%s) : \n%s\n", ((i / 2) + 10), user, post);
	}
	*/
	char test[50];
	strcpy(test, "Data\\");
	strcat(test, u);
	strcat(test, ".wall");
	FILE* fp = fopen(test, "r");
	WallPostStruct p;
	if (fp == NULL) {
		printf("Error reading wall data!");
	}
	else {
		
		int i = 1;
		while (fread(&p, sizeof(p), 1, fp)) {
			
			printf("%d. (%s) : \n", i+9, p.User);
			WhiteColor(false);
			printf("%s\n", p.Post);
			WhiteColor(true);
			i++;
		}
		
	}
}

bool LikePost(int num, char userwall[50], char liker[50]) {
	/* generate a username.lnum file to check if user already liked the said post*/
	char test[100];
	////strcpy(test, "Data\\");
	////strcat(test, userwall);
	//strcat(test, ".l");
	//strcat(test, num);
	snprintf(test, sizeof(test), "Data\\%s.l%d", userwall, num);
	if (!(FileExists(test))) {
		// can like
		AppendFile(test, liker, false, true);
		PerformLike(num, userwall);
		return true;
	}
	else {
		// check if user already liked!
		if (UserExistsForLikes(userwall, liker, num)) {
			return false;
		}
		else {
			AppendFile(test, liker, false, true);
			PerformLike(num, userwall);
			return true;
		}
		//return false;
	}

}

void PerformLike(int num, char userwall[50]) {
	WallPostStruct w;
	char test[100];
	snprintf(test, sizeof(test), "Data\\%s.wall", userwall, num);
	FILE* fp = fopen(test, "r+");
	if (fp == NULL) {
		printf("Error while liking the post");
	}
	else {
		/*for (int i = 0; i <= num; i++) {

			if (i == num) {

			}
		}*/
		fseek(fp, (num * sizeof(w))+num, 0);
		fread(&w, sizeof(w), 1, fp);
	//	printf("%s \n %s", w.User, w.Post);
		rewind(fp);
		fseek(fp, (num * sizeof(w))+num, 0);
		w.Likes += 1;
		fwrite(&w, sizeof(w), 1, fp);
	}
	fclose(fp);
}


/* Color Functions*/

void ZalimColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE |
		FOREGROUND_GREEN |
		FOREGROUND_INTENSITY

	);
}

void WhiteColor(bool x) {
	if (x) {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE |
			FOREGROUND_GREEN |
			FOREGROUND_RED |
			FOREGROUND_INTENSITY
		);
	}
	else {
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_BLUE |
			FOREGROUND_GREEN |
			FOREGROUND_RED 
		);
	}
}

void InfoTextColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN |
		FOREGROUND_RED
	);
}

void ErrorColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_RED |
		FOREGROUND_INTENSITY
	);
}

void SuccessColor() {
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), FOREGROUND_GREEN |
		FOREGROUND_INTENSITY
	);
}