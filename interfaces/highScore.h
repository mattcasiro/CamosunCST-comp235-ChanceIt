<<<<<<< HEAD
#include<stdio.h>

/*Pre-condition: a file for highscore exists
 *Post-condition: The highscore was displayed on screen
 *Clean up: N/A
 *Param N/A
 *returns N/A
 */

 void getHighScore(char info);

/*Pre-condition: a file for highscore exists
 *Post-condition: The highscore has been amended with new information
 *Clean up: N/A
 *Param  name takes in the name of the player
 *Param  date   takes in the date of the game play
 *Param score   takes in the player�s score 
 *returns N/A
 */

 void amendHighScore(char* name, char* date, unsigned score);
=======
// Pre: a file for highscore exists
// Post: The highscore was displayed on screen
// Clean up: N/A
// Param N/A
// returns N/A
 void getHighScore();

// Pre: a file for highscore exists
// Post: The highscore has been amended with new information, if necessary
// Clean up: N/A
// Param info
// returns N/A
void amendHighScore(char* name, char* date, unsigned score);
>>>>>>> 558f591f9d724ecf6dd17b60939df674aa6e0d33
