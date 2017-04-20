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

char * StringCombine(char* FirstString, char* SecondString) {
	// Allocate a seprate memory location for X in ram equal to size of firststring and second string
	// so that it will remain in memory when variable is returned.
	// Also empty its contents using '\0' to get rid of any garbage value
	char * x = (char *)malloc(sizeof(FirstString) + sizeof(SecondString));
	for (int i = 0; i < sizeof(x); i++) x[i] = '\0';
	strcat(x, FirstString);
	strcat(x, SecondString);
	return x;
}

void EqualLineText(char* x) {
	printf("%s\n%s\n%s", EqualLineReturn(), x, EqualLineReturn());
}

int CreateMenu(char* x,int limit,int total, bool NewLineBefore=true) {
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
	
	//return "";
}


void clrscr()
{
	system("@cls || clear");
}