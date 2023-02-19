#include "raylib.h"
#include <stdio.h>
#include <time.h>

// dimensions of my computer that centers
// the window in my screen, this is ultimately
// for my personal aesthetic and doesn't need to be implemented
#define SCREEN_WIDTH 2560
#define SCREEN_HEIGHT 1600

// defining a screen type
typedef enum {
	MENU, INSTRUCTIONS, Q1, Q2,
	Q3, Q4, Q5, Q6, Q7, Q8, Q9, Q10, Q11, Q12,
	Q13, Q14, Q15, Q16, Q17, Q18, Q19, Q20, END
} GameMode;
GameMode currentMode;

// returns card number so the end screen
// knows which fortune to display
int getCard(int points);
// gives the user a silly remark before 
// transitioning to the next screen
void transition(GameMode screen);