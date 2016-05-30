#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <getCon.h>
#include "inputOutput.h"
#define PRINT_LIM1		18
#define MAX_NAME_LEN 	8
#define MAX_LINE_LEN 	50
#define MAX_RESP_LEN 	1
#define MAX_IP_LEN 		45
#define MAX_PORT_LEN 	5

void displayLocalPlayGetName(char* player1, char* player2, unsigned twoPlayer)
{
	char strName1[MAX_NAME_LEN], strName2[MAX_NAME_LEN];
	unsigned i;
	
	printf("Local Play Mode \n -----------------------------\n");
	printf("Player 1 - enter name: \n");
	fgets(strName1,MAX_NAME_LEN,stdin);

 
	if (twoPlayer)
	{
	printf("Player 2 - enter name: \n");
	fgets(strName2,MAX_NAME_LEN,stdin);
	printf("\n -----------------------------\n");
	}
	
	for(i = 0 ; i < strlen(strName1); i++)
	{
		player1[i] = strName1[i];
	}
	
	//NULL terminate first array
	
	if(twoPlayer)
	{
		for(i = 0 ; i < strlen(strName1); i++)
		{
			player2[i] = strName2[i];
		}
	}
	//NULL terminate second array
	
}

void displayRules()
{
	FILE *fp;
	unsigned i = 0;
	
	fp = fopen("../Design Documents/UserManual/rules.txt", "r");
	char buff[MAX_LINE_LEN];

		
	for(i = 0; i < PRINT_LIM1; i++ )
	{
		fgets(buff,MAX_LINE_LEN, (FILE*)fp);
		printf("%s", buff);
	}

	char response;
	getch_(response);
		
	while(feof(fp) == 0)
	{
		fgets(buff,MAX_LINE_LEN,(FILE*)fp);
		printf("%s", buff);
	}
		
	getch_(response);
	system("clear");
	
	//if (response == "\n")
	//{
		//fclose(fp);
		//system("clear");
	//} 
	
	//else if (toupper(response[0]) == "R")
	//{
		//fclose(fp);
		//system("clear");
		//displayRules();	
	//}
	//TALK TO TEAMMEMBERS ABOOT DISPLAY RULES AGAIN WITH R			
	
}

unsigned displayMainMenu()
{

	FILE *fp;
	fp = fopen("../Design Documents/UserManual/UM-SS-MainPage.txt", "r");
	char buff[MAX_LINE_LEN];
	
	while(feof(fp) == 0)
	{
		fgets(buff,MAX_LINE_LEN,(FILE*)fp);
		printf("%s",buff);
	}	
	
	while (1 == 1)
	{
		char response;
		getch_(response);
		unsigned retVal = 0;

		//POSSIBLE ERROR WITH VALIDATION
		char respVal = response;
		
		switch(respVal){
			case 'L':
			case 'l':
				system("clear");
				fclose(fp);
				retVal = 1;
				return retVal;
			case 'N':
			case 'n':
				system("clear");
				fclose(fp);
				retVal = 2;
				return retVal;			
			case 'V':
			case 'v':
				system("clear");
				fclose(fp);
				exit(0); //TO BE IMPLEMENTED
			case 'R':
			case 'r'://DO WE WANNA RETURN A NUMBER VALUE FOR THIS AS WELL?
				system("clear");
				fclose(fp);
				displayRules();
				break;
			case 'E':
			case 'e'://IS THIS THE FUNCTION THAT WILL EXIT THE PROGRAM
				fclose(fp);
				system("clear");
				exit(0);
			default: 
				printf("Please enter a proper selection: ");

		}
	}
}

unsigned displayLocalSelectOpponent()
{
	FILE *fp;
	fp = fopen("../Design Documents/UserManual/UM-SS-LocalPlay.txt", "r");
	char buff[MAX_LINE_LEN];
	
	while(feof(fp) == 0)
	{
		fgets(buff,MAX_LINE_LEN,(FILE*)fp);
		printf("%s",buff);
	}	
	
	while(1 == 1)
	{
		char response[MAX_RESP_LEN];
		fgets(response,MAX_RESP_LEN,stdin);
		unsigned retVal = 0;

		//POSSIBLE ERROR WITH VALIDATION
		char respVal = response[0];
		
		switch(respVal){
			case 'S':
			case 's':
				system("clear");
				fclose(fp);
				retVal = 1;
				return retVal;
			case 'M':
			case 'm':
				system("clear");
				fclose(fp);
				retVal = 2;
				return retVal;			
			case 'P':
			case 'p':
				system("clear");
				fclose(fp);
				retVal = 0;
				return retVal;
			case 'E':
			case 'e':
				fclose(fp);
				system("clear");
				exit(0);
			default: 	
				printf("Please enter a proper selection: ");
		}
	}
}

unsigned displayNetworkSelectMode()
{
	FILE *fp;
	fp = fopen("../Design Documents/UserManual/UM-SS-NetworkPlay.txt", "r");
	char buff[MAX_LINE_LEN];

	while(feof(fp) == 0)
	{
		fgets(buff,MAX_LINE_LEN,(FILE*)fp);
		printf("%s",buff);
	}	
	
	while (1 == 1)
	{
		char response;
		getch_(response);
		unsigned retVal;

		//POSSIBLE ERROR WITH VALIDATION
		char respVal = response;
		
		switch(respVal){
			case 'H':
			case 'h':
				system("clear");
				fclose(fp);
				retVal = 1;
				return retVal;
			case 'C':
			case 'c':
				system("clear");
				fclose(fp);
				retVal = 2;
				return retVal;			
			case 'P':
			case 'p':
				system("clear");
				fclose(fp);
				retVal = 0;
				return retVal;
			case 'E':
			case 'e':
				fclose(fp);
				system("clear");
				exit(0);	
			default: 
				printf("Please enter a proper selection: ");
		
		}
	}
}

void displayInGameHelpMenu() //Work in progress
{
	FILE *fp;
	fp = fopen("../Design Documents/UserManual/UM-SS-GameHelp.txt", "r");
	char buff[MAX_LINE_LEN];

	while(feof(fp) == 0)
	{
		fgets(buff,MAX_LINE_LEN,(FILE*)fp);
		printf("%s",buff);
	}	
	
	char response;
	getch_(response);
	fclose(fp);
}

void displayNetworkPlayInput(char* IPaddress, unsigned* port)
{
	
	char strPort[5];
	char *strIP = (char*)calloc(MAX_IP_LEN, sizeof(char));
	unsigned i;
	
	printf("Network Play Mode \n -----------------------------\n");
	printf("Enter Server Information: \n Port: \n");
	scanf("%s", strPort);
	
	printf("Address: \n");
	scanf("%s", strIP);
	printf("\n -----------------------------\n");
	
	for (i = 0; i < strlen(strIP) + 1; i++)
	{
		IPaddress[i] = strIP[i];
	}
	
	free(strIP);
	*port = atoi(strPort);
	
}

unsigned displayTurn(char* name, unsigned firstRoll, unsigned round, unsigned roundScore, unsigned die1, unsigned die2, unsigned gameScore, unsigned opponentScore)
{

	printf("Current Round: %u \n", round);
	printf("-----------------------------\n");
	printf("First roll: %u \n", firstRoll);
	printf("Round score: %s \n\n", roundScore);
	printf("Last roll: %u + %u = %u \n\n PLACE HOLDER HERE. SORRY, NO DICE. \n\n", die1, die2, roundScore);
	printf("Your score: %u \n", gameScore);
	printf("Opponent score: %u \n", opponentScore);
	printf("-----------------------------\n");
	
	printf("(R)oll \n");
	printf("(S)top \n");
	printf("(P)robability \n\n");
	printf("(H)elp \n");
	printf("(F)orfeit \n");
	
	while (1 == 1)
	{
		char response;
		getch_(response);
		unsigned retVal;
		
		//POSSIBLE ERROR WITH VALIDATION
		//charAt[0] then cast to an integer to use in the switch statement
		char respVal = response;
		
		switch(respVal){
			case 'R':
			case 'r':
				system("clear");
				retVal = 1;
				return retVal;
			case 'S':
			case 's':
				system("clear");
				retVal = 2;
				return retVal;			
			case 'P':
			case 'p':
				system("clear");
				retVal = 3;
				return retVal;
			case 'H':
			case 'h':
				system("clear");
				retVal = 4;
				return retVal;
			case 'F':
			case 'f':
				system("clear");
				retVal = 0;
				return retVal;
			default: 
				printf("Please enter a proper selection: ");
		}
	}
}