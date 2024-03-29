#define _BSD_SOURCE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

#include "../interfaces/getCon.h"
#include "../interfaces/inputOutput.h"
#include "../interfaces/probability.h"
#include "../interfaces/random.h"

#define SCORE_BORDER	"----------------------------------"
#define FILEPATH	"../../Resources/"
#define SCORE_FILEPATH  "../../Resources/highScore.txt"
#define PRINT_LIM1	18
#define MAX_NAME_LEN 	17
#define MAX_LINE_LEN 	50
#define MAX_BUFF	2000
//#define MAX_RESP_LEN 	1
#define MAX_IP_LEN 	45
#define MAX_PORT_LEN 	5
#define NULL_TERM	'\0'
#define DICE_PRINT	3
#define RANDOM_ROLLS	10
#define U_SECONDS	250000
#define TAB 9

void endGameScreen(char* playerName, unsigned p1Score, char* opponentName, unsigned opScore, _Bool isHighScore)
{
	
	system("clear");
	printf("Game Over!\n");
	printf("-------------------------\n");
        
	if (p1Score > opScore)
	{
		printf("%s, you stand over the charred ashes that are the remains of your former opponent.\n",playerName);
		printf("The wind picks up, and your enemy, %s, is but dust in the wind.\n", opponentName);
		printf("%s, get gud scrub.\n\n",opponentName);
	} else if (p1Score < opScore)
	{
		printf("%s, you fought hard, but your best wasn't good enough. %s trounced you.\n",playerName,opponentName);
		printf("%s, your holdings, your title, and your pride belongs to %s now.\n",playerName,opponentName);
		printf("You have brought great shame to your family.\n\n");
	} else 
	{
		printf("Listen up %s and %s. The only thing worse than losing a contest of this\n", playerName,opponentName);
		printf("magnitude is having things end with a tie. Seriously, you both suck.\n\n");
	}

	printf("Final Scores:\n");
	printf("%s: %u\n%s: %u\n\n",playerName, p1Score,opponentName,opScore);
        
	if(isHighScore && (p1Score > opScore))
	{
		printf("%s, not only did you steal the game and your opponent's dignity but\n",playerName);
		printf("you also got a high score! Congrats! Your existence is now validated!\n");
	} else if (isHighScore && (p1Score < opScore))
	{
		printf("%s, not only did you fail in a way that I would describe as pornographic\n",playerName);
		printf("in its excess, but your opponent, %s, also got a high score. Shame %s.\n",opponentName, playerName);
	} else if (isHighScore){
		printf("Oh look, %s and %s, you both got high scores but neither of you won the game.\n", playerName, opponentName);
		printf("How bout you two losers go get married now so you can be losers together?\n");
	}
	printf("-------------------------\n");
	printf("Press any key to return to main menu\n");

	char response;
	response = getch();		
	
}

void displayStopTurn(char* playerName, unsigned score, char* opponentName)
{
	system("clear");

	printf("--------------------\n");
	printf("%s like the noble Kenny Rogers, you knew to fold em' rather than hold em'.\n", playerName);
	printf("Your score for the round is %u.\n\n",score);
	printf("%s, hopefully you can show a modicum of judgement on your turn.\n",opponentName);
	printf("Press the any key to continue...\n");
	printf("--------------------\n");

	char response;
	response = getch();
}

void displayFailRoll(char* playerName, unsigned firstRoll, char* opponentName)
{

	system("clear");
	
	printf("--------------------\n");
	printf("%s like Icarus, your hubris has cost you dearly.\n", playerName);
	printf("You have re-rolled your first roll:  %u \n\n",firstRoll);
	printf("Your score for the round is ZERO. Do not pass go, do not collect $200.\n\n");
	printf("It is now %s's turn. Do not repeat the mistakes of your opponent.\n",opponentName);
	printf("Press any key to continue...\n");
	printf("--------------------\n");

	char response;
	response = getch();

}

void displayLocalPlayGetName(char* player1, char* player2, _Bool opponentHuman)
{
	_Bool error1 = 0;
	_Bool error2 = 0;
	RESTART:
	system("clear");
	char input = 0;
	unsigned i;
	
	printf("Please enter player name(s)\n");
	printf("-----------------------------\n");
	printf("Player 1 - enter name:\n");
	if (error1) {
		printf("*** You entered an invalid character! ***\n***     No spaces or tabs allowed     ***\n");
		error1 = 0;
	}

	if (error2) {
		printf("%s\n", player1);
	} else {
		for (i = 0; i < MAX_NAME_LEN - 1; i++)
		{ 
			input = getc(stdin);
			// printf("DEBUG: Input is %d\n", input);
			if (input == '\n') {
				// End of input
				break;
			} else if (input == ' ' || input == (char)TAB) {
				error1 = 1;
				// printf("Restart\n");
				char tmp;
				do {
					tmp = getc(stdin);
				} while (tmp != '\n' && tmp != EOF);
				goto RESTART;
			}
			player1[i] = input;
			
		}
		if (input != '\n')
		{
			char tmp;
			do {
				tmp = getc(stdin);
			} while (tmp != '\n' && tmp != EOF);
		}
		player1[i] = NULL_TERM;
	}
 
	if (opponentHuman)
	{
		printf("Player 2 - enter name: \n");
		if (error2) {
			printf("*** You entered an invalid character! ***\n*** No spaces or tabs allowed. ***\n");
			error2 = 0;
		}

		for (i = 0; i < MAX_NAME_LEN - 1; i++)
		{	
			
			input = getc(stdin);
			// printf("DEBUG: Input is %d\n", input);
			if (input == '\n') 
			{
				// End of input
				break;
			} else if (input == ' ' || input == (char)TAB) {
				error2 = 1;
				char tmp;
				do {
					tmp = getc(stdin);
				} while (tmp != '\n' && tmp != EOF);
				goto RESTART;
			}
			player2[i] = input;
		}
		if (input != '\n')
		{
			char tmp;
			do {
				tmp = getc(stdin);
			} while (tmp != '\n' && tmp != EOF);
		}		
		
		printf("\n -----------------------------\n");
		player2[i] = NULL_TERM;
	}
	system("clear");
	
}

void displayRules()
{

	system("clear");
	FILE *fp;
	unsigned i = 0;
	
	char fileP[] = FILEPATH "rules.txt";
	fp = fopen(fileP, "r");
	char buff[MAX_LINE_LEN];
	int c;
		
	for(i = 0; i < PRINT_LIM1; i++ )
	
	{
		fgets(buff,MAX_LINE_LEN, (FILE*)fp);
		printf("%s", buff);
	}

	char response;
	response = getch();
	
	
	while((c = fgetc(fp)) != EOF)
	{
		fgets(buff,MAX_LINE_LEN,(FILE*)fp);
		printf("%c%s", c,buff);
	}
	fclose(fp);	
	response = getch();	
	system("clear");
	
	
}

unsigned displayMainMenu()
{
	system("clear");

	FILE *fp;
	char fileP[] = FILEPATH "MainPage.txt";
	fp = fopen(fileP, "r");
	char buff[MAX_LINE_LEN];
	int c;	

	while((c = fgetc(fp)) != EOF)
	{
		fgets(buff,MAX_LINE_LEN,(FILE*)fp);
		printf("%c%s",c,buff);
	}	
	printf("\n");
	
	while (1)
	{
		char response;
		response = getch();
		unsigned retVal = 0;

		switch(response){
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
				retVal = 4;
				return retVal;
			case 'R':
			case 'r':
				system("clear");
				fclose(fp);
				retVal = 3;
				return retVal;
			case 'E':
			case 'e':
				fclose(fp);
				system("clear");
				exit(0);
			default: 
				printf("Please enter a proper selection: \n");

		}
	}
}

void displayHighScore()
{

		
	system("clear");

	FILE *f;
        if( access( SCORE_FILEPATH, F_OK) != -1){
                printf(" Top Ten Scores\n");
                printf("--------------------------------------------\n");
                f = fopen(SCORE_FILEPATH, "r");
                int i;
                //Loop through up to 10 times
		for (i = 1; i <= 10; i++){
			char name[50] = {0};
                        fscanf(f, "%s", name);
                        char date[50] = {0};
                        fscanf(f, "%s", date);
                        char score[50] = {0};
                        fscanf(f, "%s", score);
                       //Kill loop if EOF is found
			if (feof(f)){
                                break;
                        }
			//Display the ranking of player as number
			//followed by one or two spaces and a |
			//finally the date is displayed followed by a |
                        printf(" %d%s| %s | ",i, (i < 10 ? "  " : " "), date);
                        int j = 0;

			//Display all the characters of the player name
			//up to a maximum of 16 chars
                        for (; j < 16 && name[j]; j++){
                                printf("%c", name[j]);
                        }
			//If j has not hit 16 then print
			//spaces until j hits 16
                        for (; j < 16; j++){
                                printf(" ");
                        }
			//Display | and then the score
                        printf(" | %s\n", score);
                }
                printf("--------------------------------------------\n");
                printf("Press any key to return to the Main Menu.\n");
 		char response;
		response = getch();               
		fclose(f); 	
	}
	
}

unsigned displayLocalSelectOpponent()
{
	system("clear");
	FILE *fp;
	char fileP[] = FILEPATH "LocalPlay.txt";
	fp = fopen(fileP, "r");
	char buff[MAX_LINE_LEN];
	int c;	

	while((c = fgetc(fp)) != EOF)
	{
		fgets(buff,MAX_LINE_LEN,(FILE*)fp);
		printf("%c%s",c,buff);
	}	
	
	while(1)
	{
		char response;
		response = getch();
		unsigned retVal = 0;

		//POSSIBLE ERROR WITH VALIDATION
		switch(response){
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
				printf("Please enter a proper selection: \n");
		}
	}
}

unsigned displayNetworkSelectMode()
{

	system("clear");
	FILE *fp;
	char fileP[] = FILEPATH "NetworkPlay.txt";
	fp = fopen(fileP, "r");
	char buff[MAX_LINE_LEN];
	int c;
	
	while((c = fgetc(fp)) != EOF)
	{
		fgets(buff,MAX_LINE_LEN,(FILE*)fp);
		printf("%c%s",c,buff);
	}

	printf("\n");	
	
	while (1)
	{
		char response;
		response = getch();
		unsigned retVal;
		
		switch(response){
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
				printf("Please enter a proper selection: \n");
		
		}
	}
}

void displayInGameHelpMenu() //Work in progress
{

	system("clear");
	FILE *fp;
	char fileP[] = FILEPATH "GameHelp.txt";
	fp = fopen(fileP, "r");
	char buff[MAX_LINE_LEN];
	int c;

	while((c = fgetc(fp)) != EOF)
	{
		fgets(buff,MAX_LINE_LEN,(FILE*)fp);
		printf("%c%s",c,buff);
	}	
	printf("\n");	
	char response;
	response = getch();
	fclose(fp);
}

void displayNetworkPlayInput(char* IPaddress, int* port)
{

	system("clear");
	
	char strPort[5];
	char *strIP = (char*)calloc(MAX_IP_LEN, sizeof(char));
	unsigned i;
	
	printf("Network Play Mode \n -----------------------------\n");
	printf("Enter Server Information: \nPort: \n");
	scanf("%s", strPort);
	
	printf("Address: \n");
	scanf("%s", strIP);
	printf("\n -----------------------------\n");
	
	for (i = 0; i < strlen(strIP) + 1; i++)
	{
		IPaddress[i] = strIP[i];
	}
	
	IPaddress[i] = '\0';
	free(strIP);
	*port = atoi(strPort);
	
}

void printDie(unsigned die1,unsigned die2)
{
	unsigned i;
	char* die[10];
	
	//Create different lines for printing of dice horizontally 
	die[0] = " __________  ";
	die[1] = "|          | ";
	die[2] = "|          | ";
	die[3] = "|          | ";
	die[4] = "|          | ";
	die[5] = "|__________| ";

	//Create lines for the divets on the die
	die[6] = "|  O     O | ";
	die[7] = "|     O    | ";
	die[8] = "|        O | ";
	die[9] = "|  O       | ";
	
	//Create array to hold unsigned integers that can be used
	//to choose the proper line to print for the face of the die
	//based off the line that needs to be printed and the die that
	//was rolled 
	unsigned diceRay[3][6] = { {2,9,9,6,6,6} , {7,2,7,2,7,6}, {2,8,8,6,6,6} };	

	printf("%s%s\n", die[0],die[0]);
	printf("%s%s\n", die[1],die[1]);
		
	for(i = 0; i < DICE_PRINT; i++)
	{
		printf("%s",die[diceRay[i][die1 - 1]]);
		printf("%s\n",die[diceRay[i][die2 - 1]]);
	}

	printf("%s%s\n", die[5],die[5]);
}

unsigned displayTurn(DisplayTurn turn)
{
	//Generate random for use with dice roller 
	randomInit();
	
	char* p1Name = turn.p1Name;
	unsigned p1Score = turn.p1Score;
	unsigned firstRoll = turn.firstRoll;
	unsigned rollCounter = turn.rollCounter;
	unsigned roundScore = turn.roundScore;
	unsigned die1 = turn.die1;
	unsigned die2 = turn.die2;
	unsigned turnScore = turn.turnScore;
	char* p2Name = turn.p2Name;
	unsigned p2Score = turn.p2Score;
	_Bool activePlayer = turn.activePlayer;
	unsigned turnCounter = turn.turnCounter;
	unsigned i, rRoll1, rRoll2;
	
	//Loop for printing off random die on display
	for(i = 0; i < RANDOM_ROLLS; i++)
	{
		
        	system("clear");
        	printf("Active Player: %s\n", (activePlayer ? p2Name : p1Name));
        	printf("Current Round: %u/20 \n", turnCounter);
        	printf("Current Roll: %u \n", rollCounter);
        	printf("-----------------------------\n");
		printf("First roll: \n");
        	printf("Turn score: \n\n");
        	printf("You rolled: \n");
		//Grab two random rolls to be displayed		
		rRoll1 = getRandomInt(1,6);
		rRoll2 = getRandomInt(1,6);

		printDie(rRoll1,rRoll2);
		//Sleep for half a second
		//sleep(1);
		usleep(U_SECONDS);
	} 	


        system("clear");
        printf("Active Player: %s\n", (activePlayer ? p2Name : p1Name));
        printf("Current Round: %u/20 \n", turnCounter);
        printf("Current Roll: %u \n", rollCounter);
        printf("-----------------------------\n");
        printf("First roll: %u \n", firstRoll);
        printf("Turn score: %u \n\n", turnScore);
        printf("You rolled: %u + %u = %u \n", die1, die2, roundScore);
	
	printDie(die1,die2);
	
	printf("\n%s, score: %u \n", p1Name, p1Score);
    	printf("%s, score: %u \n", p2Name, p2Score);
	printf("-----------------------------\n");
	
	printf("(R)oll \n");
	printf("(S)top \n");
	printf("(P)robability \n\n");
	printf("(H)elp \n");
	printf("(F)orfeit \n");
	
	while (1)
	{
		char response;
		response = getch();
		unsigned retVal;
		
		switch(response){
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
				printf("Please enter a proper selection: \n");
		}
	}
}

void displayProbability(double result){
	system("clear");
	char percent = '%';
	printf("Probability!\n");
	printf("--------------------\n");
	printf("It is probably quite probable that the probability of re-rolling your first roll is:\n");
	printf("%.2f%c...\n\n",result,percent);
	printf("Remember, knowledge is power!\n");
	printf("--------------------\n");
	printf("Press the any key to continue...\n");
	

	char response;
	response = getch();
}
