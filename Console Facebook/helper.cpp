#include "stdafx.h"
#include "helper.h"
#include <stdlib.h>
#include <string>
#include <iostream>
/*
Used to display New Line
*/
void NewLine() {
	printf("\n");
}

void CreateFile(char* filename, char* data) {
	FILE *fp = NULL;
	fp = fopen(filename, "w");
	fprintf(fp, "%s", data);
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

void GetWallPost(int number, char user[20], char post[255], int total) {
	
	FILE *fp;
	char buff[255];
	char test[100] = "Data//";
	strcat(test, user);
	strcat(test, ".wall");
	fp = fopen(test, "r");
	buff[0] = '\0';
	for (int i = 0; i < (total*2); i++) {
		fgets(buff, 255, (FILE*)fp);
		if (buff[strlen(buff) - 1] == '\n') {
			buff[strlen(buff) - 1] = '\0'; /* Remove \n at end*/
		}
		else {
			buff[strlen(buff)] = '\0';
		}
		if (i == number) {
			strcpy(user, buff);
		}
		if (i == (number + 1)) {
			strcpy(post, buff);
		}
		
		buff[0] = '\0';
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

int FileExists(char* filename) {
	struct stat buffer2;
	return (stat(filename, &buffer2) == 0);
}