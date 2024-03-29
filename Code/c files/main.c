#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "../interfaces/inputOutput.h"
#include "../interfaces/game.h"
#include "../interfaces/random.h"
#include "../interfaces/socket.h"

typedef enum
    {
        UNASSIGNED,
        PLAY_LOCAL,
        PLAY_NETWORK,
        SHOW_RULES,
        HIGH_SCORES,
        EXIT_GAME
    } MainMenuInput;

// static char ip[45];
char* ip = "52.38.98.137";
static int port = 1092;

int main(int argc, char** argv){
	randomInit();
    // Main Menu Game Loop
    int players;
    while (1)
    {
        // Request IO to display main menu
        MainMenuInput result = (MainMenuInput)displayMainMenu();
        switch (result)
        {
            case PLAY_LOCAL:
                players = displayLocalSelectOpponent();
                if(players == 1){
                    gameInit(0, 0);
                }else if(players == 2){
                    gameInit(0, 1);
                }
                break;
            case PLAY_NETWORK:
                //playNetwork();
                players = displayNetworkSelectMode();
                // displayNetworkPlayInput(ip, &port);
                // human playing:
                if (players == 1){
                    gameInit(1,1);
                // computer playing:
                }else if(players == 2){
                    gameInit(1,0);
                }
                break;
            case SHOW_RULES:
                displayRules();
                break;
            case HIGH_SCORES:
                displayHighScore();
                //Highscores is not implemented yet
                break;
            case EXIT_GAME:
                printf("Thanks for playing!\n");
                exit(0);
            default:
                printf("Sanity check failed - game:gameInit:displayMainMenu:switch\n");
                exit(0);
        }

    }
}
